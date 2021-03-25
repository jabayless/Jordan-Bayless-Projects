#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>

int main(int argc, char * argv[]){
   // printf("the letter is %s\n\n",argv[1]);

    //set return value initially to false
    int returnValue = 0;

//check to make sure correct number of arguments were received
//produce error if it wasn't correct
if(argc != 2){
    printf("Incorrect number of arguments, only one character should be provided in: %s", argv[0]);
}
else{
    //get the value from the user
    int codedValue = ((int)(argv[1][0]));

    //print the process id
    pid_t pid = getpid();
    printf("LowAlpha[%d]: ", pid);
    if(((codedValue >= 65) && (codedValue <= 77)) || ((codedValue >= 97) && (codedValue <= 109))){
        returnValue = 1;
    }

    //print off the value received by command line
    printf("Received coded value %d.\n", codedValue);
}
if(returnValue == 1){
    printf("LowAlpha[%d]: Result is true.\n", getpid());
}
else{
    printf("LowAlpha[%d]: Result is false.\n", getpid());
}

return returnValue;
}
