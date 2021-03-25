#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include<sys/wait.h>
#include <pthread.h>

int main(int argc, char *argv[]){

    //set return value initially to false
    int returnValue = 0;
    char returnString[10];

//check to make sure correct number of arguments were received
//produce error if it wasn't correct
    //get the value from the user
    int codedValue;
    int size;
    //print the process id
    //pid_t pid = getpid();
    //printf("LowAlpha[%d]: The array contains %s\n", pid, argv[2]);
    char *stringSize = argv[2];
    size = strlen(stringSize);
    //printf("size is %d\n", size);

    for(int i = 0; i  < size; i++){
    if(((int)argv[2][i]) != 0){
    //printf("%c", argv[2][i]);
    }
    codedValue = ((int)(argv[2][i]));
    if(((codedValue >= 65) && (codedValue <= 77)) || ((codedValue >= 97) && (codedValue <= 109))){
        returnValue++;
        //printf("\nCharacter is a LowAlpha\n");
        }
    }

   // printf("\nreturn value is %d\n", returnValue);
//create the shared memory

//name the shared memory object
const char *name = argv[1];
sprintf(returnString, "%d", returnValue);
//create a shared memory file descriptor
int fd;
//pointer to shared memory object
void *ptr;
//create the shared memory object
fd = shm_open(name, O_CREAT | O_RDWR, 0666);

if(fd == 0){
 printf("LowAlpha couldnt open shared mem\n");
}
//configure size of shared memory
ftruncate(fd, 256);
//memory map the shared memory object
ptr = mmap(0, 256, PROT_WRITE, MAP_SHARED, fd, 0);
//write to the shared memory object
sprintf(ptr, "%s", returnString);
ptr += strlen(returnString);
printf("LowAlpha[%d]: counted %s\n", getpid(), returnString);

return 0;
}
