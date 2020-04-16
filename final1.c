#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
int main(int arg1, char *arg2[])
{
    int filedescriptor[2]; 
	int fileSize; 
               int x; 

    char text[1024];  
	char copy[1024];  
    char* sourceFile = arg2[1]; 
    char* destFile = arg2[2]; 

  

    pipe(filedescriptor);
    if (pipe(filedescriptor)==-1)
    { 
        printf(stderr, "Pipe Failed" );
        return 1; 
    }  
 
    x = fork();
     if (x < 0) 
    { 
        printf(stderr, "Child Failed" ); 
        return 1; 
    } 

    if (x > 0) 
    {

	   int sourceFileNum; 
	   ssize_t numBytes; 

        close(filedescriptor[0]);
        sourceFileNum=open(sourceFile, O_RDONLY); 
        numBytes=read(sourceFileNum, text,sizeof(text)); 

        write(filedescriptor[1],text, numBytes); 
  
        close(filedescriptor[1]);

    }else if (x == 0){
    	
    	int destDesc;

        close(filedescriptor [1]); 
        ssize_t numBytesCh; 
        numBytesCh =read(filedescriptor[0], copy,sizeof(copy));

        close(filedescriptor[0]);
	    
        destDesc=open(destFile, O_CREAT | O_WRONLY); 

        write(destDesc, copy, numBytesCh); 
    }

    return 0; 
}
