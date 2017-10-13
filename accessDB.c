// Hillari Denny
// CSCE A320 - Operating Systems
// Assignment 2
//
// This program will use fseek to access random records in a db file


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

int main(int argc, char* argv[]) {

	int bytesRead;
	int record; 
	struct rec r;
	int entry; //to store "random" entry in DB file
	off_t pos; //offset position fot lseek

	//Open the database file and assign to file descriptor fd
	int fd = open("myDB.txt", O_RDONLY);
	if (fd == -1) {
		perror("Cannot open file");
		exit(1);
	}
	//Loop through DB to random point in file and print next 10 records
	for (int i = 0; i < 10; i++) {
		entry = rand() % 100;
		pos = entry * sizeof(struct rec); //sets the position for lseek
		if (lseek(fd, pos, SEEK_SET) == -1) { //current file position of descriptor fd is set to pos
			perror("");
			exit(1);
		}
		// Read the given sturct into the r variable and error check
		bytesRead = read(fd, &r, sizeof(struct rec));
		if (bytesRead != sizeof(struct rec)) {
			perror("");
			exit(1);
		}
		printf("%d.) User ID: %u User Name: %u\n", i+1, r.id, r.name);
	}
	if (close(fd) == -1) {
		perror("Close error");
	}
}