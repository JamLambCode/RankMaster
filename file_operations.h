#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

//just declaring not defining
void printData(const char *filename);
void clearData(const char* filename);
void deletePair(const char* filename, int key);
char *getValue(const char* filename, int key);  
int putValue(char* filename, int key, char* value);
void append_basic(const char *filename, const char *category);
void display_numbered(const char *filename);
void delete_string(const char *filename, const char *target);
void deleteFile(const char *filename);




#endif // FILE_OPERATIONS_H

//value frequency

//asks users to rank their favorite things and then puts those into seperate files