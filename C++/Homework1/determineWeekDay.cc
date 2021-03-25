#include <iostream>

using namespace std;


string determineWeekDay(int year, int month, int day);

string stringMonth(int month);

int determineMonth(bool leapYear, int day);

int main(){



string weekday ;
int day = 27;
bool leapYear = true;
int year = 2020;
int month = determineMonth(leapYear, day);
string monthName = stringMonth(month);


weekday = determineWeekDay(year, month, day);

cout << "It is " << weekday << " " << monthName << " " << day << " " << year;

return 0;
}

string determineWeekDay(int year, int month, int day){
string weekday = "unknown";
  static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  year -= month < 3;
  day = (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
  switch(day){
  case 1:
    weekday = "Sunday";
    break;
  case 2:
    weekday = "Monday";
    break;
  case 3:
    weekday = "Tuesday";
    break;
  case 4:
    weekday = "Wednesday";
    break;
  case 5:
    weekday = "Thursday";
    break;
  case 6:
    weekday = "Friday";
    break;
  case 7:
    weekday = "Saturday";
    break;
  }
  return weekday;
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
    monthName = "January";
    break;
case 2:
    monthName = "February";
    break;
case 3:
    monthName = "March";
    break;
case 4:
    monthName = "April";
    break;
case 5:
    monthName = "May";
    break;
case 6:
    monthName = "June";
    break;
case 7:
    monthName = "July";
    break;
case 8:
    monthName = "August";
    break;
case 9:
    monthName = "September";
    break;
case 10:
    monthName = "October";
    break;
case 11:
    monthName = "November";
    break;
case 12:
    monthName = "December";
    break;
    }
    return monthName;
}


