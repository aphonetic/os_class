#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// commenting out original program because I would like to combine a few things
// struct for movie information */
struct movie
{
    char *title;
    char *year;
    char *languages;
    char *rating;
    struct movie *next;
};

void displayMenu()
{
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit\n");
    printf("Please enter an option.\n");
}

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

// Print data for the given student
void printMovie(struct movie* aMovie){
  printf("%s, %s %s, %s\n", aMovie->title,
               aMovie->year,
               aMovie->languages,
               aMovie->rating);
}
// Print the linked list of students
void printMovieList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

void yearReleaseList(struct movie * list)
{
    char choice[5];

    printf("Enter the year for which you want to see movies: ");
    scanf("%s", choice);

    while (list != NULL)
    {
        if (strcmp(choice, list->year) == 0)
        {
            printf("%s ", list->year);
            printf("%s\n", list->title);
        }

        list = list->next;
    }
}

void languageList(struct movie * list)
{
    char choice[20];
    printf("Enter the language for which you want to see movies: ");
    scanf("%19s", choice);

    int noMovies = 1;
    while (list != NULL)
    {
        char langcopy[40];
        strcpy(langcopy, list->languages);

        const char delimiters[] = "[];";
        char *token = strtok(langcopy, delimiters);
        while (token != NULL)
        {
            if (strcmp(choice, token) == 0)
            {
                noMovies = 0;
                printf("%s ", list->year);
                printf("%s\n", list->title);
                break;
            }
            token = strtok(NULL, delimiters);
        }
        list = list->next;
    }

    if (noMovies)
    {
        printf("There are no moves in %s.\n", choice);
    }
}

void ratingList(struct movie * list)
{
    printf("you are in rating release list\n");
    struct movie * iterator = list;

    int count = 1;

    int * yearArry = calloc(count, 4);
    int firstYear = atoi(iterator->year);
    yearArry[0] = firstYear;

    printf("value of year[0]: %d\n", yearArry[0]);
    printf("value of iterator->year: %s\n", iterator->year);
    while (iterator != NULL)
    {
        printf("in the while loop\n");
        int restartTrigger = 0;

        if (iterator != list)
        {
            printf("in the giant if statement\n");
            for (int i = 0; i < count; i++)
            {
                printf("in the for loop of the if statement\n");
                if (yearArry[i] == atoi(iterator->year))
                {
                    printf("yearArry[i] matched atoi(iterator->year\n");
                    iterator = iterator->next;
                    restartTrigger = 1;
                    continue;
                }
            }

            if (restartTrigger == 1)
            {
                printf("loop is about to be restarted\n");
                continue;
            }

            count++;
            printf("count is equal to %d\n", count);

            yearArry = (int*) realloc(yearArry, count * sizeof(int));

            printf("realloc just happened\n");

            int newVal = atoi(iterator->year);
            yearArry[count-1] = newVal;
        }

        printf("made it past the giant if statement\n");

        struct movie * tempPtr = iterator->next;
        struct movie * highPtr = iterator;

        while (tempPtr != NULL)
        {

            if (strcmp(tempPtr->year, highPtr->year) == 0)
            {
                
                if (strcmp(tempPtr->rating, highPtr->rating) > 0)
                {
                    highPtr = tempPtr;
                }
            }

            tempPtr = tempPtr->next;
        }

        printf("%s ", highPtr->year);
        printf("%s ", highPtr->rating);
        printf("%s\n", highPtr->title);

        iterator = iterator->next;

        if (iterator == NULL)
        {
            printf("breaking out of the big while statement for some reason\n");
            break;
        }
    }

    printf("exited the giant while statement, should exit function soon\n");

    free(yearArry);

    printf("yearArry free'd\n");
};

// Process the file provided as an argument to the program to
// create a linked list of student structs and print out the list.
// Compile the program as follows:
// gcc --std=gnu99 -o movies moviemain.c

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./students student_info1.txt\n");
        return EXIT_FAILURE;
    }

    struct movie *list = processFile(argv[1]);

    while (1)
    {
        int * choice;
        displayMenu();
        scanf("%d", choice);

        switch(*choice) {

            case 1:
                yearReleaseList(list);
                break;
            
            case 2:
                ratingList(list);
                break;

            case 3:
                languageList(list);
                break;
            
            case 4:
                return EXIT_SUCCESS;

            default:
                printf("This is not an option. Please try again.\n");
        }
    }

    //printMovieList(list);
    return EXIT_SUCCESS;
}
