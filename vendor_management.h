#ifndef VENDOR_MANAGEMENT_H
#define VENDOR_MANAGEMENT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void show_file_contents_window(const gchar *file_path);
void display_stalls(GtkWidget *widget, gpointer data);
void create_stall_input_window();
void book_stall(GtkWidget *widget, gpointer data);
void un_book_stall();
void show_message_window(GtkWidget *label);
void vendor_main();


#endif /* VENDOR_MANAGEMENT_H */
