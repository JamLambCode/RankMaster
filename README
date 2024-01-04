# RankMaster

## Description

RankMaster is a user-friendly program designed for creating, managing, and visualizing personal rankings across an unlimited range of categories. Data is all stored in **persistant** memory (it doesn't go away). The project is built in C so memory is managed efficiently and robustly; **File I/O** and **string manipulation** are key techniques used. Upon running the file, the user will be easily navigated through core functionality.


## Running Instructions

### Prerequisites
Ensure you have GCC (GNU Compiler Collection) installed on your system for compiling the C code.

### An example compilation would look something like this...

```
$ gcc -o rank rankings.c file_operations.c 
```

### After you have the object code, you can run it as an excecutable as follows... 

```
$ ./rank
```


## FUNCTIONALITY

#### 'create'
After selecting the create function,  a file will be created of the type{category}_rankings.txt. 
The user will then be prompted to 10 times and needs to give a string of some item from that category ranked. Once all 10 items are done,
the file will be populated with your rankings. On top of this, another file, categories.txt, will be created. This file keeps track of all 
the categories that you create.

#### 'delete'
Just as the user can create, they can also destroy. The delete functionality is simply the inverse function of what was just explained. The file 
keeping track of all the created categories is printed and from there the user can say the category they want deleted. Once input, the program searches
for the file with the rankings data and removes it before also removing the category from the categories.txt file as well.

#### 'display'
This function is as the name implies, it simply displays all of the categories that the user has ranked. It does this through reading the categories.txt 
file that we have been keeping track of.

#### 'all'
This function just displays all of the categories the user has ranked.