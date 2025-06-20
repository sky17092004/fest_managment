#ifndef FEST_MANAGEMENT_H
#define FEST_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gtk/gtk.h>






// Function declarations
void displayVolunteers();
void registerVolunteer();
void remaining_budget();
void displaySponsors();
void registerSponsor();
void displayTickets();
void displayparticipants();
void display_budget();
void generateBudgetReport();
void invitation();
void display_events();
void add_events();
void edit_events();
void deleteEvent();
void displayRooms();
void bookRoom();
void unbookRoom();

// GTK main function
int gtk_admin_main(int argc, char *argv[]);

#endif /* FEST_MANAGEMENT_H */
