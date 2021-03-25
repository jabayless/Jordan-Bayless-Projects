//Program will count characters in the file and use shared memory to pass information between running processes

Example run:
change directories to bin/
./Starter infile.txt


1.) The function to create a pipe is pipe(fd); // where fd is a 1D array of 2 ints.2.) The function used to map shared memory is mmap(). An example would be:
mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryLow, 0);
3.) The function to open the shared memory for reading or writing is mmap(). Example is:
int memory = shm_open(Lowname, O_RDWR | O_CREAT, 0666);
