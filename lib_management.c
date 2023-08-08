#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

void gotoxy(int,int);
void menu();
void addbook();
void searchbook();
void disbook();
void addborrower();
void disborrower();


struct book{
    char book_id[15];
    char book_name[200];
    char book_author[75];
};

struct borrower{
    char borr_id[15];
    char borr_name[100];
};

struct borrowbook{
    char borrower_id[15];
    char book_id[15];
};

int main(){
    system("cls");
    gotoxy(15,8);
    printf("|<><><><><><><><>:LIBRARY MANAGEMENT SYSTEM:<><><><><><><><>|");
    gotoxy(33,15);
    printf("Press any Key to Continue");
    getch();
    menu();
    return 0;

}

void menu(){
    int choice;
    system("cls");
    gotoxy(10,3);
    printf("<----:Main Menu:---->");
    gotoxy(10,5);
    printf("Enter Appropriate Number to Perform Following Task.");
    gotoxy(10,7);
    printf("1 --> Add a Book");
    gotoxy(10,8);
    printf("2 --> Search a Book");
    gotoxy(10,9);
    printf("3 --> Display All Books");
    gotoxy(10,10);
    printf("4 --> Add a Borrower");
    gotoxy(10,11);
    printf("5 --> Display All Borrowers");
    gotoxy(10,12);
    printf("6 --> Borrow a Book");
    gotoxy(10,13);
    printf("7 --> Return a book");
    gotoxy(10,14);
    printf("0 --> EXIT");

    printf("\n\nEnter Your Choice:\t");
    scanf("%d",&choice);

    switch(choice){
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

            break;
        case 7:

            break;
        case 0:

            break;
        default:
            gotoxy(10,17);
            printf("Invalid Choice !");
    }

}

void addbook(){
    FILE *fp;
    struct book bok;
    char yes='y';
    system("cls");
    
    fp = fopen("BookRecord.txt","ab+");
    if(fp == NULL){
        gotoxy(10,5);
        printf("Error for Opening File");
        exit(1);
    }
    fflush(stdin);
    while(yes=='y'){
        gotoxy(10,3);
        printf("<--:ADD A BOOK:-->");
        gotoxy(10,5);
        printf("Enter Details For Adding Book");
        gotoxy(10,7);
        printf("Enter Book ID: ");
        gets(bok.book_id);
        gotoxy(10,8);
        printf("Enter Name of Book: ");
        gets(bok.book_name);
        gotoxy(10,9);
        printf("Enter Name of Author of Book: ");
        gets(bok.book_author);

        fwrite(&bok,sizeof(bok),1,fp);
        gotoxy(10,15);
        printf("If You Want to Add More Record Then Press 'y' else press any key");
        fflush(stdin);
        yes=getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,10);
    printf("Press Any Key To Continue");
    getch();
    menu();
}

void searchbook(){
    FILE *fp;
    struct book bok;
    char bkname[200];
    system("cls");
    gotoxy(10,3);
    printf("<--SEARCH BOOK-->");
    gotoxy(10,5);
    printf("Enter Tne Name of Book: ");
    fflush(stdin);
    gets(bkname);
    fp=fopen("BookRecord.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error for Opening File");
        exit(1);
    }
    while(fread(&bok,sizeof(bok),1,fp) == 1){
        if(strcmp(bkname,bok.book_name)==0){
            gotoxy(10,8);
            printf("Book ID: %s",bok.book_id);
            gotoxy(10,9);
            printf("Book Name: %s",bok.book_name);
            gotoxy(10,10);
            printf("Author of Book: %s",bok.book_author);
        }
    }
    fclose(fp);
    gotoxy(10,16);
    printf("Press any key to Continue");
    getch();
    menu();
}

void disbook(){
    FILE *fp;
    int i=1,j;
    struct book bok;
    system("cls");
    gotoxy(10,3);
    printf("<--ALL BOOKS-->");
    gotoxy(10,5);
    printf("S.No.    Book ID          Book Name                    Author");
    gotoxy(10,6);
    printf("-------------------------------------------------------------");
    fp=fopen("BookRecord.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error for Opening File");
        exit(1);
    }
    j=8;
    while(fread(&bok,sizeof(bok),1,fp)==1){
        gotoxy(10,j);
        printf("%-9d%-17s%-29s%-10s",i,bok.book_id,bok.book_name,bok.book_author);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to Continue");
    getch();
    menu();
}

void addborrower(){
    FILE *fp;
    struct borrower bor;
    char yes='y';
    system("cls");

    fp=fopen("BorrowerRecord.txt","ab+");
    if(fp == NULL){
        gotoxy(10,5);
        printf("Error for Opening File");
        exit(1);
    }
    fflush(stdin);
    while(yes=='y'){
        gotoxy(10,3);
        printf("<--:ADD A BORROWER:-->");
        gotoxy(10,5);
        printf("Enter Datails For Adding Borrowers ");
        gotoxy(10,7);
        printf("Enter Borrower ID: ");
        gets(bor.borr_id);
        gotoxy(10,8);
        printf("Enter Borrower's Name; ");
        gets(bor.borr_name);
        fwrite(&bor,sizeof(bor),1,fp);
        gotoxy(10,15);
        printf("If You Want to Add More Record Then Press 'y' else press any key");
        fflush(stdin);
        yes=getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,10);
    printf("Press Any Key To Continue");
    getch();
    menu();
}

void disborrower(){
    FILE *fp;
    int i=1,j;
    struct borrower bor;
    system("cls");
    gotoxy(10,3);
    printf("<--ALL Borrowers-->");
    gotoxy(10,5);
    printf("S.No.    Borrower ID          Borrower Name     ");
    gotoxy(10,6);
    printf("------------------------------------------------");
    fp=fopen("BorrowerRecord.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error for Opening File");
        exit(1);
    }
    j=8;
    while(fread(&bor,sizeof(bor),1,fp)==1){
        gotoxy(10,j);
        printf("%-9d%-21s%-18s",i,bor.borr_id,bor.borr_name);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to Continue");
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