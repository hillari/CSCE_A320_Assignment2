// Hillari Denny
// CSCE A320 - Operating Systems
// Assignment 2
//
// This program creates a db file with 100 records


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

//struct declaration for DB records
	struct rec {
		unsigned int id;
		unsigned int name;
	};

int main (int argc, char* argv[]) {
	struct rec r;
	int errcode;

//~~~~~create a file and open it in write only mode, if it doesnt exist, create it~~~~~//
	char* dbFile = "myDB.txt";  
	int fd = open(dbFile, O_WRONLY | O_CREAT, 0666);
	if(fd == -1) {
		perror("Error opening file");
		exit(1);
	}
//create and write the records
for (int i = 0; i < 99; ++i) {
	r.id = i;
	r.name = i + 1000;
	int errcode = write(fd, &r, sizeof(struct rec));
}
	if(errcode == -1) {
		perror(" ");
		exit(1);
	}
	close(fd);
}