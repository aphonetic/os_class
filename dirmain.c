#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

struct movie
{
    char *title;
    char *year;
    char *languages;
    char *rating;
    struct movie *next;
};

// Parse the current line which is space delimited and create a
// student struct with the data in this line
struct movie *createMovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->year, token);

    // The next token is the Languages
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->rating, token);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}

// Return a linked list of movies by parsing data from
// each line of the specified file.
struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    int firstLine = 1;
    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        if (firstLine)
        {
            firstLine = 0;
            continue;
        }
        // Get a new student node corresponding to the current line
        struct movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    return head;
}

void displayMainMenu()
{
    //Simple function to automate displaying the start menu options
    printf("1. Select file to process\n");
    printf("2. Exit Program\n");
    printf("Please enter an option.\n");
}

void displayDirMenu()
{
    //Simple function to automate displaying the directory menu options
    printf("Which file you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n");
    printf("Please enter an option.\n");
}

//a function to process the largest file
struct movie *processLargeFile(){

    // opens the current directory

    // looks through files
    // and saves the name of the largest file

    //then processes the file

    //then passes the new movie list as an arg to makeDirectory

}

//a function to process the smallest file
struct movie *processSmallFile(){

    // opens the current directory

    // looks through files
    // and saves the name of the smalled file

    //then processes the file

    //then passes the new movie list as an arg to makeDirectory

}

//a function to process a user chosen file
void processUserFile(){

    // create a variable for the file path
    //creates a variable for the flag
    int file_descriptor;

	char newFilePath[50];
    
    //prompts user for file
    printf("Please enter a filename: ");
    scanf("%s", newFilePath);

    //checks if file is valid

    // flags: the arguments are OR-ed togther
    // O_RDWR reading and writing
    // O_CREAT create an empty file if the file doesn't exist
    // O_TRUNC truncate the file if it already exists
    // mode:
    // 0600 Owner can read and write the file
	file_descriptor = open(newFilePath, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (file_descriptor == -1){
		printf("open() failed on \"%s\"\n", newFilePath);
		perror("Error");
		return;
	}

    //then processes the file

    struct movie *list = processFile(newFilePath);

    printf("The list was processed.\n");

    //then passes the new movie list as an arg to makeDirectory

    //makeDirectory(list);
}

void makeDirectory(struct movie * list){

    //receives the path name

    //creates a new directory

    //sets permissions for that directory

    //opens that new directory

    //writes a text file for the directory

    //shows close statement

    //closes the file

    //closes directory

}

// Compile the program as follows:
// gcc --std=gnu99 -o directories dirmain.c
int main()
{
    while (1)
    {
        int * choice;
        //int * dirChoice;
        displayMainMenu();
        scanf("%d", &choice);
        printf("choice equals: %d.\n", choice);

        switch(*choice) {

            case 1:
                displayDirMenu();
                scanf("%d", &choice);
                printf("choice equals: %d.\n", choice);

                switch(*choice) {

                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    default:
                        printf("This is not an option. Returning to main menu.\n");
                }

                break;
            
            case 2:
                return EXIT_SUCCESS;

            default:
                printf("This is not an option. Please try again.\n");
        }
    }

    return EXIT_SUCCESS;
}
