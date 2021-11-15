#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 50

typedef struct
{
    string title;
    string author;
    int copies;

} book;

book books[MAX];

int bookExists(string name);
void returnBook(string name);
void addBook(string name);
void rentBook(string name);
void searchByAuthor(string author);
void printLibrary(string nothing);

int main()
{
    printf("Welcome to the library!!\n\n"); //welcome message

    bool inLibrary = true;
    while(inLibrary)
    {
        printf("What would you like to do?\n"); //options
        printf("1). Check a book out.\n");
        printf("2). Return a book.\n");
        printf("3). Search by author.\n");
        printf("4). Print library.\n");
        printf("5). Leave library\n\n");

        int input = get_int("");
        printf("\n");

        if (input == 5) //leave library
        {
            inLibrary = false;
        }
        else if (input == 4) //prints library
        {
            printLibrary("");
        }
        else if (input == 3) //print by author
        {
            string author = get_string("Please input the authors name. : ");
            searchByAuthor(author);
        }
        else if (input > 5 || input < 1) //input wrong #
        {
            printf("Please enter a number between 1 and 5\n");
        }
        else
        {
            string titleOfBook = get_string("Please input title of book. : "); //all further anwsers requre book names

            if (input == 2) //if adding book to library
            {
                returnBook(titleOfBook);
            }
            else //if anwser 1 rent a book
            { 
                rentBook(titleOfBook);
            }
        }

        printf("\n\n");
    }

    printf("Thank you!!\n");
}

void printLibrary(string nothing) 
{
    for (int i = 0; i < MAX; i ++)
    {
        if (books[i].title != NULL) //for every book in library print title, author, copies
        {
            printf("%s,     ", books[i].title);
            printf("Author : %s,     ", books[i].author);
            printf("Copies : %i\n", books[i].copies);
        }
    }
}

void searchByAuthor(string author)
{5
    bool noAuthorsFound = true;

    for (int i = 0; i < MAX; i++)
    {
        if (books[i].author != NULL) 
        {
            if (strcmp(books[i].author, author) == 0)//for each book if the author = the chosen author print the book name
            {
                printf("%s, ", books[i].title);
                printf("%i copies.\n", books[i].copies);

                noAuthorsFound = false;
            }
        }
    }

    if (noAuthorsFound == true) //if no author found print message
    {
        printf("Sorry no authors were found.\n");
    }
}

int bookExists(string name)
{
    for (int i = 0; i < MAX; i++)
    {
        if (books[i].title != NULL) //check if the 
        {
            if (strcmp(books[i].title, name) == 0)
            {
                return i;
            }
        }
    }

    return -1;
}

void returnBook(string name)
{
    int newBook = bookExists(name);

    if (newBook >= 0)
    {
        books[newBook].copies++;
    }
    else
    {
        bool answer = true;

        do
        {
            string getAnswer = get_string("We couldn't find that book in our library. Do you want to add it? (y / n): ");

            if (strcmp(getAnswer, "y") == 0)
            {
                answer = false;
            }
            else if (strcmp(getAnswer, "n") == 0)
            {
                return;
            }
        } while(answer);

        addBook(name);
    }
}

void addBook(string name)
{
    int newBook;
    for (int i = 0; i < MAX; i++)
    {
        if (books[i].title == NULL)
        {
            newBook = i;
        }
    }

    books[newBook].title = name;
    books[newBook].author = get_string("Please input the author of the book. : ");
    books[newBook].copies = 1;

    return;
}

void rentBook(string name)
{
    int bookExistsInt = bookExists(name);
    if (bookExistsInt >= 0)
    {
        books[bookExistsInt].copies--;
        if (books[bookExistsInt].copies == 0)
        {
            books[bookExistsInt].title = NULL;
            books[bookExistsInt].author = NULL;
        }
    }
    else
    {
        printf("Sorry we don't have that book.\n");
    }
}
