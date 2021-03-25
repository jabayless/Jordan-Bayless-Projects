#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#define strcasecmp _stricmp
#include <algorithm>
#include <cstring>

//this class represents a single event (a date)

class Event{
    private:
        int yearDay = 0;
        int year = 0;
        int month = 0;
        int monthDay = 0;
        int weekDay = 0;
        std::string weekDayS = "";

        //functions for constructing a date
        //prototype functions
        bool isAllValidCharacters(std::string myInput);
        bool isLeapYear(int year);
        bool isValidYear(int year);
        bool checkValidDay(int day, bool leapYear);
        int determineWeekDay(int yearInt, int monthInt, int dayInt);
        int determineMonth(bool leapYear, int day);
        std::string stringMonth(int month);
        int dayOfMonth(int month, int day, bool leapYear);

        //new functions
        std::vector<int> runStandardDate(char *argv[], std::string date);
        int case_insensitive_match(std::string s1, std::string s2);
        std::vector<int> isYesterday(std::string date);
        std::vector<int> isTomorrow(std::string date);
        std::vector<int> isToday(std::string date);
        std::vector<std::string> getFullFile(std::string fileName);
        std::vector<std::string> canFileOpen(int argc, char *argv[], int optind);
        void printTime(char outputType, bool stringReplace, std::string date, int argc,
		char *argv[], std::string toReplace);
        bool checkAllDigits(std::string input);
        std::vector<int> isValidDashDate(std::string date);
        int monthDayToYearDay(int month, int monthDay, bool isLeap);
        bool checkValidMonthDay(int month, int monthDay, bool isLeap);
        bool checkValidDashDigits(std::string date);
        void printVerbose(std::string inputType);
        bool checkValidDashDay(int month, bool isLeap, int monthDay);
        void printVector(std::vector<int> const &l);
        std::string replaceDate(std::vector<int> parseDate, std::string toReplace);
        std::string replaceDate(std::vector<int> parseDate,std:: string toReplace);
        std::string userTyped(int argc, char *argv[]);

    public:
        //single c++ string argument constructor
        Event(std::string date);
            //parse out string into date components
        //single c string argument constructor
        Event(char * date);
        //parse out string into date components

        //copy constructor
        Event(const Event &);

        //assignment operator
        //operator=
        Event & operator=(const Event &);

        //destructor
        ~Event();

        //general setter
        void set(int year, int month, int day);
        //setters
        void setYear(int year);
        void setMonth(int month);
        void setMonthDay(int day);
        void setYearDay(int yearDay);
        void setWeekDayS(std::string weekDay);
        void setWeekDay(int weekDay);


        //accessors for year month and day
        //get year
        int year() const;
        //get month
        int month() const;
        //get day
        int day() const;
        //get year day
        int yearDay() const;
        //get week day
        int weekDay() const;
        //get string weekday
        std::string weekDayS() const;

        static int getCount();

};

//non methods
//istream
std::istream & operator>>(std::istream& is, Event::Event& e){
    std::string date;
    is >> date;
    Event newEvent(date);
    e = newEvent;
    return is;
}
//ostream
std::ostream& operator<<(std::ostream& os, const Event::Event& r){
    os << r.year() << "-" << r.day() << "-" << r.month();
    return os;
}
#endif