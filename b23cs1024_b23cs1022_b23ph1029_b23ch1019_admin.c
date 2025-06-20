#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

 #include <gtk/gtk.h>
float initial_expense=0,budget = 1000000;
char host_name[100] = "Japneet Singh";
char fest_name[100] = "Ignus";
char customer_care[15] ="+918837856693";
char venue[100] = "IIT";
char start_date[100] = "19-04-2024";
char end_date[100] = "22-04-2024";
int event_count=0;

struct Sponsor {
    char company[100];
    long long int contactPerson;
    char email[50];
    float paymentAmount;

};

struct Expense {
    char category[50];
    float amount;
};

struct Event {
    char name[100];
    char date[20];
    char time[20];
    char performer[100];
};
 struct LHC_rooms{
    int room_no;
    bool in_use;
 };
 struct LHC_rooms rooms[10];
 int LHC_rooms[10];
int room_count =0;


struct Volunteer {
    char name[50];
    char mail_id[50];
    long long int mobile;
    char preferredRole[100];
};
void displayVolunteers() {
    system("cls");
    printf("\033[33m");
    FILE *file = fopen("text_files/volunteers.txt","r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    char line[100];
    printf("Volunteers:\n");
    while (fgets(line, sizeof(line),file)) {
        printf("%s",line);
    }
    fclose(file);
    printf("\nPress \"Enter\" to continue.\n");
    fflush(stdin);
    getchar();
}
void registerVolunteer() {
    system("cls");
    struct Volunteer volunteer;
    printf("\033[34m");
    FILE *fptr = fopen("text_files\\volunteers.txt","a");
    printf("Enter Name: ");
    fflush(stdin);
    fgets(volunteer.name,50,stdin);
    if(strlen(volunteer.name)!=49){
        volunteer.name[strlen(volunteer.name)-1] = '\0';
    }
    printf("Enter mobile: ");
    scanf("%lld",&volunteer.mobile);
    printf("Enter Mail Id: ");
    scanf("%s",volunteer.mail_id);
    printf("Enter Preferred Role: ");
    scanf("%s",volunteer.preferredRole);
    fprintf(fptr,"%s,%lld,%s,%s",volunteer.name,volunteer.mobile,volunteer.mail_id,volunteer.preferredRole);
    fputc('\n',fptr);
    fclose(fptr);
}

void remaining_budget(){
 printf("Budget of the fest :%f",budget);
}

void displaySponsors() {
    system("cls");
    printf("\033[33m");
    FILE *file = fopen("text_files/sponsors.txt","r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    char line[100];
    printf("Sponsors:\n");
    while (fgets(line, sizeof(line),file)) {
        printf("%s",line);
    }
    fclose(file);
    printf("\nPress \"Enter\" to continue.\n");
    fflush(stdin);
    getchar();
}
void registerSponsor( ) {

    system("cls");
    struct Sponsor sponsor;
    printf("\033[34m");
    FILE *fptr = fopen("text_files\\sponsors.txt","a");
    printf("Enter Name: ");
    fflush(stdin);
    fgets(sponsor.company,100,stdin);
    if(strlen(sponsor.company)!=99){
        sponsor.company[strlen(sponsor.company)-1] = '\0';
    }
    printf("Enter mobile: ");
    scanf("%lld",&sponsor.contactPerson);
    printf("Enter Mail Id: ");
    scanf("%s",sponsor.email);
    printf("Enter Payment Amount: ");
    scanf("%f",&sponsor.paymentAmount);
    budget += sponsor.paymentAmount;
    fprintf(fptr,"%s,%lld,%s,%.2f",sponsor.company,sponsor.contactPerson,sponsor.email,sponsor.paymentAmount);
    fputc('\n',fptr);
    fclose(fptr);
}

void displayTickets() {
    system("cls");
    printf("\033[33m");
    FILE *file = fopen("text_files/guests.txt","r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    char line[100];
    printf("Tickets:\n");
    while (fgets(line, sizeof(line),file)) {
        printf("%s",line);
    }
    fclose(file);
    printf("\nPress \"Enter\" to continue.\n");
    fflush(stdin);
    getchar();
}


void displayparticipants(){
    system("cls");
    printf("\033[33m");
    FILE *file = fopen("text_files/registration.txt","r");
    if (!file) {
        printf("Error opening file.\n");
        getchar();
        return;
    }
    char line[100];
    printf("Tickets:\n");
    while (fgets(line, sizeof(line),file)) {
        printf("%s",line);
    }
    fclose(file);
    printf("\nPress \"Enter\" to continue.\n");
    fflush(stdin);
    getchar();
}
void display_budget() {
    system("cls");
    printf("\033[33m");
    FILE *file = fopen("text_files/BUDGET.txt","r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    char line[100];
    printf("Tickets:\n");
    while (fgets(line, sizeof(line),file)) {
        printf("%s",line);
    }
    fclose(file);
    printf("\nPress \"Enter\" to continue.\n");
    fflush(stdin);
    getchar();
}

int i=1;
void generateBudgetReport() {
    system("cls");
    printf("\033[36m");
    struct Expense expenses;
    printf("\nEnter the category of expense : ");
     fflush(stdin);
    fgets(expenses.category,100,stdin);
    if(strlen(expenses.category)!=99){
        expenses.category[strlen(expenses.category)-1] = '\0';
    }
    printf("Enter the  amount of expense :");
    scanf("%f",&expenses.amount);
    if(expenses.amount>budget){
        fflush(stdin);
        printf("Cannot spend more than BUDGET.\nPress \"Enter\" to continue.");
        getchar();
        return;
    }
    initial_expense += expenses.amount;

    system("cls");
    printf("               Budget Report               \n");
    printf("Initial Fest Budget: %f\n",budget);
    printf("Expense Number: %d\nCategory: %s\nAmount: %f\n",i,expenses.category,expenses.amount);
    printf("Total Expenses: %f\n",initial_expense);
    printf("Remaining Budget: %f\n", budget - expenses.amount);
    fflush(stdin);
    printf("Successfully Saved.\nPress \"Enter\" to continue.");
    getchar();
    FILE *ptr;
    ptr =fopen("text_files\\BUDGET.txt","a");
    if (!ptr) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(ptr,"\n\n               Budget Report               \n");
    fprintf(ptr, "Starting Budget: %f\n",budget);
    fprintf(ptr, "Category of the expense : %s\n",expenses.category);
    fprintf(ptr ,"Amount of the expense : %f\n\n",expenses.amount);
    fprintf(ptr,"Total Expenses :%f\n",initial_expense);
    fprintf(ptr,"Remainig Budget : %f\n",budget - expenses.amount);
    fputc('\n',ptr);
    fclose(ptr);
    i++;
    budget = budget - expenses.amount;
}


void invitation(){
    system("cls");
    printf("\033[36m");
    FILE *ptr;
    ptr= fopen("invitation.txt","a");
    fprintf(ptr,"Invitation to Attend %s\n", fest_name);
    fprintf(ptr,"Venue: %s\n", venue);
    fprintf(ptr," Start Date: %s\n", start_date);
    fprintf(ptr,"End Date: %s\n" , end_date);
    fprintf(ptr,"Hosted by: %s\n", host_name);
    fprintf(ptr,"In case of any difficulty , please contact :%s\n", customer_care);

    fprintf(ptr,"You are cordially invited to join us for a fest of celebration and cultural activities.\n");

     fclose(ptr);
}
void display_events(){
    system("cls");
    printf("\033[36m");
    printf("          Events in The Fest          \n\n");
    FILE *fptr = fopen("text_files\\event.txt","r");
    if(fptr==NULL){
        perror("Error Opening File");
        return;
    }
    char ch=fgetc(fptr);
    while(ch!=EOF){
        printf("%c",ch);
        ch=fgetc(fptr);
    }
    fclose(fptr);
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
}
void add_events(){
    system("cls");
    printf("\033[36m");
    struct Event events;
    printf("     Enter Event Details :     ");
    printf("\nEnter name of the event : ");
    fflush(stdin);
    fgets(events.name,100,stdin);
    if(strlen(events.name)!=99){
        events.name[strlen(events.name)-1] = '\0';
    }
    printf("Enter date of the event(DD/MM/YYYY) : ");
    scanf("%s" ,events.date);
    printf("Enter the timings of the event(HH:MM:SS) : ");
    scanf("%s" ,events.time);
    printf("Enter performer of the event : " );
    fflush(stdin);
    fgets(events.performer,100,stdin);
    if(strlen(events.performer)!=99){
        events.performer[strlen(events.performer)-1] = '\0';
    }
    FILE * ptr;
    ptr= fopen("text_files\\event.txt","a");
    if(ptr==NULL){
        perror("Error Opening File");
        return;
    }
    fprintf(ptr,"%s,%s,%s,%s\n",events.name,events.date,events.time,events.performer);
    fclose(ptr);
}

void edit_events(){
    system("cls");
    display_events();
    printf("\033[36m");
    FILE *ptr = fopen("text_files\\temp.txt","w");
    FILE *fptr =fopen("text_files\\event.txt","r");
    if(fptr==NULL){
        perror("Error Opening File");
        return;
    }
    if(ptr==NULL){
        perror("Error Opening File");
        return;
    }
    char str[100];
    printf("Enter name of the event to edit :");
    fflush(stdin);
    fgets(str,100,stdin);
    if(strlen(str)!=99){
        str[strlen(str)-1] = '\0';
    }
    fflush(stdin);
    char new_event[100],new_date[20],new_time[20],new_performer[20];
    char str1[100];
    while(fgets(str1,150,fptr)!=NULL){
        char delim[] = ",";
        char *token = strtok(str1,delim);
            if (strcmp(token,str)==0){
                printf("Enter new event name:");
                fflush(stdin);
                fgets(new_event,100,stdin);
                if(strlen(new_event)!=99){
                    new_event[strlen(new_event)-1] = '\0';
                }
                printf("Enter new date(DD/MM/YYYY):");
                scanf("%s",new_date);
                printf("Enter new date(HH/MM/SS):");
                scanf("%s",new_time);
                fflush(stdin);
                printf("Enter new performer:");
                fgets(new_performer,100,stdin);
                if(strlen(new_performer)!=99){
                    new_performer[strlen(new_performer)-1] = '\0';
                }
                fprintf(ptr,"%s,%s,%s,%s\n",new_event,new_date,new_time,new_performer);
            }
            else{
                fprintf(ptr,"%s,%s",token,token + strlen(token)+1);
            }

    }
    fclose(fptr);fclose(ptr);
    remove("text_files\\event.txt");
    rename("text_files\\temp.txt","text_files\\event.txt");
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
}
void deleteEvent() {
    system("cls");
    display_events();
    printf("\033[36m");
    FILE *ptr = fopen("text_files\\temp.txt","w");
    FILE *fptr =fopen("text_files\\event.txt","r");
    if(fptr==NULL){
        perror("Error Opening File");
        return;
    }
    if(ptr==NULL){
        perror("Error Opening File");
        return;
    }
    printf("Enter name of the event to delete :");
    char str[100];
    fflush(stdin);
    fgets(str,100,stdin);
    if(strlen(str)!=99){
        str[strlen(str)-1] = '\0';
    }
    fflush(stdin);
    char str1[150];
    while(fgets(str1,150,fptr)!=NULL){
        char *delim = ",";
        char *token = strtok(str1,delim);
        // char c = "";
        if (strcmp(token,str)!=0){
            fprintf(ptr,"%s,%s",token,token +strlen(token)+1);
        }

    }
    fclose(fptr);fclose(ptr);
    remove("text_files\\event.txt");
    rename("text_files\\temp.txt","text_files\\event.txt");
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
    }


void displayRooms() {
    system("cls");
    printf("\033[36m");
    printf("           Available Rooms:          \n");
    FILE *fptr = fopen("text_files\\rooms.txt","r");
    if(fptr==NULL){
        perror("Error Opening File");
        return;
    }
    char ch=fgetc(fptr);
    while(ch!=EOF){
        printf("%c",ch);
        ch=fgetc(fptr);
    }
    fclose(fptr);
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
}
void bookRoom() {
    system("cls");
    FILE *file = fopen("text_files/rooms.txt","r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    displayRooms();
    printf("\033[1;35m");
    fflush(stdin);
    int room_num;
    char event_name[50];
    printf("Enter the stall number you want to book: ");
    scanf("%d", &room_num);
    printf("Enter Event: ");
    fflush(stdin);
    fgets(event_name, sizeof(event_name), stdin);
    if(strlen(event_name)!=49){
        event_name[strlen(event_name) - 1] = '\0';
    }

    FILE *tempFile = fopen("text_files/temp.txt", "w");
    if (tempFile==NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    char str[10], status[50];
    int num,count=0;
    while (fscanf(file, "%s %d %49[^\n]\n",str,&num,status)!=EOF) {
        if (num == room_num && strcmp(status, "unbooked")==0) {
            fprintf(tempFile,"%s %d %s\n",str,num,event_name);
        }
        else if (num == room_num && strcmp(status, "unbooked")!=0) {
            fprintf(tempFile,"%s %d %s\n",str,num,status);
            count=1;
        }
        else {
            fprintf(tempFile,"%s %d %s\n",str,num,status);
        }
    }
    if(count==1){
        printf("\033[1;31m");
        printf("\nStall is already booked. Please select another.\n\n");
    }
    else{
        printf("\033[1;32m");
        printf("\nStall has been successfully booked.\n\n");
        printf("\033[0m");
    }

    fclose(file);
    fclose(tempFile);
    remove("text_files/rooms.txt");
    rename("text_files/temp.txt","text_files/rooms.txt");
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
}
void unbookRoom() {
    system("cls");
    FILE *file = fopen("text_files/rooms.txt","r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    displayRooms();
    printf("\033[1;35m");
    fflush(stdin);
    int room_num;
    char event_name[50];
    printf("Enter the stall number you want to Unbook: ");
    scanf("%d", &room_num);

    FILE *tempFile = fopen("text_files/temp.txt", "w");
    if (tempFile==NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    char str[10], status[50];
    int num,count=0;
    while (fscanf(file, "%s %d %49[^\n]\n",str,&num,status)!=EOF) {
        if (num == room_num && strcmp(status, "unbooked")!=0) {
            fprintf(tempFile,"%s %d %s\n",str,num,"unbooked");
        }
        else if (num == room_num && strcmp(status, "unbooked")==0) {
            fprintf(tempFile,"%s %d %s\n",str,num,status);
            count=1;
        }
        else {
            fprintf(tempFile,"%s %d %s\n",str,num,status);
        }
    }
    if(count==1){
        printf("\033[1;31m");
        printf("\nStall is already Un-booked. Please select another.\n\n");
    }
    else{
        printf("\033[1;32m");
        printf("\nStall has been successfully Un-booked.\n\n");
        printf("\033[0m");
    }

    fclose(file);
    fclose(tempFile);
    remove("text_files/rooms.txt");
    rename("text_files/temp.txt","text_files/rooms.txt");
    printf("Press \"Enter\" to continue");
    fflush(stdin);
    getchar();
}






void on_button_clicked(GtkWidget *widget, gpointer data) {
                                                                          // Call the corresponding function based on the button clicked
    int task = GPOINTER_TO_INT(data);
    switch (task) {
        case 1:
            registerVolunteer();
            break;
        case 2:
            displayVolunteers();
            break;
             case 3:
            remaining_budget();

            break;
        case 4:
            registerSponsor();

            break;
        case 5:
            displaySponsors();

            break;

        case 6:
            displayTickets();

            break;

        case 7:
            displayparticipants();

            break;
        case 8:
            generateBudgetReport();
            break;
        case 9:
            display_budget();
            break;
        case 10:
            invitation();
            break;
        case 11:
            add_events();
            break;
        case 12:
            edit_events();
            break;
        case 13:
            deleteEvent();
            break;
        case 14:
            display_events();
            break;
        case 15:
            displayRooms();
            break;
        case 16:
            bookRoom();
            break;
        case 17:
            unbookRoom();
            break;





    }
}

   int gtk_admin_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);                       //upper name
    gtk_window_set_title(GTK_WINDOW(window), "Fest Management System");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);                      //border width
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);            //center
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);


    GtkWidget *grid = gtk_grid_new();                                //grid pointer
    gtk_container_add(GTK_CONTAINER(window), grid);


                                                                                  // Column 1: Register, Display, Save Volunteers
    GtkWidget *button1 = gtk_button_new_with_label("Register Volunteer");
    g_signal_connect(button1, "clicked", G_CALLBACK(registerVolunteer), NULL);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);                                //grid type(rows,colums,number of widgets that will span contain only one row and one colums space)

    GtkWidget *button2 = gtk_button_new_with_label("Display Volunteers");
    g_signal_connect(button2, "clicked", G_CALLBACK(displayVolunteers), NULL);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 1, 1);


GtkWidget *button4 = gtk_button_new_with_label("View Remaining Budgets");
g_signal_connect(button4, "clicked", G_CALLBACK(remaining_budget), NULL);                      //call function remaining budget when clicked
gtk_grid_attach(GTK_GRID(grid), button4, 1, 0, 1, 1);

                                                                                    // Button for selling a ticket
GtkWidget *button5 = gtk_button_new_with_label("Register Sponsor(On File)");
g_signal_connect(button5, "clicked", G_CALLBACK(registerSponsor), NULL);
gtk_grid_attach(GTK_GRID(grid), button5, 1, 1, 1, 1);
GtkWidget *button14 = gtk_button_new_with_label("Display Sponsors(On file)");
g_signal_connect(button14, "clicked", G_CALLBACK(displaySponsors), NULL);
gtk_grid_attach(GTK_GRID(grid), button14, 1, 2, 1, 1);

// Button for displaying tickets
GtkWidget *button6 = gtk_button_new_with_label("Display Tickets");
g_signal_connect(button6, "clicked", G_CALLBACK(displayTickets), NULL);
gtk_grid_attach(GTK_GRID(grid), button6, 2, 0, 1, 1);

GtkWidget *button22 = gtk_button_new_with_label("Display Participants");
g_signal_connect(button22, "clicked", G_CALLBACK(displayparticipants), NULL);
gtk_grid_attach(GTK_GRID(grid), button22, 2, 1, 1, 1);
// Button for booking a room

GtkWidget *button17 = gtk_button_new_with_label("Generate Budget Report");
g_signal_connect(button17, "clicked", G_CALLBACK(generateBudgetReport), NULL);
gtk_grid_attach(GTK_GRID(grid), button17, 2, 2, 1, 1);

GtkWidget *button15 = gtk_button_new_with_label("Display Budget");
g_signal_connect(button15, "clicked", G_CALLBACK(display_budget), NULL);
gtk_grid_attach(GTK_GRID(grid), button15, 0, 2, 1, 1);

GtkWidget *button25 = gtk_button_new_with_label("Create Invitation");
g_signal_connect(button25, "clicked", G_CALLBACK(invitation), NULL);
gtk_grid_attach(GTK_GRID(grid), button25, 3, 0, 1, 1);


GtkWidget *button7 = gtk_button_new_with_label("Book Room");
g_signal_connect(button7, "clicked", G_CALLBACK(bookRoom), NULL);
gtk_grid_attach(GTK_GRID(grid), button7, 4, 2, 1, 1);


// Button for unbooking a room
GtkWidget *button9 = gtk_button_new_with_label("Unbook Room");
g_signal_connect(button9, "clicked", G_CALLBACK(unbookRoom), NULL);
gtk_grid_attach(GTK_GRID(grid), button9, 5, 0, 1, 1);

// Button for editing an event
GtkWidget *button10 = gtk_button_new_with_label("Edit Event");
g_signal_connect(button10, "clicked", G_CALLBACK(edit_events), NULL);
gtk_grid_attach(GTK_GRID(grid), button10, 3, 2, 1, 1);

// Button for deleting an event
GtkWidget *button11 = gtk_button_new_with_label("Delete Event");
g_signal_connect(button11, "clicked", G_CALLBACK(deleteEvent), NULL);
gtk_grid_attach(GTK_GRID(grid), button11, 4, 0, 1, 1);


GtkWidget *button13 = gtk_button_new_with_label("Register Sponsor");
g_signal_connect(button13, "clicked", G_CALLBACK(registerSponsor), NULL);
gtk_grid_attach(GTK_GRID(grid), button13, 5, 1, 1, 1);




GtkWidget *button20 = gtk_button_new_with_label("Display Events");
g_signal_connect(button20, "clicked", G_CALLBACK(display_events), NULL);
gtk_grid_attach(GTK_GRID(grid), button20, 4, 1, 1, 1);
// Button for adding an event
GtkWidget *button24 = gtk_button_new_with_label("Add Event");
g_signal_connect(button24, "clicked", G_CALLBACK(add_events), NULL);
gtk_grid_attach(GTK_GRID(grid), button24, 3, 1, 1, 1);


GtkWidget *button26 = gtk_button_new_with_label("Display Rooms");
g_signal_connect(button26, "clicked", G_CALLBACK(displayRooms), NULL);
gtk_grid_attach(GTK_GRID(grid), button26, 4, 2, 1, 1);
GtkWidget *button27 = gtk_button_new_with_label("Exit");
g_signal_connect(button27, "clicked", G_CALLBACK(gtk_main_quit), NULL);
gtk_grid_attach(GTK_GRID(grid), button27, 5, 2, 1, 1);







                                                                                   // Show all widgets
    gtk_widget_show_all(window);

                                                                                    // Run the main GTK loop
    gtk_main();

    return 0;
}



