#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void create_stall_input_window();
void book_stall(GtkWidget *widget, gpointer data);
void un_book_stall();
void show_message_window(GtkWidget *label);
void vendor_main();
void display_stalls(GtkWidget *widget, gpointer data);

// Global variables
GtkWidget *stall_window = NULL;
GtkWidget *vendor_entry = NULL;
GtkWidget *message_window = NULL;

void show_file_contents_window(const gchar *file_path) {
    GtkWidget *file_window;
    GtkWidget *scrolled_window;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;

    // Create the window
    file_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(file_window), "Stalls File Contents");
    gtk_window_set_default_size(GTK_WINDOW(file_window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(file_window), 10);

    // Create scrolled window
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Create text view
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);

    // Get text buffer from text view
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Load file contents into buffer
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Error opening file: %s\n", file_path);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Convert line to UTF-8 and insert into buffer
        gchar *utf8_line = g_locale_to_utf8(line, -1, NULL, NULL, NULL);
        if (utf8_line) {
            gtk_text_buffer_insert_at_cursor(buffer, utf8_line, -1);
            g_free(utf8_line);
        }
    }
    fclose(file);

    // Add text view to scrolled window
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Add scrolled window to file window
    gtk_container_add(GTK_CONTAINER(file_window), scrolled_window);

    // Show all widgets
    gtk_widget_show_all(file_window);
}


void display_stalls(GtkWidget *widget, gpointer data) {
    const gchar *file_path = "text_files/stalls.txt";
    show_file_contents_window(file_path);
}

void create_stall_input_window() {
    // Create the window
    stall_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(stall_window), "Book Stall");
    gtk_container_set_border_width(GTK_CONTAINER(stall_window), 10);

    // Create labels and entry fields
    GtkWidget *stall_label = gtk_label_new("Enter Stall Number:");
    GtkWidget *vendor_label = gtk_label_new("Enter Your Name:");
    vendor_entry = gtk_entry_new();
    GtkWidget *stall_entry = gtk_entry_new();

    // Create button
    GtkWidget *button = gtk_button_new_with_label("Book");
    g_signal_connect(button, "clicked", G_CALLBACK(book_stall), stall_entry);

    // Create layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), stall_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), stall_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), vendor_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), vendor_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 5);

    // Add layout to window and show window
    gtk_container_add(GTK_CONTAINER(stall_window), vbox);
    gtk_widget_show_all(stall_window);
}

void book_stall(GtkWidget *widget, gpointer data) {
    // Get the stall number and vendor name from the entry fields
    const gchar *stall_text = gtk_entry_get_text(GTK_ENTRY(data));
    const gchar *vendor_name = gtk_entry_get_text(GTK_ENTRY(vendor_entry));

    // Check if the stall number is valid
    int stall_number = atoi(stall_text);
    if (stall_number <= 0) {
        // Display error message for invalid stall number
        GtkWidget *label = gtk_label_new("Invalid stall number. Please enter a positive integer.");
        show_message_window(label);
        return;
    }

    // Update the stalls file with the newly booked stall
    FILE *file = fopen("text_files/stalls.txt", "r");
    if (!file) {
        printf("Error opening stalls.txt for reading.\n");
        exit(1);
    }

    FILE *tempFile = fopen("text_files/temp.txt", "w");
    if (!tempFile) {
        printf("Error opening temp.txt for writing.\n");
        fclose(file);
        return;
    }

    char str[10], status[50];
    int num;
    int stall_found = 0;
    while (fscanf(file, "%s %d %49[^\n]\n", str, &num, status) != EOF) {
        if (num == stall_number) {
            if (strcmp(status, "unbooked") == 0) {
                // Book the stall with the vendor's name
                fprintf(tempFile, "%s %d %s\n", str, num, vendor_name);
                stall_found = 1;
            } else {
                // Stall is already booked
                stall_found = -1;
            }
        } else {
            // Copy the existing stall details to the temporary file
            fprintf(tempFile, "%s %d %s\n", str, num, status);
        }
    }
    fclose(file);
    fclose(tempFile);

    // Replace the original stalls file with the temporary file
    remove("text_files/stalls.txt");
    rename("text_files/temp.txt", "text_files/stalls.txt");

    // Display message in a new window
    if (stall_found == 1) {
        // Stall has been successfully booked
        GtkWidget *label = gtk_label_new("Stall has been successfully booked.");
        show_message_window(label);
    } else if (stall_found == -1) {
        // Stall is already booked
        GtkWidget *label = gtk_label_new("Stall is already booked. Please select another.");
        show_message_window(label);
    }

    // Close the stall input window
    gtk_widget_destroy(stall_window);
}


void un_book_stall() {

    FILE *file = fopen("text_files/stalls.txt","r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\033[1;34m");
    fflush(stdin);
    int stall_number;
    printf("Enter the stall number you want to unbook: ");
    scanf("%d", &stall_number);
    FILE *tempFile = fopen("text_files/temp.txt", "w");
    if (tempFile==NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    char str[10], status[50];
    int num,count=0;
    while (fscanf(file, "%s %d %49[^\n]\n",str,&num,status)!=EOF) {
        if (num == stall_number && strcmp(status, "unbooked")!=0) {
            fprintf(tempFile,"%s %d %s\n",str,num,"unbooked");
        }
        else if (num == stall_number && strcmp(status, "unbooked")==0) {
            fprintf(tempFile,"%s %d %s\n",str,num,status);
            count=1;
        }
        else {
            fprintf(tempFile,"%s %d %s\n",str,num,status);
        }
    }
    if(count==1){
        printf("\033[1;31m");
        printf("\nStall is already Unbooked. Please select another stall to Unbook.\n\n");
    }
    else{
        printf("\033[1;32m");
        printf("\nStall has been successfully Unbooked.\n\n");
        printf("\033[0m");
    }

    fclose(file);
    fclose(tempFile);
    remove("text_files/stalls.txt");
    rename("text_files/temp.txt","text_files/stalls.txt");
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
}

void show_message_window(GtkWidget *label) {
    if (message_window != NULL) {
        gtk_widget_destroy(message_window);
    }

    message_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(message_window), "Message");
    gtk_window_set_default_size(GTK_WINDOW(message_window), 200, 100);
    gtk_container_set_border_width(GTK_CONTAINER(message_window), 10);

    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    g_signal_connect(ok_button, "clicked", G_CALLBACK(gtk_widget_destroy), message_window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(vbox), ok_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(message_window), vbox);
    gtk_widget_show_all(message_window);
}

void vendor_main() {
    GtkWidget *window;
    GtkWidget *display_button, *book_button, *unbook_button;
    GtkWidget *vbox;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Vendor Main Menu");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    display_button = gtk_button_new_with_label("Display Stalls");
    book_button = gtk_button_new_with_label("Book Stall");
    unbook_button = gtk_button_new_with_label("Un-book Stall");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), display_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), book_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), unbook_button, TRUE, TRUE, 0);

    g_signal_connect(display_button, "clicked", G_CALLBACK(display_stalls), NULL);
    g_signal_connect(book_button, "clicked", G_CALLBACK(create_stall_input_window), NULL);
    g_signal_connect(unbook_button, "clicked", G_CALLBACK(un_book_stall), NULL);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();
}


