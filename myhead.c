// Hillari Denny
// CSCE A320 - Operating Systems
// Assignment 2
//
// This program recreates the head program using sys calls with a default size of 10 lines
// 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 4096
#define DEFAULT_LINES 10

int main (int argc, char* argv[]) {

//-----Set either a default value of 10 lines or parse command line to get number of lines-----//
		int numLines;
		char* path;

		if (argc == 2) {
			path = argv[1];
			numLines = DEFAULT_LINES;
	    } else {
			path = argv[2];
			numLines = atoi(argv[1]); 
		}
		
		char buf[BUF_SIZE]; //buffer for reading/writing
		int bytes_read; //integer to determine how much was read, for write paramater
		int n; //to keep track of newline chars

        int fd = open(path, O_RDONLY); //creates a file descriptor
		if (fd == -1) {
			perror("Error attempting to open file");  //checks for error opening file
			exit(1); //error exit
		}

		if(strcmp(argv[2], "-")) {
			puts("Error. Usage is: $ ./myhead <n> filename.txt");
		}


	while ((bytes_read = read(fd, buf, BUF_SIZE)) > 0 ) { //read from file descriptor
			if (bytes_read == -1) {
				perror("Error reading file"); 
			}

			for (int i =0; i < bytes_read; ++i) {  //loop through the bytes text file and write accordingly
				if (buf[i] == '\n') {
					n += 1;  //counting newlines

					if (n==numLines) { //once we reach the number of lines requested, write the bytes to terminal and then exit
					   write(1,buf,i+1);
					   exit(0); //normal exit
					}
				}	 
								
			}
			
	}
		close(fd); //closing the file after we are done
}