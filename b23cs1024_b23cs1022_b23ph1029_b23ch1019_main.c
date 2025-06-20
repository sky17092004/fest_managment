#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b23cs1024_b23cs1022_b23ph1029_b23ch1019_user.c"
#include "b23cs1024_b23cs1022_b23ph1029_b23ch1019_vendor.c"
#include "b23cs1024_b23cs1022_b23ph1029_b23ch1019_admin.c"
#include "gtk_user_interface.h"
#include "fest_management.h"
#include "vendor_management.h"             //all function




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
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);                                   // Center the window
     gtk_window_set_default_size(GTK_WINDOW(window), 600, 100);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    button_user = gtk_button_new_with_label("User Portal");
    g_signal_connect(button_user, "clicked", G_CALLBACK(user_main), NULL);
    gtk_widget_set_size_request(button_user, 200, 100);                        // Set button size
    gtk_grid_attach(GTK_GRID(grid), button_user, 0, 0, 1, 1);

    button_vendor = gtk_button_new_with_label("Vendor Portal");
    g_signal_connect(button_vendor, "clicked", G_CALLBACK(vendor_main), NULL);
    gtk_widget_set_size_request(button_vendor, 200, 100); // Set button size
    gtk_grid_attach(GTK_GRID(grid), button_vendor, 1, 0, 1, 1);                   //row,colums,span

    button_admin = gtk_button_new_with_label("Admin Portal");
    g_signal_connect(button_admin, "clicked", G_CALLBACK(gtk_admin_main), NULL);
    gtk_widget_set_size_request(button_admin, 200, 100); // Set button size
    gtk_grid_attach(GTK_GRID(grid), button_admin, 2, 0, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
