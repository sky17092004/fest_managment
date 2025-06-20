#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *window;
GtkWidget *entry;

void create_user_gui();
void on_entry_activate(GtkWidget *entry, gpointer text_view);
gchar *process_user_input(const gchar *userInput);

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    create_user_gui();
    gtk_main();
    return 0;
}

void create_user_gui() {
    GtkWidget *vbox;
    GtkWidget *scrolled_window;
    GtkWidget *text_view;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ChatBot");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, 300, 200);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
g_signal_connect(entry, "activate", G_CALLBACK(on_entry_activate), text_view);

    gtk_widget_show_all(window);
}

void on_entry_activate(GtkWidget *entry, gpointer text_view) {
    const gchar *userInput = gtk_entry_get_text(GTK_ENTRY(entry));
    gchar *response = process_user_input(userInput);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, "You: ", -1);
    gtk_text_buffer_insert(buffer, &iter, userInput, -1);
    gtk_text_buffer_insert(buffer, &iter, "\n", -1);
    gtk_text_buffer_insert(buffer, &iter, "ChatBot: ", -1);
    gtk_text_buffer_insert(buffer, &iter, response, -1);
    gtk_text_buffer_insert(buffer, &iter, "\n\n", -1);

    gtk_entry_set_text(GTK_ENTRY(entry), ""); // Clear the entry after processing

    g_free(response);
}


gchar *process_user_input(const gchar *userInput) {
    gchar *response;
    if (strstr(userInput, "hello") != NULL || strstr(userInput, "hi") != NULL) {
        response = g_strdup("Hello! How can I assist you?");
    } else if (strstr(userInput, "how are you") != NULL) {
        response = g_strdup("I'm a chatbot. I'm always here to help.");
    } else if (strstr(userInput, "thank you") != NULL || strstr(userInput, "thanks") != NULL) {
        response = g_strdup("You're welcome!");
    } else {
        response = g_strdup("Sorry, I didn't understand your query.");
    }
    return response;
}
