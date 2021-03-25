#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <time.h>

using namespace std;

//prototype functions
bool isAllValidCharacters(string myInput);
bool isLeapYear(int year);
bool isValidYear(int year);
bool checkValidDay(int day, bool leapYear);
string determineWeekDay(int yearInt, int monthInt, int dayInt);
int determineMonth(bool leapYear, int day);
string stringMonth(int month);
int dayOfMonth(int month, int day, bool leapYear);

string programName;
int main(int argc, char *argv[]){

    //get rid of unused argc warning
    if(argc == 1){

    }
    else{

    }

    int lineNumber = 0;
    programName = argv[0];
    int maxLength = 2001;
    char fullString[2001];
    string monthName;
    int monthInt;
    string fullString1;
    string year;
    string day;
    int yearInt = 0;
    int dayInt = 0;
    int monthDay = 0;
    string previous = "" ;

    //check the input for errors
    //separate incoming string into year and day strings
    //check the string for illegal characters
    while(cin){
    ostringstream oss;
    string fullOutput = "";

    //reset values so it doesn't print twice
    day = "";
    monthDay = 0;
    monthName = "";
    monthInt = 0;
    lineNumber++;

    //get input from standard input
    cin.getline(fullString, maxLength, '\n');
   // cout << fullString;
    if(fullString[0] == '\n'){
        cerr << "line contains a new line character and no data in program " << programName << "\n";
        exit(0);
    }
    if(isAllValidCharacters(fullString)){
        fullString1 = fullString;
        }

    else{
        exit(0);
    }
    //run all validity tests before adding to vector
    //separate each line of cin into two strings
    int pos = fullString1.find_first_of('.');

    //first part of string is the year
    year = fullString1.substr(0, pos);
    stringstream yearString(year);
    yearString >> yearInt;

    //check if the year is valid
    bool validYear = isValidYear(yearInt);

    //check if the year is a leap year
    bool leapYear = isLeapYear(yearInt);

    //second part of string is the day
    day = fullString1.substr(pos+1);
    stringstream dayString(day);
    dayString >> dayInt;

    //check if all parts of input are valid before printing
    //check if the day is valid
    if((checkValidDay(dayInt, leapYear) ==  true) && (validYear == true)){
        monthInt = determineMonth(leapYear, dayInt);
        monthName = stringMonth(monthInt);

        //convert to proper format
        monthInt = determineMonth(leapYear, dayInt);
        string monthName = stringMonth(monthInt);
        monthDay = dayOfMonth(monthInt, dayInt, leapYear);
        day = determineWeekDay(yearInt, monthInt, monthDay);

    //print date
    oss << day << " " << setw(2) << setfill('0') << monthDay << " " << monthName << " " << setw(4) << setfill('0') << yearInt ;
    fullOutput = oss.str();

    }
    if(fullOutput != previous){
    cout << fullOutput << "\n";
    fullOutput = previous;
    }
    else{
    }

    }//end while loop
return 0;
}


bool isAllValidCharacters(string myInput){
    bool validCharacters = true;
    int numberOfDots = 0;
for (int i=0; i< ((int)myInput.length()); i++){
        if(isdigit(myInput[i])){
        }
        else if(myInput[i] == '.') {
                numberOfDots++;
        }
        else if(myInput[i] == '\n'){
        cerr << " newline detected at " << myInput[i] << "in " << programName << "\n";
        exit(1);
        }
        else{

         cerr << "character " << myInput[i] << " in line containing " << myInput << "\n";
         cerr << "is an invalid character in standard input in program " << programName << "\n";
         exit(1);
         return validCharacters = false;
        }

    }
    if(numberOfDots != 1){
        cerr << "data is not of correct format, use <number>.<number> with no leading white space or newline in program: \n" << programName << "\n";
        exit(1);
    }
    return validCharacters;
}


bool isLeapYear(int year){
bool leapYear = false;
 if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))){
    leapYear = true;
 }
 else{
 }
    return leapYear;
}


bool isValidYear(int year){
bool validYear = false;
if ((year < 1) || year > 9999 ){
    cerr << "The year is out of range 1 - 9999 in program " << programName << "\n";
    exit(0);
}
else{
    validYear = true;
}
    return validYear;
}

bool checkValidDay(int day, bool leapYear){
bool validDay = true;
if(day < 1){
    validDay = false;
    cerr << "the day " << day << " is out of range in program " << programName << "\n";
    exit(0);
}
else if((leapYear == false) && (day > 365)){
    cerr << "the day " << day << " is out of range in program " << programName << "\n";
    exit(0);
    validDay = false;
}
else if((leapYear == true) && (day > 366)){
    cerr << "the day " << day << " is out of range in program " << programName << "\n";
    exit(0);
    validDay = false;
}
    return validDay;
}


int determineMonth(bool leapYear, int day){
    int leapYearMonthsHigh[12] = {31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
    int leapYearMonthsLow[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    int commonYearMonthsHigh[12] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int commonYearMonthsLow[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    int month;
    if(leapYear == true){
        if((day > leapYearMonthsLow[0]) && (day <= leapYearMonthsHigh[0])){
            month = 1;
        }
        else if((day > leapYearMonthsLow[1]) && (day <=leapYearMonthsHigh[1])){
            month = 2;
        }
        else if((day > leapYearMonthsLow[2]) && (day <=leapYearMonthsHigh[2])){
            month = 3;
        }
        else if((day > leapYearMonthsLow[3]) && (day <=leapYearMonthsHigh[3])){
            month = 4;
        }
        else if((day > leapYearMonthsLow[4]) && (day <=leapYearMonthsHigh[4])){
            month = 5;
        }
        else if((day > leapYearMonthsLow[5]) && (day <=leapYearMonthsHigh[5])){
            month = 6;
        }
        else if((day > leapYearMonthsLow[6]) && (day <= leapYearMonthsHigh[6])){
            month = 7;
        }
        else if((day > leapYearMonthsLow[7]) && (day <= leapYearMonthsHigh[7])){
            month = 8;
        }
        else if((day > leapYearMonthsLow[8]) && (day <= leapYearMonthsHigh[8])){
            month = 9;
        }
        else if((day > leapYearMonthsLow[9]) && (day <= leapYearMonthsHigh[9])){
            month = 10;
        }
        else if((day > leapYearMonthsLow[10]) && (day <= leapYearMonthsHigh[10])){
            month = 11;
        }
        else if((day > leapYearMonthsLow[11]) && (day <= leapYearMonthsHigh[11])){
            month = 12;
        }
    }

    if(leapYear == false){
        if((day > commonYearMonthsLow[0]) && (day <= commonYearMonthsHigh[0])){
            month = 1;
        }
        else if((day > commonYearMonthsLow[1]) && (day <=commonYearMonthsHigh[1])){
            month = 2;
        }
        else if((day > commonYearMonthsLow[2]) && (day <=commonYearMonthsHigh[2])){
            month = 3;
        }
        else if((day > commonYearMonthsLow[3]) && (day <=commonYearMonthsHigh[3])){
            month = 4;
        }
        else if((day > commonYearMonthsLow[4]) && (day <=commonYearMonthsHigh[4])){
            month = 5;
        }
        else if((day > commonYearMonthsLow[5]) && (day <=commonYearMonthsHigh[5])){
            month = 6;
        }
        else if((day > commonYearMonthsLow[6]) && (day <= commonYearMonthsHigh[6])){
            month = 7;
        }
        else if((day > commonYearMonthsLow[7]) && (day <= commonYearMonthsHigh[7])){
            month = 8;
        }
        else if((day > commonYearMonthsLow[8]) && (day <= commonYearMonthsHigh[8])){
            month = 9;
        }
        else if((day > commonYearMonthsLow[9]) && (day <= commonYearMonthsHigh[9])){
            month = 10;
        }
        else if((day > commonYearMonthsLow[10]) && (day <= commonYearMonthsHigh[10])){
            month = 11;
        }
        else if((day > commonYearMonthsLow[11]) && (day <= commonYearMonthsHigh[11])){
            month = 12;
        }
    }
    return month;
}


string stringMonth(int month){
    string monthName;
    switch (month){
case 1:
    monthName = "Jan";
    break;
case 2:
    monthName = "Feb";
    break;
case 3:
    monthName = "Mar";
    break;
case 4:
    monthName = "Apr";
    break;
case 5:
    monthName = "May";
    break;
case 6:
    monthName = "Jun";
    break;
case 7:
    monthName = "Jul";
    break;
case 8:
    monthName = "Aug";
    break;
case 9:
    monthName = "Sep";
    break;
case 10:
    monthName = "Oct";
    break;
case 11:
    monthName = "Nov";
    break;
case 12:
    monthName = "Dec";
    break;
    }
    return monthName;
}



string determineWeekDay(int year, int month, int day){
  string weekday1 = "unknown";
  time_t rawtime;
  struct tm * timeinfo;
  const char * weekday[] = { "Sun", "Mon",
                             "Tue", "Wed",
                             "Thu", "Fri", "Sat"};

time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  timeinfo->tm_year = year - 1900;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = day;

  mktime ( timeinfo );
  weekday1 = weekday[timeinfo->tm_wday];
    return weekday1;
}




int dayOfMonth(int month, int day, bool leapYear){
int dayInMonth = 0;
    switch(month){
case 1:
    dayInMonth = (day-0);
    break;
case 2:
    dayInMonth = (day - 31);
    break;
case 3:
    if(leapYear == true){
        dayInMonth = (day - 60);
    }
    else if(leapYear == false){
        dayInMonth = (day - 59);
    }
    break;
case 4:
    if(leapYear == true){
        dayInMonth = (day - 91);
    }
    else if(leapYear == false){
        dayInMonth = (day - 90);
    }
    break;
case 5:
if(leapYear == true){
        dayInMonth = (day - 121);
    }
    else if(leapYear == false){
        dayInMonth = (day - 120);
    }
    break;
case 6:
    if(leapYear == true){
        dayInMonth = (day - 152);
    }
    else if(leapYear == false){
        dayInMonth = (day - 151);
    }
    break;
case 7:
    if(leapYear == true){
        dayInMonth = (day - 182);
    }
    else if(leapYear == false){
        dayInMonth = (day - 181);
    }
    break;
case 8:
    if(leapYear == true){
        dayInMonth = (day - 213);
    }
    else if(leapYear == false){
        dayInMonth = (day - 212);
    }
    break;
case 9:
    if(leapYear == true){
        dayInMonth = (day - 244);
    }
    else if(leapYear == false){
        dayInMonth = (day - 243);
    }
    break;
case 10:
    if(leapYear == true){
        dayInMonth = (day - 274);
    }
    else if(leapYear == false){
        dayInMonth = (day - 273);
    }
    break;
case 11:
    if(leapYear == true){
        dayInMonth = (day - 305);
    }
    else if(leapYear == false){
        dayInMonth = (day - 304);
    }
    break;
case 12:
    if(leapYear == true){
        dayInMonth = (day - 335);
    }
    else if(leapYear == false){
        dayInMonth = (day - 334);
    }
    break;
    }
    return dayInMonth;
}
