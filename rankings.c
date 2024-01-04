#include "file_operations.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


//Loosely define some info regarding how we are gonna format input and output info
#define MAX_RANKINGS 10
#define CATEGORY_NAME_LEN 256
#define RANKING_LEN 256
#define FILENAME_FORMAT "%s_rankings.txt"
#define CATEGORIES_FILE "categories.txt"




int is_empty(const char *s) {
//Traverse the string until we get to the end
  while (*s != '\0') {
    //If a single thing that isn't whitespace is found then we return that it is not empty
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
  //Else 1 means that it is empty
  return 1;
}

void prompt_for_rankings(const char *category) {
    char filename[CATEGORY_NAME_LEN];

    //Creating the custom file to store data
    snprintf(filename, sizeof(filename), FILENAME_FORMAT, category);

    //String for what you are ranking
    char ranking[RANKING_LEN];
    
    //Initializing how we are keeping track of the rankings
    int rank = 1;

    printf("Enter your top %d rankings for %s:\n", MAX_RANKINGS, category);

    //Clear existing data for this category
    clearData(filename); 

    //Take rankings and store them in file
    for (int i = 0; i < MAX_RANKINGS; ++i) {
        printf("Rank %d: ", i + 1);
        if (fgets(ranking, RANKING_LEN, stdin) != NULL) {
            //Remove newline character if present
            size_t len = strlen(ranking);
            if (len > 0 && ranking[len - 1] == '\n') {
                ranking[len - 1] = '\0';
            }
            if(is_empty(ranking)){
                //Joke message if empty
                putValue(filename, rank++, "I guess you're not very good at ranking");

            }
            else{
                putValue(filename, rank++, ranking);
            }
        }
    }
    //Used for later display
    append_basic(CATEGORIES_FILE ,category);
}


int main() {
    //This string category is initialized here and can only be as big as we define at the top
    char category[CATEGORY_NAME_LEN];

    //Also have a string for option
    char option[RANKING_LEN];

    printf("Do you want to see 'all' rankings, 'display' one, 'create' one, or 'delete' one? ");
    if (fgets(option, RANKING_LEN, stdin) == NULL) {
        printf("ERROR: Couldn't read input.\n");
        exit(EXIT_FAILURE);
    }
    option[strcspn(option, "\n")] = '\0';


    if (strcmp(option, "display") == 0) {
        display_numbered(CATEGORIES_FILE);
        printf("Enter the name of the ranking you want to display: ");
        if (fgets(category, CATEGORY_NAME_LEN, stdin) == NULL) {
            printf("ERROR: Couldn't read input.\n");
            exit(EXIT_FAILURE);
        }
        //Remove newline character
        category[strcspn(category, "\n")] = '\0';  
        
        //Check if the input is empty
        if (is_empty(category)) {
            printf("You must enter a category name.\n");
            exit(EXIT_FAILURE);
        }

        //Construct the filename for the chosen category
        char filename[CATEGORY_NAME_LEN];
        snprintf(filename, sizeof(filename), FILENAME_FORMAT, category);
        
        //Call printData to print the rankings for the chosen category
        printData(filename);

    } else if (strcmp(option, "create") == 0) {
        printf("What category would you like to rank? ");
        if (fgets(category, CATEGORY_NAME_LEN, stdin) == NULL) {
            printf("ERROR: Couldn't read input.\n");
            exit(EXIT_FAILURE);
        }
        //Remove newline
        category[strcspn(category, "\n")] = '\0';  
        prompt_for_rankings(category);
    } 
    else if (strcmp(option, "delete") == 0) {
        //Display all categories
        display_numbered(CATEGORIES_FILE);
        
        //Ask the user for the specific ranking category they want to delete
        printf("Enter the name of the ranking you want to delete: ");
        if (fgets(category, CATEGORY_NAME_LEN, stdin) == NULL) {
            printf("ERROR: Couldn't read input.\n");
            exit(EXIT_FAILURE);
        }
        //Remove newline
        category[strcspn(category, "\n")] = '\0';
        
        //Check if the input is empty
        if (is_empty(category)) {
            printf("ERROR: Couldn't read input.\n");
            exit(EXIT_FAILURE);
        }

        //Construct the filename for the chosen category
        char filename[CATEGORY_NAME_LEN];
        snprintf(filename, sizeof(filename), FILENAME_FORMAT, category);
        //Check if the ranking file exists
    if (access(filename, F_OK) != -1) {
        //File exists... delete

        //remove the category from CATEGORIES_FILE
        printf("here is the category %s",category);
        delete_string(CATEGORIES_FILE, category);
        deleteFile(filename);

        printf("Ranking '%s' deleted successfully.\n", category);
    } else {
        //File does not exist
        printf("The ranking file for '%s' does not exist.\n", category);
    }
    }
    else if(strcmp(option, "all") == 0){
        display_numbered(CATEGORIES_FILE);
    }
    else {
        printf("Invalid option.\n");
    }

    return EXIT_SUCCESS;
}
