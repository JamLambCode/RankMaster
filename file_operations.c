#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FILENAME "data.txt"

void printData(const char *filename){
    FILE *fp = fopen(filename, "r");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    int line_count = 0;

    if(fp == NULL){
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }
    //Get the first line of the file.
    line_size = getline(&line_buf, &line_buf_size, fp);

    while(line_size >= 0){
        line_count++;
        printf("%s", line_buf);
        //Line_buf stores contents data.
        char * token = strtok(line_buf, ",");
        line_size = getline(&line_buf,&line_buf_size,fp);
    }

    free(line_buf);
    line_buf = NULL;
    fclose(fp);


}



void clearData(const char* filename){

    //Simply by opening the file as write and closing
    //this will overwrite the data in the file

    FILE *fp = fopen(filename, "w");

    if(fp == NULL){
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE); 
    }

    fclose(fp);

}

void deletePair(const char* filename, int key) {
    FILE *fp = fopen(filename, "r");
    FILE *temp_fp;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    int found = 0;

    fp = fopen(FILENAME, "r"); 
    if (fp == NULL) {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    //Open a temporary file for writing
    temp_fp = fopen("temp_database.txt", "w"); 
    if (temp_fp == NULL) {
        printf("ERROR: Could not open file\n");
        fclose(fp); //close the original file before returning
        exit(EXIT_FAILURE);
    }

    while ((line_size = getline(&line_buf, &line_buf_size, fp)) != -1) {
        char *tmp = strdup(line_buf);
        if (!tmp) {
            perror("Failed to duplicate line buffer");
            break;
        }
        char *token = strtok(tmp, ",");
        if (atoi(token) != key) {
            //Write to temp file if not the key we want to delete
            fprintf(temp_fp, "%s", line_buf);
        } else {
            found = 1; 
            //Mark that we've found the key
            //Don't write this line to the temp file
        }
        free(tmp); //Free the duplicated string
    }

    free(line_buf);
    fclose(fp);
    fclose(temp_fp);

    if (found) {
        //Delete the original file and rename the temporary file
        remove(FILENAME);
        rename("temp_database.txt", FILENAME);
    } else {
        //If we didn't find the key, delete the temporary file and report error
        remove("temp_database.txt");
        printf("Key not found\n");
    }
}



char *getValue(const char* filename, int key){
    FILE *fp = fopen(filename, "r");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;


    if(fp == NULL){
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE); 
    }

    //Get the first line of the file.
    line_size = getline(&line_buf, &line_buf_size, fp);

    while(line_size >= 0){
        line_count++;
        char* tmp = strdup(line_buf);
        char * token = strtok(line_buf, ",");
        if(atoi(token) == key){
            return tmp;
        }
        line_size = getline(&line_buf,&line_buf_size,fp);
    }

    free(line_buf);
    line_buf = NULL;

    fclose(fp);

    //If we get here then we could not find the key
    return "ERROR";

}

int putValue(const char *filename, int key, const char *value) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }
    
    //Write the key-value pair to the file
    fprintf(fp, "%d: %s\n", key, value);
    fclose(fp);
    
    return EXIT_SUCCESS; 
}

void append_basic(const char *filename, const char *item) {
    //Append the new item to the file
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s\n", item);
    fclose(fp);
}

void display_numbered(const char *filename) {
    FILE *fp = fopen(filename, "r");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    //Count is starting at the first line
    int count = 1;  

    if (fp == NULL) {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    //Read and print each line of the file with the line number
    while ((line_size = getline(&line_buf, &line_buf_size, fp)) != -1) {
        printf("%d. %s", count++, line_buf);  
    }

    //Free the dynamically allocated buffer
    free(line_buf);  
    fclose(fp);      
}

void delete_string(const char *filename, const char *target) {
    FILE *fp = fopen(filename, "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    int target_found = 0; //Flag to check if the target string was found and deleted

    
    if (fp == NULL || temp_fp == NULL) {
        printf("ERROR: Could not open file\n");
        if (fp != NULL) fclose(fp);
        if (temp_fp != NULL) fclose(temp_fp);
        exit(EXIT_FAILURE);
    }

    //Read through the file line by line
    while ((line_size = getline(&line_buf, &line_buf_size, fp)) != -1) {
        //Write all lines to the temp file except the one that contains the target string
        if (strstr(line_buf, target) == NULL) {
            fputs(line_buf, temp_fp);
        } else {
            target_found = 1; //Set the flag if the target string is found
        }
    }

    //Free the dynamically allocated memory and close the files
    free(line_buf);
    fclose(fp);
    fclose(temp_fp);
    
    //If the target string was found and the temporary file was created, replace the original file
    if (target_found) {
        //Remove the original file
        if (remove(filename) != 0) {
            perror("Error removing original file");
        }
        //Rename the temporary file to the original file
        else if (rename("temp.txt", filename) != 0) {
            perror("Error renaming temporary file");
        }
    } else {
        //If the target string wasn't found, delete the temporary file
        remove("temp.txt");
    }
}

void deleteFile(const char *filename) {
    // Attempt to delete the file
    if (remove(filename) != 0) {
        //If remove() returns a non-zero value, there was an error
        printf("ERROR: Failed to remove original file");
        exit(EXIT_FAILURE);
    }
    //Otherwise the file is simply removed
}