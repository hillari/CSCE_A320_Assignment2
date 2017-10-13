// Hillari Denny
// CSCE A320 - Operating Systems
// Assignment 2
//
// This program creates a pipe and forks off a child to execute commands and send the output of those commands to the parent
// 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char* argv[]) {
	char buf[4098]; 
	int fd[2]; //The first int in array is set up for reading, while the second integer is set up for writing
	pid_t pid; //pid_t for portability
	ssize_t bytes_read; //for read command

//create pipe and check for error	
	if (pipe(fd)==-1) {
		perror("Pipe error");
		exit(1);
	}  

//create child process and check for error
	if((pid = fork()) == -1) {
		perror("Fork error");
		exit(1);
	}

//*****If the parent receive data from the child, it closes fd1, and the child should close fd0
  //++CHILD++//
	if (pid == 0) { 
		if(close(fd[0])== -1) { //child process close stdin/RD side of fork since it's writing
			perror("Close error");
			exit(1);
		} 

		if (dup2(fd[1],STDOUT_FILENO) == -1) { //redirect stdout to fd[1] (wr end of pipe)
			perror("Could not dupe2 output side to fd[1] (stdout)");
			exit(1);
		} 


		if (execvp(argv[1], argv +1) == -1) { //execute command line arguments
			perror("Execve error");
			exit(1);
		}  

  //++PARENT++// - should read from pipe and write to stdout
	} else { 
		if (close(fd[1])==-1) { //close write end of pipe
			perror("Close error");
			exit(1);
		} 

//Read from fd (0 for stdout), and use write to print the command results to terminal (1 for stdout)
		while(bytes_read = read(fd[0], buf, 1) != 0) {
			if (bytes_read == -1) {
				perror("Read error");
				exit(1);
			}
			write(1,buf,1);
		}
		waitpid(pid, 0, 0); //wait for child to die	
	}
	close(*fd);
}
