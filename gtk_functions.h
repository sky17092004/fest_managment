#ifndef GTK_FUNCTIONS_H
#define GTK_FUNCTIONS_H

#include <gtk/gtk.h>

void show_file_contents_window(const gchar *file_path);
void display_stalls(GtkWidget *widget, gpointer data);
void create_stall_input_window();
void book_stall(GtkWidget *widget, gpointer data);
void create_unbook_input_window();
void un_book_stall(GtkWidget *widget, gpointer data);
void show_message_window(GtkWidget *label);
void vendor_main();
typedef struct user {
    int id;
    char name[50];
    long long int mobile;
    char mail_id[30];
    char event[50];
} Guest;

void create_registration_window(const gchar *event_name);
void save_user_info(const gchar *name, const gchar *mobile_str, const gchar *mail_id);
void on_submit_clicked(GtkWidget *widget, gpointer user_data);
void on_event_selection_clicked(GtkWidget *widget, gpointer user_data);
void create_user_gui();

#endif /* GTK_FUNCTIONS_H */
