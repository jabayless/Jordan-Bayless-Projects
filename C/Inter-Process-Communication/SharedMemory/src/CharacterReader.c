#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define READ_END 0
#define WRITE_END 1
int main(int argc, char *argv[]){
//argv[1] is the name of the file

//determine number of arguments and read from a file
    char buffer[60000];

    /* open an existing file for reading */
    FILE *inFile = fopen(argv[1], "r");
    /* quit if the file does not exist */
    if (inFile == NULL){
        printf("Error in program: %s. File: %s does not exist.\n", argv[0],
               argv[1]);
        return 1;
    }
    else{
        int i = 0;
        while(1){
            // Taking input single character at a time
            char c = fgetc(inFile);
            //printf("Character is %c\n", c);
            // Checking for end of file
            if (feof(inFile)){
                break ;
            }
            else{
                if((c != '\n') && (c != '\r')){
                    buffer[i] = c;
                    i++;
                }
            }
        }
        fclose(inFile);
    }

    //send the data to the write end of the pipe
    int readPipe = atoi(argv[2]);
    write(readPipe, buffer, 60000);
    //close the write end of the pipe
    close(readPipe);
return 0;
}
