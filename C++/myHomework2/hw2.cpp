#include <iostream>
#include <string>
#include <vector>

using namespace std;

//prototype functions
char outputBase(int argc, char *argv[]);
char mathOperation(int argc, char *argv[], string fullArguments);
bool isNumber(string argument);
int binaryToDecimal(int n);
int stringToNumber(string argument, char outBase);
int performOperation(vector<int> myArray, char mathOperator, string fullArguments);
void convertOutput(int answer, char baseOutput);
int furthestFortyFive(vector<int> myArray);
int binaryToDecimal(int n);
void decToBinary(int n);
bool checkInput(string fullArguments,char *argv[], int argc);
bool isMathOperator(char c);
bool locationChecker(string fullArguments, char mathOperator, char baseOutput);
bool whiteSpaceChecker(string fullArguments);
bool isOutputBase(string argument);
bool divZero(vector<int> myArray, char mathOperator, string fullArguments);

//the only global variable
string programName;

//main function

int main(int argc, char *argv[]){

        string fullArguments;

        //get the math operation that the program will perform
        for(int i = 0; i < argc; i++){
        fullArguments+= argv[i];
        fullArguments+= " ";
            }

        //save program name
        programName = argv[0];

         //check for the right number of function arguments
    if(argc < 2){
        cerr << "There must be at least 2 additional arguments to the program name,\n";
        cerr << "the operation and at least one argument, you typed: " << fullArguments;
        cerr << "in program " << programName << endl;
        exit(1);
    }

    //get rid of warning
    if(argc == 1){
        cout << "";
    }

    //the individual elements of the command line arguments
    char baseOutput;
    char mathOperator;
    vector<int> operands;
    int answer = 0;

    //get the baseOutput
    baseOutput = outputBase(argc, argv);
    //code testing

    //check the input for illegal characters
    bool inputChecked = checkInput(fullArguments, argv, argc);
    if(inputChecked == false){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
    }
    //check for white space
    bool whiteSpace = false;
    whiteSpace = whiteSpaceChecker(fullArguments);
    if(whiteSpace == true){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
    }

    //get the math operation to perform
    mathOperator = mathOperation(argc, argv, fullArguments);
    //cout << "math operator is " << mathOperator << endl;
    if(mathOperator == 'E'){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
    }

    string indivArgs;
    //loop through the values in argv and see if they are numbers
    string allNumbers;
    for(int i = 0 ; i < argc; i++){
        indivArgs = argv[i];
        //cout << "Shit: " << indivArgs << "\n";

        if((indivArgs[0] == '0') && (indivArgs.length() == 1)){
            operands.push_back(stoi(indivArgs));
            //cout << operands[i] << "\n";
        }

        if(isNumber(indivArgs)){
                int indexOfFirstNumber = fullArguments.find_first_of(indivArgs);
               // cout << "index of first number is " << indexOfFirstNumber << endl;
                allNumbers = fullArguments.substr(indexOfFirstNumber+1);
                //cout << allNumbers << " are just the numbers" << endl;

            //if they are numbers, add them to the operands array
            operands.push_back(stringToNumber(indivArgs, baseOutput));
        }
    }

    //check for repeat math operator
    int mathOperatorCount = 0;
    for(int i = 0 ; i < ((int)allNumbers.length()); i++){
        if(isMathOperator(allNumbers[i])){
        mathOperatorCount++;
        }
        if(mathOperatorCount > 2){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
        }
    }

    //check if at least one number was provided through command line
    if(operands.size() < 1){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
    }


    //check for correct operand order
    bool goodInput = locationChecker(fullArguments, mathOperator, baseOutput);
    if(goodInput == false){
        cerr << "The parameters are in the wrong order, system exiting program " << programName << endl;
        exit(1);
    }


    //check to make sure that the full input is either a math operator, a
    //number or an output type
    for(int i = 1 ; i < argc ; i++){
            string arguments = argv[i];
        if(!(isMathOperator(arguments[0])) && (!isOutputBase(arguments))){
            if(!(isNumber(argv[i]))){
            cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
            exit(1);
        }
    }
}
    //all operands are to be printed
    answer = performOperation(operands, mathOperator, fullArguments);
    //cout << "answer in dec is " << answer << '\n';

    //print out the answer to the math problem
    convertOutput(answer, baseOutput);

    //terminate program correctly
    return 0;
}// end main




//get the output base
char outputBase(int argc, char *argv[]){
    if(argc == 1){
    }
char outPutBase;
        string firstArg = argv[1];
        //check if there is an argument set to - in the string
        if((firstArg[0] == '-')){
            if((firstArg[1] != 'o') && (firstArg[1] != 'h') && (firstArg[1] != 'd') && ((int)firstArg.length() == 2)){
                cerr << "Incorrect output base in program " << programName << " You typed: " << firstArg << endl;
                exit(1);
            }
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
int pos = 0;
int minusCount = 0;
int otherOperators = 0;
//find if there is a multiplication sign
pos = fullArguments.find_first_of('*');
//cout << "argc is " << argc << endl;
for(int i = 1; i < argc ; i++ ){
        string myArgs = argv[i];
      //  cout << "args are " << myArgs << endl;
      //  cout << "first letter is " << myArgs[0] << endl;
    if((myArgs == "-o") || (myArgs == "-h") || (myArgs == "-d")){
        //do nothing, the value should already have been set
    }
    //check minus signs
    if((myArgs[0] == '-') && !(isalpha(myArgs[1])) && (!isMathOperator(myArgs[1]))){
      //  cout << "in minus " << endl;
        //check minus signs
        minusCount++;
        mathOperator = '-';
        //check for a negative number
        if(isdigit(myArgs[1])){
            cerr << myArgs << " is a negative numbers, negatives are not allowed in program " << programName << " System exiting" << endl;
            exit(1);
            }
        else if(myArgs[1] == '-'){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
        }
        else{
        }
    }
    if(myArgs[0] == '+'){
        otherOperators++;
        mathOperator = '+';
    }
    else if(myArgs[0] == '@'){
        otherOperators++;
        mathOperator = '@';
    }
    else if(myArgs[0] == '/'){
        otherOperators++;
        mathOperator = '/';
    }
    else if((mathOperator == 'E') && (pos != -1)){
        otherOperators++;
        mathOperator = '*';
    }
}
if((minusCount > 2) || (otherOperators > 1)){
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
}
else{
//cout << "otherOperators count is " << otherOperators << " minus count is " << minusCount << endl;
}
return mathOperator;
}




bool isMathOperator(char c){
    bool isOperator = false;
if((c == '+') || (c == '-') || (c == '/') || (c == '*') || (c == '@')){
        isOperator = true;
    }
    return isOperator;
}





//check to see if the string is a number
bool isNumber(string argument){
bool isNumber = false;
int argLength = argument.length();
//bool test = true;

if((argument[0] == '0') && (argLength == 1)){
    return isNumber = true;
}

//check if all of the numbers are digits in decimal format
if((argument[0] != '0') && (isdigit(argument[0]))){
    for(int i = 0 ; i < argLength; i++){
            if(!isdigit(argument[i])){
                cerr << argument << " is a decimal number but contains a non decimal input in program " << programName << endl;
                exit(1);
                }
            else{
                isNumber = true;
                    }
                }
}// end check if all the digits are digital

//if its an octal number
if((argument[0] == '0')){
       // cout << "in octal\n";
        int i;
        for(i = 1 ; i < (argLength); i++){
            if(argLength == 1){
                return isNumber = true;
                break;
            }
            if((isdigit(argument[i])) && (argument[i] != '8') && (argument[i] != '9')){
                isNumber = true;
            }
        }
}// end check octal

//the number is a standard hex number
if((argument[0] == '0') && (argument[1] == 'x')){
        int i;
    for(i = 2 ; i < (argLength); i++){
        if(isdigit(argument[i]) || (argument[i] == 'a') || (argument[i] == 'b') ||
           (argument[i] == 'c') || (argument[i] == 'd') || (argument[i] == 'e') ||
           (argument[i] == 'f')){
               isNumber = true;
           }
           else{
            cerr << " hex statement " << argument << " ";
           }
    } // end hexCheck
}

//the number is a standard binary number
if((argument[0] == '0') && (argument[1] == 'b')){
        int i;
        for(i = 2 ; i < (argLength); i++){
            if((argument[i] == '0') || (argument[i] == '1')){
                isNumber = true;
               }
            else{
                cerr << argument << " is binary but contains a non 1 or 0 character in program " << programName << endl;
                exit(1);
            }
        }
}//end check binary

//check if number was tested for decimal output
//if(test == true){
//    isNumber = true;
//}
//cout << "argument is " << argument << endl;
return isNumber;
}



int stringToNumber(string argument, char outBase){
    int decimalNumber;
    if(outBase == 'o'){
        decimalNumber = stoi(argument, nullptr, 8);
    }
    if((argument[0] == '0') && (argument[1] == 'b')){
            int pos = argument.find_first_of('b');
            string binaryNumber = argument.substr(pos+1);
            int binaryInt = stoi(binaryNumber);
               decimalNumber = binaryToDecimal(binaryInt);
    }
    else{
        decimalNumber = stoi(argument, nullptr, 0);
    }
    return decimalNumber;
}




int performOperation(vector<int> myArray, char mathOperator, string fullArguments){
    int answer = myArray[0];
    bool checkDivZero = false;
    checkDivZero = divZero(myArray, mathOperator, fullArguments);

    if(checkDivZero == false){

if(mathOperator == '+'){
    for(int i = 1 ; i < ((int)myArray.size()); i++){
        answer = answer + myArray[i];
    }
}
if(mathOperator == '-'){
    for(int i = 1 ; i < ((int)myArray.size()); i++){
        answer = answer - myArray[i];
    }
}
if(mathOperator == '*'){
    for(int i = 1 ; i < ((int)myArray.size()); i++){
        answer = answer * myArray[i];
    }
}
if(mathOperator == '/'){
    for(int i = 1 ; i < ((int)myArray.size()); i++){
        answer = answer / myArray[i];
        }
    }
if(mathOperator == '@'){
    int furthest = furthestFortyFive(myArray);
    answer = furthest;
        }
    }
    return answer;
}// end performOperation



void convertOutput(int answer, char baseOutput){
    string output;
    if(baseOutput == 'd'){
        cout << dec << answer << endl;
    }
    if(baseOutput == 'h'){
            if(answer < 0){
                cout << "-";
            }
            answer = abs(answer);
        cout << hex << answer << endl;
    }
    if(baseOutput == 'b'){
       decToBinary(answer);
    }
    if(baseOutput == 'o'){
        if(answer < 0){
            cout << oct << '-' << -answer << endl;
        }
        else{
            cout << oct << answer << endl;
        }

    }
}



int furthestFortyFive(vector<int> myArray){
    int furthest = myArray[0];

    //loop through the array and see if any values have an absolute value equal or less than
    for(int i = 0 ; i < (int)myArray.size(); i++){
        if(abs(myArray[i]- 45) > (abs(furthest - 45))){
            furthest = myArray[i];
        }
        //if the two numbers are equally far from 45 return the smallest one
        else if((abs(myArray[i] - 45) == (abs(furthest - 45)))){
                 if(myArray[i] < furthest){
                    furthest = myArray[i];
                 }
            }
        }
    return furthest;
}


void decToBinary(int n) {
    // array to store binary number
    int binaryNum[32];
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        cout << binaryNum[j] << endl;
}

int binaryToDecimal(int n){
    int num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }
    return dec_value;
}


bool checkInput(string fullArguments,char *argv[], int argc){
    bool inputChecked =  true;
    char apostrophe = (char)39;
    int mathCount = 0;
    int lengthOfArgs = fullArguments.length();
    for(int i = 5 ; i < lengthOfArgs; i++){
        if((fullArguments[i] != '@') && (fullArguments[i] != '+') && (fullArguments[i] != '-') && (fullArguments[i] != '/') &&
           (fullArguments[i] != '*') && (fullArguments[i] != apostrophe) && (fullArguments[i] != 'd') && (fullArguments[i] != 'b') &&
           (fullArguments[i] != 'o') && !isdigit(fullArguments[i]) && (fullArguments[i] != 'a') && (fullArguments[i] != 'b') &&
           (fullArguments[i] != 'c') && (fullArguments[i] != 'd') && (fullArguments[i] != 'e') && (fullArguments[i] != 'f') &&
           (fullArguments[i] != 'A') && (fullArguments[i] != 'B') && (fullArguments[i] != 'C') && (fullArguments[i] != 'D') &&
           (fullArguments[i] != 'E') && (fullArguments[i] != 'F') && (fullArguments[i] != ' ') && (fullArguments[i] != 'h')
           && (fullArguments[i] != 'x')){
            inputChecked = false;
                       }
                       if(((fullArguments[i] == '-') && (fullArguments[i+1] != 'd') && (fullArguments[i+1] != 'o')
                           && (fullArguments[i+1] != 'h') && (!isdigit(fullArguments[i+1]))) || (fullArguments[i] == '+') || (fullArguments[i] == '/')
                          || (fullArguments[i] == '@') || (fullArguments[i] == '*')){
                            mathCount++;
                       }
    }

    if(mathCount > 1){

        cerr << "\nToo many math operation in program " << programName << "\nYou typed " << fullArguments << endl;
        exit(1);
    }

if(inputChecked == false) {
        cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
        exit(1);
}

//check for hex character
for(int i = 0 ; i < argc; i++){
        string argument = argv[i];
        if(((argument[0] != '0') && (argument[1] != 'x') && ((argument[0] == 'a') || (argument[0] == 'b') ||
            (argument[0] == 'c') || (argument[0] == 'd') || (argument[0] == 'e') || (argument[0] == 'f')) && (isalpha(argument[0])))){
                cerr << "\nError in program: " << programName << " illegal syntax. \nUse: <output base> <math operation> <operand1>, <operand n>. You typed: " << fullArguments << "\n" << endl;
                exit(1);
            }
}

return inputChecked;
}


bool locationChecker(string fullArguments, char mathOperator, char baseOutput){
bool checked = false;
int positionOfMathOperator = 0;
int positionOfBaseOutput = 0;
int positionOfFirstNumber = 0;

int fullLength = fullArguments.length();

if(baseOutput == 'd'){
    positionOfBaseOutput = 1;
}

//get the positions of all the operands
for(int i = 5; i < fullLength; i++){
    //get position of base output
    if(((fullArguments[i] == '-') && (fullArguments[i+1] == 'd')) || ((fullArguments[i] == '-') && (fullArguments[i+1] == 'h')) ||
       ((fullArguments[i] == '-') && (fullArguments[i+1] == 'o'))){
           positionOfBaseOutput = i;
       }
    //get position of the math operator
    if((fullArguments[i] == mathOperator) && (fullArguments[i+1] != (positionOfBaseOutput + 1))){
        positionOfMathOperator = i;
    }


        //get position of the first number
    if(isdigit(fullArguments[i])){
        positionOfFirstNumber = i;
    }

    //check to make sure they are in the right order
    if((positionOfBaseOutput < positionOfMathOperator) && (positionOfMathOperator < positionOfFirstNumber)){
        checked = true;
    }
    else{
        checked = false;
    }
}
return checked;
}



bool whiteSpaceChecker(string fullArguments){
bool hasWhiteSpace = false ;
int fullLength = fullArguments.length();

for(int i = 0 ; i < fullLength; i++){
    if((fullArguments[i] == ' ') && (fullArguments[i+1] == ' ')){
            hasWhiteSpace = true;
    }
}
return hasWhiteSpace;

}

bool isOutputBase(string argument){
bool isBase = true;

if((argument != "-d") && (argument != "-h") && (argument != "-o")){
        isBase = false;
    }
    return isBase;
}


bool divZero(vector<int> myArray, char mathOperator, string fullArguments){
    bool isDivZero = false;
    int arraySize = (int)myArray.size();

        //check if 0 is in the array and not the first element, if it is, div by 0 error
        bool hasOtherZero = false;
        for(int i = 2 ; i < arraySize; i++){
            if(myArray[i] == 0){
                hasOtherZero = true;
            }
        }
    //check if operator is division
    if(mathOperator == '/'){
    //if the first number is 0 and there are no other zeros, print 0
    if(myArray[0] == 0){
            if(hasOtherZero == true){
                cerr << "Error in program " << programName << " division by 0. You typed " << fullArguments << endl;
                exit(1);
            }
            else{
                cout << 0 << endl;
                exit(0);
            }
    }


    //check if 0 is first element, and if the size is greater than 1 if it is, cout << 0 and exit
    if((myArray[0] == 0) && (arraySize > 1)){
        if(hasOtherZero == false){
        cout << 0 << endl;
        exit(0);
        }
    }
    //if the operation is division, and any other operator is 0
    if(hasOtherZero == true){
        cerr << "Error in program " << programName << " division by 0. You typed " << fullArguments << endl;
        exit(1);
        }
    }
    //if the operator is not division the answer is not an error
    else{
        return isDivZero = false;
        }
        return isDivZero;
}
