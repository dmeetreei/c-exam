/*
 * Программа управления личным каталогом книг
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BOOKS 100
#define MAX_STR_LEN 50


struct Book
{
    int id;
    char author[MAX_STR_LEN];
    char title[MAX_STR_LEN];
    int year;
    char genre[MAX_STR_LEN];
};

void addBook(struct Book * library)
{
    system("cls");

    FILE * file = fopen("library.txt", "a");
    if (file == NULL)
    {
        printf("Error in library file opening.\n");
        return;
    }

    FILE * idFile = fopen("ids.txt", "a");
    if (idFile == NULL)
    {
        printf("Error in id file opening.\n");
        return;
    }
    int actualId = 0;
    while (fgets(line, sizeof(line), idFile) != NULL)
    {
        strcpy(lastLine, line);
    }

    char line[10];
    char lastLine[10];



    printf("Enter author: ");
    scanf("%s", library -> author);
    printf("Enter title: ");
    scanf("%s", library -> title);
    printf("Enter year: ");
    scanf("%d", & library -> year);
    printf("Enter genre: ");
    scanf("%s", library -> genre);
    library -> id = actualId++;

    fprintf(idFile, "%d\n",library -> id);
    fprintf(file, "%s,%s,%d,%s\n", library -> author, library -> title, library -> year, library -> genre);
    fclose(idFile);
    fclose(file);
}

void showBooks()
{
    system("cls");
    FILE * file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("Error in file opening.\n");
        return;
    }

    FILE * idFile = fopen("ids.txt", "r");
    if (idFile == NULL)
    {
        printf("Error in id file opening.\n");
        return;
    }

    printf("%-5s%-20s%-20s%-5s%-20s\n", "ID", "Author", "Title", "Year", "Genre");
    char id[3];
    char line[200];


    while (fgets(id, sizeof(id), idFile)&&(fgets(line, sizeof(line), file)))
    {
        id[strcspn(id, "\n")] = '\0';
        printf("%-5s %s", id, line);
    }

    fclose(idFile);
    fclose(file);
}

void deleteBook()
{
    system("cls");
    int id;
    printf("Enter the ID of the book to delete: ");
    scanf("%d", & id);

    FILE * file = fopen("library.txt", "r");
    FILE * tempFile = fopen("temp.txt", "w");
    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int tempId;
        sscanf(line, "%d,", & tempId);
        if (tempId != id)
        {
            fputs(line, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
    {
        printf("Book deleted successfully.\n");
    }
    else
    {
        printf("Book not found.\n");
    }
}

void searchBooks()
{
    system("cls");
    char searchQuery[MAX_STR_LEN];
    printf("Enter search query: ");
    scanf("%s", searchQuery);

    FILE * file = fopen("library.txt", "r");
    char line[200];
    int found = 0;

    printf("Search results:\n");
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, searchQuery) != NULL)
        {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No books found with the given query.\n");
    }

    fclose(file);
}

void editBook()
{
    system("cls");
    int id;
    printf("Enter the ID of the book to edit: ");
    scanf("%d", & id);

    FILE * file = fopen("library.txt", "r");
    FILE * tempFile = fopen("temp.txt", "w");
    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int tempId;
        sscanf(line, "%d,", & tempId);
        if (tempId == id)
        {
            struct Book book;
            printf("Enter new author: ");
            scanf("%s", book.author);
            printf("Enter new title: ");
            scanf("%s", book.title);
            printf("Enter new year: ");
            scanf("%d", & book.year);
            printf("Enter new genre: ");
            scanf("%s", book.genre);
            book.id = id;

            fprintf(tempFile, "%d,%s,%s,%d,%s\n", book.id, book.author, book.title, book.year, book.genre);
            found = 1;
        }
        else
        {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
    {
        printf("Book edited successfully.\n");
    }
    else
    {
        printf("Book not found.\n");
    }
}

void printStats()
{
    system("cls");
    FILE * file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("Error in file opening.\n");
        return;
    }
    int count = 0;
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        count++;
    }

    printf("Total number of books: %d\n", count);

    fclose(file);
}

void actionsWithBooks(struct Book * library)
{
    system("cls");
    int choice;
    do
    {
        printf("1. Add book\n");
        printf("2. Show catalog\n");
        printf("3. Delete book\n");
        printf("4. Search book\n");
        printf("5. Edit book\n");
        printf("6. Catalog statistics\n");
        printf("7. Exit\n");
        scanf("%d", & choice);
        switch (choice)
        {
        case 1:
            addBook(library);
            break;
        case 2:
            showBooks();
            break;
        case 3:
            deleteBook();
            break;
        case 4:
            searchBooks();
            break;
        case 5:
            editBook();
            break;
        case 6:
            printStats();
            break;
        case 7:
            printf("Exiting...\n");
            return;
        default:
            printf("Invalid option. Try again.\n");
        }
    }
    while (choice != 7);
}

int main()
{
    system("cls");
    struct Book library[MAX_BOOKS];
    actionsWithBooks(library);
    return 0;
}
