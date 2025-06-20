#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mmsystem.h>
#include <windows.h>
void displayWelcomeMessage()
{
    printf("=========================================\n");
    printf("Welcome to Ignus Chatbot!\n");
    printf("=========================================\n\n");
}

void playSound(const char *filename)
{
    PlaySound(filename, NULL, SND_ASYNC | SND_FILENAME);
}

void stopSound()
{
    PlaySound(NULL, NULL, 0);
}

GtkWidget *window;        //globaly declare field
GtkWidget *entry_name;
GtkWidget *entry_mobile;
GtkWidget *entry_mail;

void on_submit_clicked(GtkWidget *widget, gpointer user_data);           //all function
void save_user_info(const gchar *name, const gchar *mobile_str, const gchar *mail_id);
void create_registration_window(const gchar *event_name);
void create_user_gui();
void open_terminal();

typedef struct user {
    int id;
    char name[50];
    long long int mobile;
    char mail_id[30];
    char event[50];           // Added event field to the struct
} Guest;






void create_registration_window(const gchar *event_name) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label_name;
    GtkWidget *label_mobile;
    GtkWidget *label_mail;
    GtkWidget *btn_submit;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), event_name);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    label_name = gtk_label_new("Name:");
    entry_name = gtk_entry_new();                             //like a loop to create new widgets
    gtk_box_pack_start(GTK_BOX(vbox), label_name, FALSE, FALSE, 0);       //label name
    gtk_box_pack_start(GTK_BOX(vbox), entry_name, FALSE, FALSE, 0);

    label_mobile = gtk_label_new("Mobile:");
    entry_mobile = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), label_mobile, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_mobile, FALSE, FALSE, 0);

    label_mail = gtk_label_new("Mail ID:");
    entry_mail = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), label_mail, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_mail, FALSE, FALSE, 0);

    btn_submit = gtk_button_new_with_label("Submit");
    g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_submit_clicked), (gpointer)event_name);     //after submit
    gtk_box_pack_start(GTK_BOX(vbox), btn_submit, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
}

void save_user_info(const gchar *name, const gchar *mobile_str, const gchar *mail_id) {
    FILE *file = fopen("text_files/guests.txt", "a");
    if (file != NULL) {
        int id = rand() % 100000; // Generate a random ID
        fprintf(file, "%d,%s,%s,%s\n", id, name, mobile_str, mail_id);
        fclose(file);
    } else {
        printf("Error opening file for writing!\n");
    }
}

void on_submit_clicked(GtkWidget *widget, gpointer user_data) {
    const gchar *event_name = (const gchar *)user_data;           // Get the event name passed from the button click

                                                                        // Retrieve user input from the entry fields
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const gchar *mobile_str = gtk_entry_get_text(GTK_ENTRY(entry_mobile));     //get all information
    const gchar *mail_id = gtk_entry_get_text(GTK_ENTRY(entry_mail));

                                                                // Convert mobile number from string to long long int
    long long int mobile = atoll(mobile_str);

                                                                      // Save user information to a file
    save_user_info(name, mobile_str, mail_id);

                                                                        // Save event registration to another file
    FILE *registration_file = fopen("text_files/registration.txt", "a");
    if (registration_file != NULL) {
        fprintf(registration_file, "%s,%s\n", name, event_name);
        fclose(registration_file);
    } else {
        printf("Error opening file for writing!\n");
    }

                                                                                // Hide the window after submission
    gtk_widget_hide(gtk_widget_get_toplevel(GTK_WIDGET(widget)));

                                                                       // Open a new window to show the purchased events
    GtkWidget *window_purchased_events = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_purchased_events), "Purchased Events");
    gtk_window_set_default_size(GTK_WINDOW(window_purchased_events), 300, 200);

                                                                                // Read the contents of the guests.txt file and display them in the new window
    FILE *file = fopen("text_files/guests.txt", "r");
    if (file != NULL) {
        GtkWidget *label_purchased_events = gtk_label_new(NULL);
        gchar *events_text = g_malloc0(sizeof(gchar) * 500);              // Allocate memory for events_text

        while (fgets(events_text, 500, file) != NULL) {
            gtk_label_set_text(GTK_LABEL(label_purchased_events), events_text);
        }

        gtk_container_add(GTK_CONTAINER(window_purchased_events), label_purchased_events);
        fclose(file);
    } else {
        GtkWidget *label_no_events = gtk_label_new("No events purchased yet.");
        gtk_container_add(GTK_CONTAINER(window_purchased_events), label_no_events);
    }

    gtk_widget_show_all(window_purchased_events);
}

void on_event_selection_clicked(GtkWidget *widget, gpointer user_data) {
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(widget));

    if (strcmp(button_label, "Event Registration") == 0) {
        // Open window for event registration
        GtkWidget *window_event_registration;
        GtkWidget *vbox;
        GtkWidget *btn_solo_dancing;
        GtkWidget *btn_mr_and_mrs_ignus;
        GtkWidget *btn_standup_comedy;
        GtkWidget *btn_solo_singing;
        GtkWidget *btn_tshirt_painting;

        window_event_registration = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window_event_registration), "Event Registration");
        gtk_window_set_default_size(GTK_WINDOW(window_event_registration), 300, 200);

        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_container_add(GTK_CONTAINER(window_event_registration), vbox);

        // Create buttons for each event option
        btn_solo_dancing = gtk_button_new_with_label("Solo Dancing");
        btn_mr_and_mrs_ignus = gtk_button_new_with_label("Mr and Mrs Ignus");
        btn_standup_comedy = gtk_button_new_with_label("Standup Comedy");
        btn_solo_singing = gtk_button_new_with_label("Solo Singing");
        btn_tshirt_painting = gtk_button_new_with_label("Tshirt Painting");

        g_signal_connect(btn_solo_dancing, "clicked", G_CALLBACK(on_event_selection_clicked), "Solo Dancing");
        g_signal_connect(btn_mr_and_mrs_ignus, "clicked", G_CALLBACK(on_event_selection_clicked), "Mr and Mrs Ignus");
        g_signal_connect(btn_standup_comedy , "clicked", G_CALLBACK(on_event_selection_clicked), "Standup Comedy");
        g_signal_connect(btn_solo_singing, "clicked", G_CALLBACK(on_event_selection_clicked), "Solo Singing");
        g_signal_connect(btn_tshirt_painting, "clicked", G_CALLBACK(on_event_selection_clicked), "Tshirt Painting");

                                                                                 // Pack buttons into the vbox
        gtk_box_pack_start(GTK_BOX(vbox), btn_solo_dancing, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), btn_mr_and_mrs_ignus, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), btn_standup_comedy, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), btn_solo_singing, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), btn_tshirt_painting, FALSE, FALSE, 0);

        // Show all widgets
        gtk_widget_show_all(window_event_registration);
    } else {
                                                                // Create the registration window for the selected event
        create_registration_window(button_label);
    }
}

void create_user_gui() {
    GtkWidget *vbox;
    GtkWidget *btn_purchase_pronite;
    GtkWidget *btn_event_registration;
    GtkWidget *btn_chat_bot; // New button for Chat Bot

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "User Interface");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    btn_purchase_pronite = gtk_button_new_with_label("Purchase Pronite Ticket");
    btn_event_registration = gtk_button_new_with_label("Event Registration");
    btn_chat_bot = gtk_button_new_with_label("Chat Bot");                         // Create Chat Bot button

    g_signal_connect(btn_purchase_pronite, "clicked", G_CALLBACK(on_event_selection_clicked), NULL);
    g_signal_connect(btn_event_registration, "clicked", G_CALLBACK(on_event_selection_clicked), NULL);
    g_signal_connect(btn_chat_bot, "clicked", G_CALLBACK(open_terminal), NULL);    // Connect Chat Bot button to open_terminal function

    gtk_box_pack_start(GTK_BOX(vbox), btn_purchase_pronite, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn_event_registration, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn_chat_bot, FALSE, FALSE, 0);           // Add Chat Bot button to the vbox

    gtk_widget_show_all(window);
}

void open_terminal() {
    char userInput[100];
    displayWelcomeMessage();

    while (1)
    {
        printf("You can ask for information or the event schedule.\n");
        printf("Enter your query: ");
        gets(userInput);

        stopSound(); // Stop any currently playing sound

        if (strstr(userInput, "info") != NULL || strstr(userInput, "information") != NULL)
        {
            printf("\nIGNUS, the much anticipated annual socio-cultural fest of IIT Jodhpur, is now back, after three years.\n");
            printf("Ignus celebrates art, culture, and pluralism. It provides a stage for the creative and intellectual minds from across the country to showcase their incredible talent and creativity through art and culture.\n");
            printf("For many years, the Indian Institute of Technology, Jodhpur has been a forerunner in technical education in Rajasthan. Since its inception in 2008, the institute has grown by leaps and bounds, constantly striving for excellence in academics and management.\n\n");
            playSound("ignusinfo.wav");
        }
        else if (strstr(userInput, "schedule") != NULL || strstr(userInput, "events") != NULL)
        {
            printf("\nHere's the event schedule for Ignus, the cultural fest at IIT Jodhpur:\n\n");

            printf("Day 1:\n"
                   "Morning: Registration for Mr. and Ms. Ignus starts at 9:00 AM.\n"
                   "Afternoon: Solo dance competition at 1:00 PM, singing competition at 3:00 PM.\n"
                   "Evening: T-shirt painting workshop from 5:00 PM to 7:00 PM.\n\n");

            printf("Day 2:\n"
                   "Morning: Mr. and Ms. Ignus preliminary rounds begin at 10:00 AM.\n"
                   "Afternoon: Group dance competition at 1:00 PM, instrumental music competition at 3:00 PM.\n"
                   "Evening: Cultural performances by guest artists from 5:00 PM onwards.\n\n");

            printf("Day 3:\n"
                   "Morning: Mr. and Ms. Ignus final rounds start at 10:00 AM.\n"
                   "Afternoon: Fashion show at 1:00 PM, stand-up comedy competition at 3:00 PM.\n"
                   "Evening: Award ceremony and closing ceremony at 6:00 PM, followed by a DJ night.\n");
            playSound("ignusschedule.wav");
        }
        else if (strstr(userInput, "guests") != NULL || strstr(userInput, "performers") != NULL)
        {
            printf("\nWe have an exciting lineup of guest artists and performers at Ignus this year!\n");
            printf("Stay tuned for announcements regarding the guest artists and their performances.\n\n");
            playSound("guest.wav");
        }
        else if (strstr(userInput, "workshops") != NULL || strstr(userInput, "workshop") != NULL)
        {
            printf("\nIgnus offers a variety of workshops to enhance your skills and creativity.\n");
            printf("Stay updated on our website or social media for workshop schedules and registration details.\n\n");
            playSound("workshop.wav");
        }
        else if (strstr(userInput, "tickets") != NULL || strstr(userInput, "pass") != NULL)
        {
            printf("\nYou can go to the ticket portal of this app from the user menu where you can book tickets.\n");
            playSound("tickets.wav");
        }
        else if (strstr(userInput, "register") != NULL || strstr(userInput, "participate") != NULL)
        {
            printf("\nWe welcome all the registrations and participants to be part of Ignus!\n");
            printf("You can register yourself for the events of the fest from the user menu.\n\n");
            playSound("event reg.wav");
        }
        else if (strstr(userInput, "accommodation") != NULL || strstr(userInput, "stay") != NULL)
        {
            printf("\nFor accommodation during Ignus, we have tie-ups with nearby hotels offering special rates for participants.\n");
            printf("Contact our accommodation team for booking and assistance.\n\n");
            playSound("accom.wav");
        }
        else if (strstr(userInput, "contact") != NULL || strstr(userInput, "reach") != NULL)
        {
            printf("\nYou can reach us via email at contact@ignus.co.in or call our helpline at +91-2876543210.\n");
            printf("Our team is available to assist you with any queries or information.\n\n");
            playSound("contact.wav");
        }
        else if (strstr(userInput, "sponsor") != NULL || strstr(userInput, "sponsorship") != NULL)
        {
            printf("\nIgnus offers various sponsorship opportunities for businesses and organizations.\n");
            printf("Contact our sponsorship team to explore partnership options and benefits.\n\n");
            playSound("sponsor.wav");
        }
        else if (strcmp(userInput, "exit") == 0)
        {
            break;
        }
        else if (strcmp(userInput, "stop") == 0)
        {
            stopSound();
        }
        else
        {
            printf("\nSorry, I didn't understand your query. Please try again or type 'exit' to end.\n");
        }
    }

    return 0;
}


int user_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    create_user_gui();

    gtk_main();

    return 0;
}
