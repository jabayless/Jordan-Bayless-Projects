#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
//determine number of arguments and read from a file
        FILE *infile;
        char *buffer;
        long numbytes;

//if the file name was not provided, throw an error
        if (argc != 2) {
                printf(
                "Error in program: %s. One argument (the file name) should be provided.\n",
                argv[0]);
                exit(1);
        }

        /* open an existing file for reading */
        infile = fopen(argv[1], "r");

        /* quit if the file does not exist */
        if (infile == NULL) {
                printf("Error in program: %s. File: %s does not exist.\n", argv[0],
                argv[1]);
                return 1;
        }

        else {
                //get the number of bytes from the file
                fseek(infile, 0L, SEEK_END);
                numbytes = ftell(infile);

                //get back to the beginning of the file
                fseek(infile, 0L, SEEK_SET);

                //allocate memory to the buffer
                buffer = (char*) calloc(numbytes, sizeof(char));
                //read the file into the buffer
                fread(buffer, sizeof(char), numbytes, infile);
                //close the open file
                fclose(infile);
                //print the file contents
                //printf("The file called %s contains this text\n\n%s\n",argv[1], buffer);

        }
//send the contents of the buffer to the programs
//create a counter for each program
        int mathCounter = 0;
        int upperAlphaCount = 0;
        int lowerAlphaCount = 0;
        int miscCounter = 0;

//create a process id variable
        pid_t pid1;

        int i;
//loop through all the characters in the buffer
        for (i = 0; i < numbytes; i++) {
                char character = buffer[i];
                char buffer1[5];
                sprintf(buffer1, "%c", character);
                //create a child process to run the other programs
                int stat1;
                pid1 = fork();
                if (pid1 > 0) {
                        printf("Starter: Forked process with ID %d\n", pid1);
                        printf("Starter: Waiting for process [%d]\n", pid1);
                        wait(&stat1);
                        int returnedLow = WEXITSTATUS(stat1);
                        //printf("Parent: wait completed, exit status was %d\nreturned was %d\n", stat1, returnedLow);
                        if (returnedLow == 1) {
                                printf("Starter: Child process %d returned true.\n", pid1);
                                lowerAlphaCount++;
                        }
                        //Low alpha was false, spawn new process
                        if (returnedLow == 0) {

                                printf("Starter: Child process %d returned false.\n", pid1);
                                int stat2;
                                pid_t pid2 = fork();
                                //parent process, wait for child to terminate
                                if (pid2 > 0) {
                                        printf("Starter: Forked process with ID %d\n", pid2);
                                        printf("Starter: Waiting for process [%d]\n", pid2);
                                        wait(&stat2);

                                        //get exit status of second forked process
                                        int returnedHigh = WEXITSTATUS(stat2);

                                        if (returnedHigh == 1) {
                                                printf("Starter: Child process %d returned true.\n",
                                                                pid2);
                                                upperAlphaCount++;
                                        }
                                        //Low alpha was false, spawn new process
                                        if (returnedHigh == 0) {
                                                printf("Starter: Child process %d returned false.\n",
                                                                pid2);
                                                int stat3;
                                                pid_t pid3 = fork();

                                                //parent process, wait for child
                                                if (pid3 > 0) {
                                                        printf("Starter: Forked process with ID %d\n",
                                                                        pid3);
                                                        printf("Starter: Waiting for process [%d]\n", pid3);
                                                        wait(&stat3);

                                                        //get exit status of second forked process
                                                        int returnedMath = WEXITSTATUS(stat3);

                                                        if (returnedMath == 1) {
                                                                printf(
                                                                                "Starter: Child process %d returned true.\n",
                                                                                pid3);
                                                                mathCounter++;
                                                        }
                                                        if (returnedMath == 0) {
                                                                printf(
                                                                                "Starter: Child process %d returned false.\n",
                                                                                pid3);
                                                                miscCounter++;
                                                        }
                                                }
                                                //child process execute math program
                                                if (pid3 == 0) {
                                                        execlp("./Math", "./Math", buffer1, NULL);
                                                        printf("exec failed\n");
                                                }
                                                //error
                                                if (pid3 < 0) {
                                                        printf("fork failed\n");
                                                }
                                                //spawn a new process
                                                //parent process, wait for child to terminate
                                        }
                                        //check if the return value was false, if it was spawn a new process and execute HighAlpha

                                }
                                //second forked child process
                                if (pid2 == 0) {
                                        execlp("./HighAlpha", "./HighAlpha", buffer1, NULL);
                                        printf("exec failed\n");
                                }
                                //check if its in the child process

                                //parent process of first fork checks to see if the child finished
                                if (pid1 < 0) {
                                        printf("fork failed \n");

                                }
                        }
                }
                if (pid1 == 0) {
                        //increment the counters depending on the return status of the programs run
                        execlp("./LowAlpha", "./LowAlpha", buffer1, NULL);
                        printf("exec failed\n");
                }
        }                //end for loop

//print the counters
        printf("Low Alpha:  %d\n", lowerAlphaCount);
        printf("High Alpha: %d\n", upperAlphaCount);
        printf("Math:       %d\n", mathCounter);
        printf("Other:      %d\n", miscCounter);

//deallocate the memory to the buffer pointer
        free(buffer);
        return 0;
}
