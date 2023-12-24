 //!Library management System

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

void gotoxy(int, int);
void displayHeader();
void displayMenu();
void addbook();
void searchbook();
void disbook();
void addborrower();
void disborrower();
void borobook();
void returnbook();
void borrowstat();
// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct book{                            //todo structure for book details
    char book_id[15];
    char book_name[200];
    char book_author[75];
};
struct borrower{                        //todo structure for borrower detaile
    char borr_id[15];
    char borr_name[100];
    int p_no;
};
struct borrowbook{
    char borr_id[15];
    char book_id[15];
    char date_of_issue[10];
};
void displayHeader() {
    gotoxy(15, 8);
    setColor(14); // Yellow color
    printf("|<><><><><><><><>: LIBRARY MANAGEMENT SYSTEM :<><><><><><><><>|");
    setColor(15); // White color
}
void displayMenu() {
    system("cls");
    displayHeader();
    gotoxy(10, 10);
    setColor(11); // Light cyan color
    printf("Enter the number to perform the corresponding task.\n\n");
    setColor(15); // White color
    gotoxy(10, 12);
    printf("1 --> Add a Book");
    gotoxy(10, 13);
    printf("2 --> Search a Book");
    gotoxy(10, 14);
    printf("3 --> Display All Books");
    gotoxy(10, 15);
    printf("4 --> Add a Borrower");
    gotoxy(10, 16);
    printf("5 --> Display All Borrowers");
    gotoxy(10, 17);
    printf("6 --> Borrow a Book");
    gotoxy(10, 18);
    printf("7 --> Return a Book");
    gotoxy(10, 19);
    printf("8 --> Display Borrow Status");
    gotoxy(10, 20);
    printf("0 --> EXIT");
}

void menu() {
    int choice;
    displayMenu();
    gotoxy(10, 22);
    setColor(11); // Light cyan color
    printf("Enter Your Choice: ");
    setColor(15); // White color
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addbook();
            break;
        case 2:
            searchbook();
            break;
        case 3:
            disbook();
            break;
        case 4:
            addborrower();
            break;
        case 5:
            disborrower();
            break;
        case 6:
            borobook();
            break;
        case 7:
            returnbook();
            break;
        case 8:
            borrowstat();
            break;
        case 0:
            break;
        default:
            system("cls");
            gotoxy(10, 14);
            setColor(12); // Red color
            printf("Invalid Choice !");
            setColor(15); // White color
            printf("\n\tPress any key to Continue");
            getch();
            menu();

    }

}

void addbook() {
    FILE *fp;
    struct book bok;
    char yes = 'y';
    system("cls");

    fp = fopen("Files/BookRecord.txt", "ab+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 5);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    fflush(stdin);
    while (yes == 'y' || yes == 'Y') {
        gotoxy(10, 3);
        setColor(11); // Light cyan color
        printf("<--:ADD A BOOK:-->");
        setColor(15); // White color
        gotoxy(10, 5);
        printf("Enter Details For Adding Book");
        gotoxy(10, 7);
        printf("Enter Book ID: ");
        fgets(bok.book_id, sizeof(bok.book_id), stdin);
        strtok(bok.book_id, "\n");  // Remove the newline character
        gotoxy(10, 8);
        printf("Enter Name of Book: ");
        fgets(bok.book_name, sizeof(bok.book_name), stdin);
        strtok(bok.book_name, "\n");  // Remove the newline character
        gotoxy(10, 9);
        printf("Enter Name of Author of Book: ");
        fgets(bok.book_author, sizeof(bok.book_author), stdin);
        strtok(bok.book_author, "\n");  // Remove the newline character

        fwrite(&bok, sizeof(bok), 1, fp);
        gotoxy(10, 15);
        printf("If You Want to Add More Record Then Press 'y' else press any key");
        fflush(stdin);
        yes = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10, 10);
    printf("Press Any Key To Continue");
    getch();
    menu();
}

void searchbook() {
    FILE *fp;
    struct book bok;
    char bkid[15];
    system("cls");
    gotoxy(10, 3);
    setColor(11); // Light cyan color
    printf("<--SEARCH BOOK-->");
    setColor(15); // White color
    gotoxy(10, 5);
    printf("Enter The Book ID: ");
    fflush(stdin);
    fgets(bkid, sizeof(bkid), stdin);
    strtok(bkid, "\n");  // Remove the newline character

    fp = fopen("Files/BookRecord.txt", "rb+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 6);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }

    int found = 0;  // Flag to check if the book ID was found or not.

    while (fread(&bok, sizeof(bok), 1, fp) == 1) {
        if (strcmp(bkid, bok.book_id) == 0) {
            gotoxy(10, 8);
            printf("Book ID: %s", bok.book_id);
            gotoxy(10, 9);
            printf("Book Name: %s", bok.book_name);
            gotoxy(10, 10);
            printf("Author of Book: %s", bok.book_author);

            found = 1;  // Set the flag to indicate the book ID was found
            break;      // Stop searching once a match is found
        }
    }

    if (!found) {
        gotoxy(10, 8);
        printf("Book ID not found.");
    }

    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to Continue");
    getch();
    menu();
}




void disbook() {
    FILE *fp;
    int i = 1, j;
    struct book bok;
    system("cls");
    gotoxy(10, 3);
    setColor(11); // Light cyan color
    printf("<--ALL BOOKS-->");
    setColor(15); // White color
    gotoxy(10, 5);
    printf("S.No.    Book ID          Book Name                    Author");
    gotoxy(10, 6);
    printf("-------------------------------------------------------------");
    fp = fopen("Files/BookRecord.txt", "rb+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 6);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    j = 8;
    while (fread(&bok, sizeof(bok), 1, fp) == 1) {
        gotoxy(10, j);
        printf("%-9d%-17s%-29s%-10s", i, bok.book_id, bok.book_name, bok.book_author);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10, j + 3);
    printf("Press any key to Continue");
    getch();
    menu();
}

void addborrower() {
    FILE *fp;
    struct borrower bor;
    char yes = 'y';
    system("cls");

    fp = fopen("Files/BorrowerRecord.txt", "ab+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 5);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    fflush(stdin);
    while (yes == 'y' || yes == 'Y') {
        gotoxy(10, 3);
        setColor(11); // Light cyan color
        printf("<--:ADD A BORROWER:-->");
        setColor(15); // White color
        gotoxy(10, 5);
        printf("Enter Details For Adding Borrowers ");
        gotoxy(10, 7);
        printf("Enter Borrower ID: ");
        fgets(bor.borr_id, sizeof(bor.borr_id), stdin);
        strtok(bor.borr_id, "\n");  // Remove the newline character
        gotoxy(10, 8);
        printf("Enter Borrower's Name; ");
        fgets(bor.borr_name, sizeof(bor.borr_name), stdin);
        strtok(bor.borr_name, "\n");  // Remove the newline character
        fwrite(&bor, sizeof(bor), 1, fp);
        gotoxy(10, 15);
        printf("If You Want to Add More Record Then Press 'y' else press any key");
        fflush(stdin);
        yes = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10, 10);
    printf("Press Any Key To Continue");
    getch();
    menu();
}

void disborrower() {
    FILE *fp;
    int i = 1, j;
    struct borrower bor;
    system("cls");
    gotoxy(10, 3);
    setColor(11); // Light cyan color
    printf("<--:ALL Borrowers:-->");
    setColor(15); // White color
    gotoxy(10, 5);
    printf("S.No.    Borrower ID          Borrower Name     ");
    gotoxy(10, 6);
    printf("------------------------------------------------");
    fp = fopen("Files/BorrowerRecord.txt", "rb+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 6);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    j = 8;
    while (fread(&bor, sizeof(bor), 1, fp) == 1) {
        gotoxy(10, j);
        printf("%-9d%-21s%-18s", i, bor.borr_id, bor.borr_name);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10, j + 3);
    printf("Press any key to Continue");
    getch();
    menu();
}

void borobook() {
    FILE *fp, *fp1, *fp2;

    struct borrowbook borbok;
    char yes = 'y';
    system("cls");

    fp = fopen("Files/BorrowRecord.txt", "ab+");
    fp1 = fopen("Files/BookRecord.txt", "rb+");
    fp2 = fopen("Files/BorrowerRecord.txt", "rb+");

    if (fp == NULL && fp1 == NULL && fp2 == NULL) {
        system("cls");
        gotoxy(10, 5);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    fflush(stdin);
    while (yes == 'y' || yes == 'Y') {
        gotoxy(10, 3);
        setColor(11); // Light cyan color
        printf("<--:BORROW A BOOK:-->");
        setColor(15); // White color
        gotoxy(10, 5);
        printf("Enter Borrower ID: ");
        fgets(borbok.borr_id, sizeof(borbok.borr_id), stdin);
        strtok(borbok.borr_id, "\n");  // Remove the newline character
        gotoxy(10, 6);
        printf("Enter Book ID: ");
        fgets(borbok.book_id, sizeof(borbok.book_id), stdin);
        strtok(borbok.book_id, "\n");  // Remove the newline character
        gotoxy(10, 7);
        printf("Enter Date Of Issue: ");
        fgets(borbok.date_of_issue, sizeof(borbok.date_of_issue), stdin);
        strtok(borbok.date_of_issue, "\n");  // Remove the newline character

        fwrite(&borbok, sizeof(borbok), 1, fp);
        gotoxy(10, 15);
        printf("If You Want to Add More Record Then Press 'y' else press any key");
        fflush(stdin);
        yes = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    gotoxy(10, 16);
    printf("Press any key to Continue");
    getch();
    menu();
}

void borrowstat() {
    FILE *fp;
    int i = 1, j;
    struct borrowbook borbok;
    system("cls");
    gotoxy(10, 3);
    setColor(11); // Light cyan color
    printf("<--:BORROW STATUS:-->");
    setColor(15); // White color
    gotoxy(10, 5);
    printf("S.No.    Borrower ID            Book ID          Date of Issue");
    gotoxy(10, 6);
    printf("--------------------------------------------------------------");
    fp = fopen("Files/BorrowRecord.txt", "rb+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 6);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    j = 8;
    while (fread(&borbok, sizeof(borbok), 1, fp) == 1) {
        gotoxy(10, j);
        printf("%-9d%-23s%-18s%-13s", i, borbok.borr_id, borbok.book_id, borbok.date_of_issue);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10, j + 3);
    printf("Press any key to Continue");
    getch();
    menu();
}

void returnbook() {
    char borid[15];
    char bokid[15];
    FILE *fp, *fr;
    struct borrowbook borbok;
    system("cls");
    gotoxy(10, 3);
    setColor(11); // Light cyan color
    printf("<--RETURN A RECORD:-->");
    setColor(15); // White color
    gotoxy(10, 5);
    printf("Enter Borrower ID: ");
    fflush(stdin);
    fgets(borid, sizeof(borid), stdin);
    strtok(borid, "\n");  // Remove the newline character
    gotoxy(10, 6);
    printf("Enter Book ID: ");
    fflush(stdin);
    fgets(bokid, sizeof(bokid), stdin);
    strtok(bokid, "\n");  // Remove the newline character
    fp = fopen("Files/BorrowRecord.txt", "rb+");
    if (fp == NULL) {
        system("cls");
        gotoxy(10, 6);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    fr = fopen("Files/temp.txt", "wb+");
    if (fr == NULL) {
        system("cls");
        gotoxy(10, 6);
        setColor(12); // Red color
        printf("Error for Opening File");
        setColor(15); // White color
        exit(1);
    }
    while (fread(&borbok, sizeof(borbok), 1, fp) == 1) {
        if (strcmp(borid, borbok.borr_id) != 0 || strcmp(bokid, borbok.book_id) != 0) {
            fwrite(&borbok, sizeof(borbok), 1, fr);
        }
    }
    fclose(fp);
    fclose(fr);
    remove("Files/BorrowRecord.txt");
    rename("Files/temp.txt", "Files/BorrowRecord.txt");
    gotoxy(10, 10);
    printf("Press any Key to continue.");
    getch();
    menu();
}

void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int main() {
    system("cls");
    displayHeader();
    getch();
    menu();
    return 0;
}