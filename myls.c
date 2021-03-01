/*
Ivan Stus - 821201908
Kenny Kieu - 819180993
CS 570-05
Spring 2021
Assignment #1 - ls command
Description - Shell that replicates ls command in Unix.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int opt;
int hFlag = 0;
int resetHFlag = 0;

int main (int argc, char **argv) {
    struct dirent *Direct;
    DIR *pDirect;

    if (argc < 1) {     //Initial prompt error check
       printf("Invalid Prompt");
    }
    
    while (opt = getopt(argc, argv, "h") != -1) {   //Signifies "-h" hidden files exist
        hFlag = 1;        
    }

    if (argc == 1 || (hFlag == 1 && argc == 2)) {   //{"myls ' '" & myls -h"} cases 
        char cwd[PATH_MAX];    
        getcwd(cwd, sizeof(cwd));   //Gets current working directory
        pDirect = opendir (cwd);    //Open directory
        printf("%s\n", cwd);        //Print directory name
        if (pDirect == NULL) {
            printf ("Cannot open directory '%s'\n", cwd);
            return 1;
        }
        // Process each entry.
        while ((Direct = readdir(pDirect)) != NULL) {   //Reading directory contents
            if (hFlag == 1) {   //Hidden files are printed
                if(strcmp(Direct->d_name,"..") != 0 && strcmp(Direct->d_name, ".") != 0)
                    printf ("%s\n", Direct->d_name);
            } else {    //All non-hidden files are printed
                if((strcmp(Direct->d_name,"..") != 0) && (strcmp(Direct->d_name, ".") != 0) && (Direct->d_name[0] != '.'))
                    printf ("%s\n", Direct->d_name);
            }
        }
        closedir(pDirect);
    }

    else {  
        int i;      
        for (i = 1; i < argc; i++) {    //Accepts functioning of myls with multiple arguments                       
            if (hFlag == 1) {   //Skip over "-h" and onto next command line argument               
                i++;
                resetHFlag = 1;
                hFlag = 0;
            }
            pDirect = opendir (argv[i]);    //Open specified directory
            printf("%s\n", argv[i]);
            if (pDirect == NULL) {  //Unable to access directory
                printf ("Cannot open directory '%s'\n", argv[i]);
                return 1;
            }
        // Process each entry.
            while ((Direct = readdir(pDirect)) != NULL) {
                if (resetHFlag == 1) {
                    if(strcmp(Direct->d_name,"..") != 0 && strcmp(Direct->d_name, ".") != 0)
                        printf ("%s\n", Direct->d_name);    //Hidden files are included
                } else {
                    if((strcmp(Direct->d_name,"..") != 0) && (strcmp(Direct->d_name, ".") != 0) && (Direct->d_name[0] != '.'))
                        printf ("%s\n", Direct->d_name);    //List all non hidden files
                }
            }                        
        }
        closedir(pDirect);
    }
}
