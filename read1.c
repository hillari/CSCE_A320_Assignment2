// Hillari Denny
// CSCE A320 - Operating Systems
// Assignment 2
//
// This program uses system calls to read data from a specified file. Output from time and descripton of
// read vs fread is seen below code

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 4096 
int main (int argc, char* argv[]) {

	char* file = argv[1];
	char buf[BUF_SIZE]; 
	ssize_t bytes_read;

//Create a file dsicriptor for the specified file and check for open error
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		exit(1);
	}
//Read the bytes from fd to buffer for up to 4096 bytes and check for error
	bytes_read = read(fd, buf, BUF_SIZE);
	if (bytes_read == -1) {
		perror("File read error");
		exit(1);
	}

close(fd);

}

//******read1 output: /usr/share/dict/words ******

// real	0m0.002s
// user	0m0.000s
// sys	0m0.004s

//******fread output: /usr/share/dict/words ******

// real	0m0.006s
// user	0m0.000s
// sys	0m0.000s


//The difference between read and fread is that the read family is a system call, so goes to the kernel for the call, and is
//an unbuffered read. It tries to read the user specified number of bytes
//fread, however, is a C standard library call.  It is a buffered read so can be faster in certain implementations,
//It uses an internal buffer and in many systems (but not all), fread will call read

