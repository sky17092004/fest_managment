#ifndef GTK_USER_INTERFACE_H
#define GTK_USER_INTERFACE_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void create_registration_window(const gchar *event_name);
void save_user_info(const gchar *name, const gchar *mobile_str, const gchar *mail_id);
void on_submit_clicked(GtkWidget *widget, gpointer user_data);
void on_event_selection_clicked(GtkWidget *widget, gpointer user_data);
void create_user_gui();
int user_main(int argc, char *argv[]);

#endif /* GTK_USER_INTERFACE_H */
