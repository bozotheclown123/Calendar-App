#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

/* Description here: This test checks if the function can initialize, print, 
   and destroy the calendar  */
static int test1() {
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }
    
   return FAILURE;
}

/* This test checks if events are added and if the calendar is destroyed properly. */
static int test2() {
    Calendar *calendar;
    int days = 31;

   if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar) == SUCCESS) {

      if (add_event(calendar, "Halloween", 1800, 180, NULL, 1) == SUCCESS &&
          add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) == SUCCESS){
             destroy_calendar(calendar);
          } 
            return SUCCESS;
   }
   return FAILURE;
}
   

/* This test checks if events are added and printed properly. */
static int test3() {
    Calendar *calendar;
    int days = 31;

      if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
         if (print_calendar(calendar, stdout, 1) == SUCCESS){
            print_calendar(calendar, stdout, 1);
            destroy_calendar(calendar);
         }
         return SUCCESS;
      }
   return FAILURE;
}

/* This tests whether clear_day functions properly. */
static int test4() {
   Calendar *calendar;
   int days = 31;

      if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Halo 6 Release", 1700, 60, NULL, 1);
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      add_event(calendar, "Bowling Tournament", 1100, 90, NULL, 1);
      print_calendar(calendar, stdout, 1);
         if (clear_day(calendar, 1) == SUCCESS){
            print_calendar(calendar, stdout, 1);
            destroy_calendar(calendar);
         }
         return SUCCESS;
      }
   return FAILURE;
}

/* This test checks whether remove event works properly */
static int test5(){
   Calendar *calendar;
   int days = 31;

      if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (remove_event(calendar, "Dentist Appointment") == SUCCESS){
            print_calendar(calendar, stdout, 1);
            destroy_calendar(calendar);
         }
         return SUCCESS;
      }
   return FAILURE;
}

/* This test checks whether remove event works properly */
static int test6(){
   Calendar *calendar;
   int days = 31;

      if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (remove_event(calendar, "Pool Party") == FAILURE){
            print_calendar(calendar, stdout, 1);
            destroy_calendar(calendar);
         }
         return SUCCESS;
      } 
   return FAILURE;
}

/* This test checks if find_event works properly */
static int test7(){
   Calendar *calendar;
   int days = 31;
   Event *check;

      if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (find_event(calendar, "Casino Sesh", &check ) == FAILURE) {
             destroy_calendar(calendar);
            return SUCCESS;
         }
      }
      return FAILURE;
}

/* This test checks if find_event works properly */
static int test8(){
   Calendar *calendar;
   int days = 31;
   Event *check;

      if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (find_event(calendar, "Barbaque Cookout", &check ) == SUCCESS){
             destroy_calendar(calendar);
            return SUCCESS;
         }
      }
      return FAILURE;
}

/* This test checks if find_event_in_day works properly */
static int test9(){
   Calendar *calendar;
   int days = 31;
   Event *check;

       if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (find_event_in_day(calendar, "Barbaque Cookout", 2, &check ) == SUCCESS){
             destroy_calendar(calendar);
            return SUCCESS;
         }
      }
      return FAILURE;
}

/* This test checks if find_event_in_day works properly */
static int test10(){
   Calendar *calendar;
   int days = 31;
   Event *check;

       if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (find_event_in_day(calendar, "Movie Night", 2, &check ) == FAILURE){
             destroy_calendar(calendar);
            return SUCCESS;
         }
      }
      return FAILURE;
}

/* This test checks if clear_calendar works properly */
static int test11(){
   Calendar *calendar;
   int days = 31;

       if (init_calendar("October Calendar", days, comp_minutes, NULL, &calendar)  == SUCCESS) { 
      add_event(calendar, "Halloween", 1800, 180, NULL, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
         if (clear_calendar(calendar) == SUCCESS){
            print_calendar(calendar, stdout, 1);
            destroy_calendar(calendar);
            return SUCCESS;
         }
      }
      return FAILURE;
}

/*static int test12(){
   Calendar *calendar;
   int days = 31;
   char *info = "Spooky Spider Skeleton";

      init_calendar("October Calendar", days, comp_minutes, NULL, &calendar);
      add_event(calendar, "Halloween", 1800, 180, *info, 1);
      add_event(calendar, "Dentist Appointment", 1200, 60, NULL, 2) ;
      add_event(calendar, "Barbaque Cookout", 1300, 60, NULL, 2) ;
      add_event(calendar, "Movie Night", 300, 120, NULL, 5);
      print_calendar(calendar, stdout, 1);
      printf("%s\n,", get_event_info(calendar, "Halloween"));
      return SUCCESS;

}*/


int main() {
   int result = SUCCESS;
   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE) result = FAILURE;
   if (test2() == FAILURE) result = FAILURE;
   if (test3() == FAILURE) result = FAILURE;
   if (test4() == FAILURE) result = FAILURE;
   if (test5() == FAILURE) result = FAILURE;
   if (test6() == FAILURE) result = FAILURE;
   if (test7() == FAILURE) result = FAILURE;
   if (test8() == FAILURE) result = FAILURE;
   if (test9() == FAILURE) result = FAILURE;
   if (test10() == FAILURE) result = FAILURE;
   if (test11() == FAILURE) result = FAILURE;
  
   if ((result = SUCCESS)){
      printf("You failed!\n");
   } else{
      printf("You passed!\n");
   }

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
  
   return EXIT_SUCCESS;
}
