#include <iostream>
#include <string>
#include <vector>

using namespace std;

//prototype functions
//check the input string for errors
bool errorChecker(char *argv[]);

//get the output base
char outputBase(int argc, char *argv[]);

char mathOperation(int argc, char *argv[], string fullArguments);

int main(int argc, char *argv[]){
    string fullArguments;
    //the individual elements of the command line arguments
    char baseOutput;
    char mathOperator;
    vector<string> operands;
    bool operationSet = false;


    //get the baseOutput
    baseOutput = outputBase(argc, argv);
    //code testing
    cout << "base output is set to " << baseOutput << '\n';

    //get the math operation to perform
    for(int i = 0; i < argc; i++){
        fullArguments+= argv[i];
    }
    mathOperator = mathOperation(argc, argv, fullArguments);
    cout << "The math operation to perform is " << mathOperator << '\n';
    if(mathOperator == 'E'){
        cerr << "the math operation to perform is a mandatory argument, please provide it\n";
        exit(1);
    }



    return 0;
}




bool errorChecker(char *argv[]){
bool isCorrect = true;
}

//get the output base
char outputBase(int argc, char *argv[]){
char outPutBase;
        string firstArg = argv[1];
        //check if there is an argument set to - in the string
        if((firstArg[0] == '-')){
            if((firstArg[1] == 'o') || (firstArg[1] == 'h') || (firstArg[1] == 'd')){
               outPutBase = firstArg[1];
               }
            else if(firstArg[1] == 0){
                    outPutBase = 'd';
            }
        }
        else{
            outPutBase = 'd';
        }
return outPutBase;
}


char mathOperation(int argc, char *argv[], string fullArguments){

char mathOperator = 'E';

for(int i = 1; i < argc ; i++ ){
        string myArgs = argv[i];

        for(int j = 0 ; j < fullArguments.length(); j++){
            if((fullArguments[j] == 39) && (fullArguments[j+1] == '*')){
                mathOperator = '*';
            }
        }

    if((myArgs == "-o") || (myArgs == "-h") || (myArgs == "-d")){
        //do nothing, the value should already have been set
    }
    else if(myArgs[0] == '+'){
        mathOperator = '+';
    }
    else if(myArgs[0] == '-'){
        mathOperator = '-';
    }
    else if(myArgs[0] == '/'){
        mathOperator = '/';
    }
}

return mathOperator;
}
