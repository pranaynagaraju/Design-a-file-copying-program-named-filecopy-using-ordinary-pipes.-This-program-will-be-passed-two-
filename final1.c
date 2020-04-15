#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    int fd[2];
	int fileSize;
	pid_t pid;

    char text[1024];
	char copy[1024];  

    char* sourceFile = argv[1];
    char* destFile = argv[2];

  

    pipe(fd);
    if (pipe(fd)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    }  
 
    pid = fork();
     if (pid < 0) 
    { 
        fprintf(stderr, "Fork Failed" ); 
        return 1; 
    } 

    if (pid > 0) 
    {

	   int sourceFileNum;
	   ssize_t numBytes; 

        close(fd[0]);
        sourceFileNum=open(sourceFile, O_RDONLY);
        numBytes=read(sourceFileNum, text,sizeof(text));

        write(fd[1],text, numBytes);
  
        close(fd[1]);

    }else if (pid == 0){
    	
    	int destDesc;

        close(fd[1]);
        ssize_t numBytesCh;
        numBytesCh =read(fd[0], copy,sizeof(copy));

        close(fd[0]);
    
        destDesc=open(destFile, O_CREAT | O_WRONLY);

        write(destDesc, copy, numBytesCh);
    }

    return 0;
}  
