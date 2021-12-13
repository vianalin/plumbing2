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
	
		
	while(1) { //if parent process ends before child, childs new parent pid is 1
		
		//constantly prompts a user for input
		printf("input: ");
			
		//sends that input to child 
		char line[20];
		fgets(line, 20, stdin);
		write(child, line, sizeof(line)); //writing into child line in size bytes
		
		//displays the response to the user
		char s[20];
		read(parent, s, sizeof(s)); //reading from parent
		printf("response from child: %s\n", s);
	}

	return 0; 
}

