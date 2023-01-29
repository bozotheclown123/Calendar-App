# Calendar App
The calendar application allows events to be scheduled on specific days. A calendar is defined by the following structs:

typedef struct event { <br />
char *name; <br />
int start_time, duration_minutes; <br />
void *info; <br />
struct event *next; <br />
} Event; 

typedef struct calendar { <br />
char *name; <br />
Event **events; <br />
int days, total_events; <br />
int (*comp_func) (const void *ptr1, const void *ptr2); <br />
void (*free_info_func) (void *ptr); <br />
} Calendar;

An Event struct represents an event. The fields of the Event struct maintain a pointer to the event’s name, the
start time (military time), the duration in minutes, a pointer to information about the event, and a pointer to
another Event struct. The last field is used to place the Event struct in a linked list.

The Calendar struct keeps track of events by using an array of linked lists of Event structs. Field name points
to the calendar’s name. Field events points to an array, each entry of which points to a linked list of events
scheduled for a particular day. The array has an entry for every day of the calender. Field days indicates the
number of days in the calendar. Field total events indicates the number of events in the calendar.

Field comp func points to a comparison function (similar to compareTo in Java) for events. The events for
each day are kept in increasing sorted order according to this function. Different comparison functions enable
different sorting criteria: for example, events sorted by duration or by name.

Field free info func points to a function used to free the information pointed to by the info field of an event.
This allows the information associated with an event to have arbitrary structure, for example, a struct, a string,
an array, anything. When an event is removed, this function is called to free the memory that stores the event’s
information.

The events in a calendar are uniquely identified by their names. An attempt to add an event fails if the
event’s name equals the name of an event already in the calendar.
