#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


#define READ 0
#define WRITE 1

//design a program that uses unnamed pipes to facilitate parent/child process communication
//a pipe is a conduit in memory between 2 separate processes on the same comp
//2 ends: read end [0] and write end [1]
int main() {

	//in order to facilitate 2 way communication, you will need 2 pipes
	
	//to child
	int child;
	
	//to parent
	int parent;

	mkfifo("child", 0644); //shell command to make a fifo, acts like regular file 
	mkfifo("parent", 0644);
	
	//open as file
	child = open("child", O_WRONLY);
	parent = open("parent", O_RDONLY);
	

	//gets input from parent
	char s[20]; 
	while(read(child, s, sizeof(s))) { //reading from child
		
	//processes the input: any of a number of string processes (all caps, all lower, reverse)
		s[strlen(s) - 1] = '\0';
		strcat(s, ":)"); //adding 
		s[strlen(s)] = '\0';
			
		//sends the response to parent
		write(parent, s, strlen(s) + 1); //writing into parent
		s[0] = '\0';
	}


	return 0;
}

