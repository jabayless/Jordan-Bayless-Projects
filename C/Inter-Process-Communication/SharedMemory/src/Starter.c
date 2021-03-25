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

#include <pthread.h>


#define BUFFER_SIZE 60000
#define READ_END 0
#define WRITE_END 1

int main(int argc, char * argv[]) {
  //declare two char arrays to store the message on either end of the pipe
  char read_msg[BUFFER_SIZE];

  //Size of the shared memory object
  const char * Lowname = "SHM_LowAlpha";
  //shared memory file descriptor
  int sharedMemoryLow;
  //pointer to the shared memory object
  void * LowPtr;
  //open the shared memory object
  sharedMemoryLow = shm_open(Lowname, O_RDWR | O_CREAT, 0666);

  if (sharedMemoryLow == 0) {
    printf("Error opening shared memory\n");
  }
  ftruncate(sharedMemoryLow, 256);
  //memory map the shm object
  LowPtr = (char * ) mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryLow, 0);
  //read from the shared memory object
  printf("Starter[%d]: Created shared memory \"SHM_LOWALPHA\" with FD: %d\n", getpid(), sharedMemoryLow);
  //remove shared memory object

  //Size of the shared memory object
  const char * Highname = "SHM_HighAlpha";
  //shared memory file descriptor
  int sharedMemoryHigh;
  //pointer to the shared memory object
  void * HighPtr;
  //open the shared memory object
  sharedMemoryHigh = shm_open(Highname, O_RDWR | O_CREAT, 0666);

  if (sharedMemoryHigh == 0) {
    printf("Error opening shared memory\n");
  }
  ftruncate(sharedMemoryHigh, 256);
  //memory map the shm object
  HighPtr = (char * ) mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryHigh, 0);
  printf("Starter[%d]: Created shared memory \"SHM_LOWALPHA\" with FD: %d\n", getpid(), sharedMemoryHigh);

  //Size of the shared memory object
  const char * Mathname = "SHM_Math";
  //shared memory file descriptor
  int sharedMemoryMath;
  //pointer to the shared memory object
  void * MathPtr;
  //open the shared memory object
  sharedMemoryMath = shm_open(Mathname, O_RDWR | O_CREAT, 0666);

  if (sharedMemoryMath == 0) {
    printf("Error opening shared memory\n");
  }
  ftruncate(sharedMemoryMath, 256);
  //memory map the shm object
  MathPtr = (char * ) mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryMath, 0);
  printf("Starter[%d]: Created shared memory \"SHM_LOWALPHA\" with FD: %d\n", getpid(), sharedMemoryMath);

  //create file descriptor
  int fd[2];
  //create a process id
  pid_t pid;

  //create the pipe
  int pipeStat = pipe(fd);

  if (pipeStat == -1) {
    fprintf(stderr, "pipe failed");
    return 1;
  }

  //create a child process
  int stat1;
  pid = fork();
  //check if fork failed
  if (pid < 0) {
    fprintf(stderr, "fork failed");
    return 1;
  }
  //if parent process, close the read end of the pipe so you can write to it
  if (pid > 0) {
    //close the write end of the pipe
    close(fd[WRITE_END]);
    //printf("Starter: Forked process with ID %d\n", pid);
    //printf("Starter: Waiting for process [%d]\n", pid);
    wait( & stat1);
    int returnedReader = WEXITSTATUS(stat1);
    //printf("Parent: wait completed, exit status was %d\nreturned was %d\n", stat1, returnedLow);
    if (returnedReader == 0) {
      //     printf("Starter: Child process %d returned with status of %d (1 is bad, 0 is good).\n", pid, returnedReader);
    } else {
      printf("There was an error in CharacterReader\n");
      exit(1);
    }
    //read the message
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    //print the message read
    //printf("Parent process [%d] received message: %s\n",getpid(), read_msg);
  }
  //child process write message to the parent
  if (pid == 0) {
    close(fd[READ_END]);
    char buffer1[16];
    sprintf(buffer1, "%d", fd[1]);
    //  printf("the buffer sent in exec to CharacterReader contains file descriptor: %s\n", buffer1);
    execlp("./CharacterReader", "./CharacterReader", argv[1], buffer1, NULL);
    //increment the counters depending on the return status of the programs run
    printf("exec failed\n");
  }

  //create the LowAlpha program
  int stat2;
  pid_t pid1 = fork();
  if (pid1 > 0) {
    //  printf("Starter: Waiting for process [%d]\n", pid1);
    wait( & stat2);
    int returnedLow = WEXITSTATUS(stat2);
    if (returnedLow == 0) {
      //  printf("Starter: Child process %d returned with status of %d (1 is bad, 0 is good).\n", pid1, returnedLow);
      //printf("The value read from shared memory is %s\n", (char *)LowPtr);
    } else {
      printf("There was an error in LowAlpha\n");
      exit(1);
    }
  }
  //child process execute LowAlpha
  if (pid1 == 0) {
    char buffer2[60000];
    sprintf(buffer2, "%s", read_msg);
    // printf("Buffer being sent to process [%d] is: %s\n", getpid(), buffer2);
    execlp("./LowAlpha", "./LowAlpha", "SHM_LowAlpha", buffer2, NULL);
    printf("Exec failed for LowAlpha\n");
  }

  //create the HighAlpha program
  int stat3;
  pid_t pid3 = fork();
  if (pid3 > 0) {
    //printf("Starter: Waiting for process [%d]\n", pid3);
    wait( & stat3);
    int returnedHigh = WEXITSTATUS(stat3);
    if (returnedHigh == 0) {
      // printf("Starter: Child process %d returned with status of %d (1 is bad, 0 is good).\n", pid3, returnedHigh);
      // printf("The value read from shared memory is %s\n", (char *)HighPtr);
    } else {
      printf("There was an error in HighAlpha\n");
      exit(1);
    }
  }
  //child process execute HighAlpha
  if (pid3 == 0) {
    char buffer3[60000];
    sprintf(buffer3, "%s", read_msg);
    //printf("Buffer being sent to process [%d] is: %s\n", getpid(), buffer3);
    execlp("./HighAlpha", "./HighAlpha", "SHM_HighAlpha", buffer3, NULL);
    printf("Exec failed for HighAlpha\n");
  }

  //create the Math program
  int stat4;
  pid_t pid4 = fork();
  if (pid4 > 0) {
    //printf("Starter: Waiting for process [%d]\n", pid4);
    wait( & stat4);
    int returnedMath = WEXITSTATUS(stat4);
    if (returnedMath == 0) {
      //  printf("Starter: Child process %d returned with status of %d (1 is bad, 0 is good).\n", pid4, returnedMath);
      // printf("The value read from shared memory is %s\n", (char *)MathPtr);
    } else {
      printf("There was an error in Math\n");
      exit(1);
    }
  }
  //child process execute LowAlpha
  if (pid4 == 0) {
    char buffer4[60000];
    sprintf(buffer4, "%s", read_msg);
    // printf("Buffer being sent to process [%d] is: %s\n", getpid(), buffer4);
    execlp("./Math", "./Math", "SHM_Math", buffer4, NULL);
    printf("Exec failed for Math\n");
  }
  int size = strlen(read_msg);
  int sum = (atoi((char * ) LowPtr) + atoi((char * ) HighPtr) + atoi((char * ) MathPtr));
  int otherSize = size - sum;
  printf("Low alpha:  %s\n", (char * ) LowPtr);
  printf("High alpha: %s\n", (char * ) HighPtr);
  printf("Math:       %s\n", (char * ) MathPtr);
  printf("Other:      %d\n", otherSize);

  //read the shared memory from LowAlpha
  shm_unlink(Lowname);
  shm_unlink(Highname);
  shm_unlink(Mathname);
  return 0;
}
