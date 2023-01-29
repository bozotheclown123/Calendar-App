#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"

int init_calendar(const char *name, int days,
                  int (*comp_func) (const void *ptr1, const void *ptr2),
                  void (*free_info_func) (void *ptr), Calendar ** calendar) {
/* checks if the parameters are valid */
 if ((*calendar) != NULL && name != NULL && days >= 1) {
   /* dynamically allocates memory for the Calendar struct */
     (*calendar) = malloc(sizeof(Calendar));
     /* makes sure calendar struct was dynamically allocated */
     if (calendar != NULL){
       /* dynamically allocates memory for the name field to hold a copy
          of parameter name’s string */
        (*calendar)->name = malloc((strlen(name) + 1));
        /* makes sure name field was dynamically allocated */
        if ((*calendar)->name != NULL){
            strcpy((*calendar)->name, name);
            (*calendar)->days = days;
            (*calendar)->comp_func = comp_func;
            (*calendar)->free_info_func = free_info_func;
            /* dynamically allocates memory for the events field to hold an 
               array of pointers to Event structs */
            (*calendar)->events = calloc(days, sizeof(Event));
            /* makes sure events field was dynamically allocated */
            if ((*calendar)->events != NULL) {
                (*calendar)->total_events = 0;
                return SUCCESS;
            }
        }
     }
 }
 return FAILURE;
                  }
 


int print_calendar(Calendar *calendar, FILE *output_stream, int print_all){
    Event *current_event = NULL;
    int i = 0;
  /* checks if the parameters are valid */
  if (calendar != NULL && output_stream != NULL ){
    
    if (print_all){
      fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
      fprintf(output_stream, "Days: %d\n", calendar->days);
      fprintf(output_stream, "Total Events: %d\n", calendar->total_events);
      fprintf(output_stream, "\n");
    }

    fprintf(output_stream, "**** Events ****\n");
    /* prints out the information about events */
    if (calendar->total_events > 0) { 
      /* loops through each day in the calendar */       
        for (i = 0; i < calendar->days; i++) {
            printf("Day %d\n", i + 1);
            current_event = calendar->events[i];
            while (current_event != NULL) {
	            fprintf(output_stream, 
              "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
		          current_event->name,
              current_event->start_time, 
              current_event->duration_minutes);
	            current_event = current_event->next;
            }
        }
    }
    return SUCCESS;
  }
  return FAILURE;
}



int add_event(Calendar *calendar, const char *name, int start_time, 
              int duration_minutes, void *info, int day) {

Event *current = calendar->events[day - 1], *prev = NULL, *new_item, *checking;
/* checks if parameters are valid */
if (calendar != NULL &&  name != NULL && start_time >= 0 && start_time <= 2400
     && duration_minutes > 0 && day >= 1 && day <= calendar->days ) {
  /* checks if the event is already in the linked list */
  if (find_event(calendar, name, &checking) == FAILURE) {
      new_item = malloc (sizeof(Event));
      if (new_item != NULL) {
        new_item->name = malloc(strlen(name)+1);
	      if (new_item->name != NULL) {
            strcpy(new_item->name, name);
	          new_item->info = info;
	          new_item->start_time = start_time;
	          new_item->duration_minutes = duration_minutes;
        }
      }
  }
  /* updates previous and current to determine 
     the exact spot for new_item to be inserted */
  while (current != NULL &&  (calendar->comp_func(current, new_item) < 0)) {
      prev = current;
      current = current->next;
   }
  /* new_item inserted into its proper place in the linked list */
   new_item->next = current; 

   if (prev == NULL) { /* Insert at the beginning */ 
      calendar->events[day - 1] = new_item;
   } else {
      prev->next = new_item;
   }
   /* Updates total_events */
  calendar->total_events++;
  return SUCCESS;
     }
  return FAILURE;
}


int find_event(Calendar *calendar, const char *name, Event **event){
  Event  *current = NULL;
  int i = 0;
  /* checks if the parameters are valid */
  if (calendar != NULL &&  name != NULL && event != NULL){
    
    for (i = 0; i < calendar->days; i++){
      current = calendar->events[i];
      while (current != NULL) {
        /* event has been found according to its name */
	      if (strcmp(current->name, name) == 0) {
	        *event = current;
	        return SUCCESS;
	    } else {
	        current = current->next;
      }
      }
    }
  }
  return FAILURE;
}


int find_event_in_day(Calendar *calendar, const char *name, 
                      int day, Event **event) {
  Event  *current = NULL;
   /* checks if the parameters are valid */
  if (calendar!= NULL && name != NULL && event != NULL && 
      day >= 1 && day <= calendar->days) {

    current = calendar->events[day-1];
    while (current != NULL) {
      /* event has been found according to its name */
      if (strcmp(current->name, name) == 0){
	      *event = current;
	      return SUCCESS;
      } else {
      current = current->next;
      }
    }
  }
  return FAILURE;
}


int remove_event(Calendar *calendar, const char *name){
  int i = 0;
  Event  *current = NULL, *previous = NULL, *checking;
  /* Checking if we have valid parameters and if the event exists */
  /* Can't remove an event if it doesn't even exist */
  if (calendar != NULL &&  name != NULL && 
      find_event(calendar, name, &checking) == SUCCESS ){
  
    for (i = 0; i < calendar->days; i++){
      current = calendar->events[i];
       /* An event is removed by changing the references. The removed event 
          will have no reference in the linked list */ 
      while (current != NULL){
	      if (strcmp(current->name, name) == 0) {
	
	        if (current == calendar->events[i]) {
            /* If the event we found was located at the head 
              (first event in the linked list) */
	          calendar->events[i] = current->next;  
          } else {
	          previous->next = current->next;
          }

    /* Freeing any dynmaically allocated memory 
       associated with the event to be removed */
	  free(current->name);
	  if (current->info && calendar->free_info_func) {
	    calendar->free_info_func(current->info);
	  }
	  free(current); 
    /* Updating total_events */
	  calendar->total_events--;
	  return SUCCESS;	

	  } else {
	  previous = current;
	  current = current->next;
    }
      }
    }
  }
  return FAILURE;
}


void *get_event_info(Calendar *calendar, const char *name){
  Event  *current = NULL;
  int i = 0;

  for (i = 0; i < calendar->days; i++){
    
    current = calendar->events[i];
    while (current != NULL) {
      /* Simply return the event's info once we have found the event */
      if (strcmp(current->name, name) == 0){
	      return current->info;
      } else {
      current= current->next;
      }
    }  
  }
  return NULL;
}

int clear_calendar(Calendar *calendar){
    int i = 0;
    if (calendar != NULL){ 
      /* Loops through each day in the calendar and calls the function 
        clear_day to clear each day in the calendar */ 
        for (i = 0; i < calendar->days; i++) {
            clear_day(calendar, i + 1);
        }
    return SUCCESS;
  }
  return FAILURE;
}
int clear_day(Calendar *calendar, int day){
  Event *previous, *current;
  /* Checks if the parameters are valid */
  if (calendar != NULL && day > 0 && day <= calendar->days) {
    current = calendar->events[day - 1];
    while (current) {
      /* We use prev because if we just use current, free current, and then 
      do current = current->next, it will result in a segmentation fault 
      (core dumped). So we are using previous as a temporary variable
      for current and then free memory with no issue */
      previous = current;
      current = current->next;
      free(previous->name);
      if (calendar->free_info_func && previous->info) {
        calendar->free_info_func(previous->info);
      }
      free(previous);
      calendar->total_events--;
    }
    /* Makes sure the linked list points to NULL since 
       there are no events for that day */
    calendar->events[day - 1] = NULL;
    return SUCCESS;
  }
    return FAILURE;
}


int destroy_calendar(Calendar *calendar){
  /* Removes every event,frees all memory that was dynamically allocated 
     for the calendar,and returns SUCCESS */
  if (calendar != NULL) {
        free(calendar->name);
        clear_calendar(calendar);
        free(calendar->events);
        free(calendar);
        return SUCCESS;
    }
    return FAILURE;
}

