#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b23cs1024_b23cs1022_b23ph1029_b23ch1019_user.c"
#include "b23cs1024_b23cs1022_b23ph1029_b23ch1019_vendor.c"
#include "b23cs1024_b23cs1022_b23ph1029_b23ch1019_admin.c"
#include "gtk_user_interface.h"
#include "fest_management.h"
#include "vendor_management.h"


void on_user_button_clicked(GtkWidget *widget, gpointer data) {
    user_main(1,"b23cs1024_b23cs1022_b23ph1029_b23ch1019_user.c");
}

void on_vendor_button_clicked(GtkWidget *widget, gpointer data) {
    vendor_main();
}
void on_login_activate();

void on_admin_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *entry_username;
    GtkWidget *entry_password;
    gint result;

    // Create a new dialog window for entering credentials
    dialog = gtk_dialog_new_with_buttons("Admin Login", NULL, GTK_DIALOG_MODAL, "Login", GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Add label and entry widgets for username and password
    label = gtk_label_new("Enter your credentials:");
    gtk_container_add(GTK_CONTAINER(content_area), label);

    entry_username = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_username), "Username");
    gtk_container_add(GTK_CONTAINER(content_area), entry_username);

    entry_password = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_password), "Password");
    gtk_container_add(GTK_CONTAINER(content_area), entry_password);

    // Connect the "activate" signal of the password entry to the login callback function
    g_signal_connect(entry_password, "activate", G_CALLBACK(on_login_activate), dialog);

    gtk_widget_show_all(dialog);

    // Run the dialog and handle the response
    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        // The login callback function will handle the login process
    }

    // Destroy the dialog window
    gtk_widget_destroy(dialog);
}

void on_login_activate(GtkWidget *widget, gpointer data) {
    // Retrieve the dialog window
    GtkWidget *dialog = GTK_WIDGET(data);

    // Retrieve the username and password
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(gtk_container_get_children(GTK_CONTAINER(dialog))->next->data));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(widget));

    // Check if the credentials are correct
    if (strcmp(username, "GoodMarks") == 0 && strcmp(password, "1234") == 0) {
        // If correct, open the admin portal
        gtk_admin_main(1, "b23cs1024_b23cs1022_b23ph1029_b23ch1019_admin.c");
    } else {
        // If incorrect, show an error message
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid credentials");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }

    // Destroy the dialog window
    gtk_widget_destroy(dialog);
}



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_user;
    GtkWidget *button_vendor;
    GtkWidget *button_admin;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Portal Selection");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Center the window
     gtk_window_set_default_size(GTK_WINDOW(window), 600, 100);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    button_user = gtk_button_new_with_label("User Portal");
    g_signal_connect(button_user, "clicked", G_CALLBACK(user_main), NULL);
    gtk_widget_set_size_request(button_user, 200, 100); // Set button size
    gtk_grid_attach(GTK_GRID(grid), button_user, 0, 0, 1, 1);

    button_vendor = gtk_button_new_with_label("Vendor Portal");
    g_signal_connect(button_vendor, "clicked", G_CALLBACK(vendor_main), NULL);
    gtk_widget_set_size_request(button_vendor, 200, 50); // Set button size
    gtk_grid_attach(GTK_GRID(grid), button_vendor, 1, 0, 1, 1);

    button_admin = gtk_button_new_with_label("Admin Portal");
    g_signal_connect(button_admin, "clicked", G_CALLBACK(gtk_admin_main), NULL);
    gtk_widget_set_size_request(button_admin, 200, 50); // Set button size
    gtk_grid_attach(GTK_GRID(grid), button_admin, 2, 0, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
