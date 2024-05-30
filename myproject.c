#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
char ch[10][130] = {"Janrath Superfast", "SRS Express", "Meena Travels", "Pune-Lonavla Express", "NewDelhi Roadways"};
char name[32][100] = {'\0'};
char number[32][2] = {'\0'};
int num1[32] = {0};
int busno;

void bus(); // for list of bus
void name_number(int booking, char numstr[100]);
void booking(); // for booking the tickets
int read_number(int busno); // for reading the number from the file
void read_name(int busno); // for reading the name from the file
void status(); // for printing the status by user input
void ststatus(int busno); // for printing the status while booking ticket
void cancel();
void login(); // for login

int main() {
    login();
    int num, i;
    do {
        system("cls");
        printf("\n\n\n");
        printf("====================================== WELCOME TO BUS RESERVATION SYSTEM ======================================\n\n\n");
        printf("\t\t\t\t\t[1]=> View Bus List\n");
        printf("\n");
        printf("\t\t\t\t\t[2]=> Book Tickets\n");
        printf("\n");
        printf("\t\t\t\t\t[3]=> Cancel Booking\n");
        printf("\n");
        printf("\t\t\t\t\t[4]=> Bus Status Board\n");
        printf("\n");
        printf("\t\t\t\t\t[5]=> Exit\n\n");
        printf("===============================================================================================================\n\n");
        printf("\n\t\t\tEnter Your Choice: ");
        scanf("%d", &num);
        switch (num) {
            case 1:
                bus();
                break;
            case 2:
                booking();
                break;
            case 3:
                cancel();
                break;
            case 4:
                status();
                break;
        }
        getch();
    } while (num != 5);
    system("CLS");
    printf("\t----------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tThank You...We wish to serve you again!\t\t\t\t\t\t\n");
    printf("\t----------------------------------------------------------------------------------------------------------\n");
    getch();
    return 0;
}

void bus() {
    system("cls");
    printf("\n\n\n");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n");
    printf("\t\t\t\t\t[1]  =>  %s\n", ch[0]);
    printf("\n");
    printf("\t\t\t\t\t[2]  =>  %s\n", ch[1]);
    printf("\n");
    printf("\t\t\t\t\t[3]  =>  %s\n", ch[2]);
    printf("\n");
    printf("\t\t\t\t\t[4]  =>  %s\n", ch[3]);
    printf("\n");
    printf("\t\t\t\t\t[5]  =>  %s\n", ch[4]);
}

void booking() {
    int i = 0;
    char numstr[100];
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n"); // for entering bus number
    bus();
    printf("\nEnter the Bus number: ");
    scanf("%d", &busno);
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n"); // for selecting coach
    printf("Your Bus Number is %d ********** %s", busno, ch[busno - 1]);
    ststatus(busno);
    FILE *f1; // for reading the seats from the user
    char str1[80] = "32";
    int seat1, booking = 0;

    char filename[10];
    snprintf(filename, 10, "tr%d.txt", busno);

    f1 = fopen(filename, "r+");
    if (f1 != NULL) {
        fgets(str1, 80, f1);
        fclose(f1);
    }

    seat1 = atoi(str1);
    if (seat1 <= 0) {
        printf("\nThere is no blank seat in this bus ");
    } else {
        printf("\n\n\n\t\t\t\tAvailable Seats: %d\n", seat1);
        printf("\n\t\t\t\tNumber of Tickets: ");
        scanf("%d", &booking);
        printf("\n");

        seat1 = seat1 - booking;
        itoa(busno, numstr, 10);
        name_number(booking, numstr);
        printf("\n\t\t\t\tThe Total booking amount is %d", 120 * booking);
        itoa(seat1, str1, 10);

        f1 = fopen(filename, "w");
        if (f1 != NULL) {
            fputs(str1, f1);
            fclose(f1);
        }
    }
}

void name_number(int booking, char numstr[100]) {
    char tempstr[100], tempstr1[12] = "status", tempstr2[12] = "number";
    int number;
    FILE *a, *b;
    int i = 0;
    strcat(numstr, ".txt");
    strcat(tempstr1, numstr);
    strcat(tempstr2, numstr);
    a = fopen(tempstr1, "a"); // for open the file to write the name in the file
    b = fopen(tempstr2, "a"); // for open the file for writing the number in the file
    for (i = 0; i < booking; i++) { // for entering the person name and seat number in the file
        printf("============================Enter the details for ticket no %d============================\n\n\n", i + 1);
        printf("\t\t\t\tEnter the seat number: ");
        scanf("%d", &number);
        printf("\t\t\t\tEnter the name of person: ");
        scanf("%s", name[number - 1]);
        printf("\n======================================================================================================\n\n");
        printf("\n");
        itoa(number, tempstr, 10);
        fprintf(a, "%s ", name[number - 1]);
        fprintf(b, "%s ", tempstr);
    }
    fclose(a);
    fclose(b);
}

int read_number(int busno) { // for putting the numeric value in the array
    char tempstr2[12] = "number";
    FILE *a;
    char numstr[100];
    int i = 0, j = 0, k;
    itoa(busno, numstr, 10);
    strcat(numstr, ".txt");
    strcat(tempstr2, numstr);
    a = fopen(tempstr2, "a+"); // for open the file to write the name in the file
    while (!feof(a)) {
        number[i][j] = fgetc(a);
        if (number[i][j] == ' ') {
            j = 0;
            i++;
        } else {
            j++;
        }
    }
    k = i;
    for (i = 0; i < k; i++) {
        num1[i] = atoi(number[i]);
    }
    fclose(a);
    return k;
}

void read_name(int busno) { // for putting the numeric value in the array
    char tempstr1[12] = "status";
    FILE *b;
    char numstr[100];
    int i = 0, j = 0, k = 0;
    itoa(busno, numstr, 10);
    strcat(numstr, ".txt");
    strcat(tempstr1, numstr);
    b = fopen(tempstr1, "a+"); // for open the file to write the name in the file
    while (!feof(b)) {
        name[i][j] = fgetc(b);
        if (name[i][j] == ' ') {
            j = 0;
            i++;
        } else {
            j++;
        }
    }
    name[i][j] = '\0';
    k = i;
    fclose(b);
}

void status() {
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n");
    int i, busno, index = 0, j;
    printf("Enter the number of bus: ");
    scanf("%d", &busno);
    j = read_number(busno);
    read_name(busno);
    printf("____________________________________________________________________________________________________________________\n");
    printf("                                      Bus.no-->%d---->%s                                                            \n", busno, ch[busno - 1]);
    printf("____________________________________________________________________________________________________________________\n");
    char tempname[33][10] = {"Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty "};
    for (i = 0; i < j; i++) {
        strcpy(tempname[num1[i]], name[i]);
    }
    for (i = 0; i < 8; i++) {
        printf("\t\t\t\t");
        for (j = 0; j < 4; j++) {
            printf("%d.%s\t", index + 1, tempname[index + 1]);
            index++;
        }
        printf("\n");
    }
}

void ststatus(int busno) {
    printf("Your Bus Number is %d ********** %s", busno, ch[busno - 1]);
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n");
    int i, index = 0, j;
    j = read_number(busno);
    read_name(busno);
    char tempname[33][10] = {"Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty ", "Empty "};
    for (i = 0; i < j; i++) {
        strcpy(tempname[num1[i]], name[i]);
    }
    for (i = 0; i < 8; i++) {
        printf("\t\t\t\t");
        for (j = 0; j < 4; j++) {
            printf("%d.%s\t", index + 1, tempname[index + 1]);
            index++;
        }
        printf("\n");
    }
}

void cancel() {
    int seat_no, i, j;
    char numstr[100], tempstr2[15] = "number", tempstr1[15] = "status";
    printf("\n Enter the bus number: ");
    scanf("%d", &busno);
    itoa(busno, numstr, 10);
    strcat(numstr, ".txt");
    strcat(tempstr1, numstr);
    strcat(tempstr2, numstr);
    read_number(busno);
    read_name(busno);
    ststatus(busno);
    printf("\n Enter the seat number: ");
    scanf("%d", &seat_no);
    FILE *a, *b;
    a = fopen(tempstr1, "w+");
    b = fopen(tempstr2, "w+");
    for (i = 0; i < 32; i++) {
        if (num1[i] == seat_no) {
            for (j = 0; j < 32; j++) {
                if (num1[j] != seat_no && num1[j] != 0) {
                    fprintf(b, "%d ", num1[j]);
                    fprintf(a, "%s", name[j]);
                } else if (num1[j] == seat_no && num1[j] != 0) {
                    strcpy(name[j], "Empty ");
                }
            }
        }
    }
    fclose(a);
    fclose(b);
    printf("\n\n");
    printf("======================================================================================================\n");
    printf("\t\t\t\tYour 120 rupees has been Returned\t\t\t\n");
    printf("======================================================================================================\n");
}

void login() {
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];
    char user[10] = "user";
    char pass[10] = "pass";
    do {
        system("cls");
        printf("\n  =========================  Welcome to SS Tours and Travels  =========================  ");
        printf(" \n\n ENTER USERNAME:- ");
        scanf("%s", uname);
        printf(" \n ENTER PASSWORD:- ");
        while (i < 10) {
            pword[i] = getch();
            c = pword[i];
            if (c == 13) break;
            else printf("*");
            i++;
        }
        pword[i] = '\0';
        i = 0;
        if (strcmp(uname, "user") == 0 && strcmp(pword, "pass") == 0) {
            printf("\n\n\n Welcome to the portal...Login is SUCCESSFUL");
            printf("\n\n\n Press any key to continue...");
            getch(); // holds the screen
            break;
        } else {
            printf("\n\n\n OOPS!...Login is UNSUCCESSFUL");
            a++;
            getch();
        }
    } while (a <= 2);
    if (a > 2) {
        printf("\n Sorry you have entered the wrong username and password for three or more times!");
        getch();
    }
    system("cls");
}
