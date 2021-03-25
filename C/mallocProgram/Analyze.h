#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//prototype functions
//returns the number of iterations of the program to run
int get_iteration_count(int rand);

//function called once per iteration to generate an array size between 100 and 799
int get_arr_size(int rand);

//generate a random number to fill the array
int get_arr_val(int rand);

//this function calls the other functions inside of Analyze.c
float get_running__ratio();

//check if that number is a perfect square
int isPerfectSquare(int number);

double get_running_ratio(){
    int *p;
    //generate a random number to be the number of iterations the program will run
    int randomNumber = rand();
    int randomIterationCount = get_iteration_count(randomNumber);

    //loop loop through the iterations of the program
    //and calculate the average for that run
    int k = 0;
    double sum = 0.0;
    double average = 0.0;
    double perfectSquareCount = 0;
    double notPerfectSquareCount = 0;
    for(k=0; k < randomIterationCount; k++){

    //generate a random number that will be used as the size of the array
    int randArraySize = get_arr_size(rand());
    //build the array of that size
    p = (int*)malloc(sizeof(int)*randArraySize);

    //fill the array with random numbers
    int i ;
    for(i = 0 ; i < randArraySize; i++){
       p[i] = get_arr_val(rand());
    }
    //for debugging, print the array
    int j;

    //loop through array and check if each element is a perfect square
    for(j=0; j < (randArraySize); j++){
        if(isPerfectSquare(p[j])){
        perfectSquareCount++;
        }
    else{
        notPerfectSquareCount++;
    }

    }// end loop for the single

    //determine the number of numbers that are perfect squares
    double perfectSquareRatio = ((double)perfectSquareCount / (double)notPerfectSquareCount);
    printf("ratio for array %d is %f \n",k, perfectSquareRatio);

    //add the current ratio of perfect squares to the other iterations
    sum = (sum + perfectSquareRatio);
    free(p);
    }

    //compute the average across all iterations
    average = (sum / randomIterationCount);
        return average;
}

//Functions specified in design implementation
int get_iteration_count(int rand){
    int high = 499;
    int low = 100;
    return (rand % ((high - low + 1) + low));
}

int get_arr_size(int rand){
    int high = 799;
    int low = 100;
    return (rand % ((high - low + 1) + low));
}

int get_arr_val(int rand){
    int high = 999;
    int low = 1;
    return (rand % ((high - low + 1) + low));
}

int isPerfectSquare(int number){
    int iVar;
    float fVar;
    double myNumber = (double)number;
    fVar=sqrt(myNumber);
    iVar=fVar;

    if(iVar==fVar)
        return 1;
    else
        return 0;
}
