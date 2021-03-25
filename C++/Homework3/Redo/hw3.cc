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

//new functions
vector<string> runStandardDate(char *argv[], string date);
int case_insensitive_match(string s1, string s2);
vector<string> isYesterday(char fullString[3000]);
vector<string> isTomorrow(char fullString[3000]);
vector<string> isToday(char fullString[3000]);
vector<string> getFullFile(string fileName);
vector<string> canFileOpen(int argc, char *argv[]);
void printTime(char outputType, bool stringReplace, string date,
		int argc, char *argv[], string toReplace);
bool checkAllDigits(string input);
vector<string> isValidDashDate(string date);
int monthDayToYearDay(int month, int monthDay, bool isLeap);
bool checkValidMonthDay(int month, int monthDay);
bool checkValidDashDigits(string date);
void printVerbose(string inputType);

//main begins right here
string programName;
int main(int argc, char *argv[]) {
    cout << "in main" << endl;

	//get the command line arguments
	int opt;
	bool verbose = false;
	char outputType = 'n';
	char inputType = 'u';
	string stringToReplace;
	bool replaceString = false;
	while ((opt = getopt(argc, argv, "vif:")) != -1) {
		switch (opt) {
		case 'v':
		    verbose = true;
			break;
		case 'f':
			//use string replace
			replaceString = true;
			stringToReplace = optarg;
			break;
		case 'i':
            outputType = 'i';
			break;
		default: /* '?' */
			cerr << "Incorrect format specifier was specified. In program " << programName << " you typed " << argv[optind] << endl;
			exit (EXIT_FAILURE);
		}
	}
    cout << " after getopt, verbose is " << verbose << " replace string is " << replaceString << " output type is " << outputType << '\n';
    cout << "string to replace is " << stringToReplace << '\n';
	//check the commandLine for files to open
	vector < string > files = canFileOpen(argc, argv);
	char fullString[3000];
	if ((files.size() == 0) && (opt >= argc))  {
        cout << "Input was determined to be cin\n";
	    string verboseType = "cin";
        if(verbose == true){
        printVerbose(verboseType);
        }

		//use cin instead
		string line;
		int maxLength = 3000;
		int opCount = 0;
		//if not files, read from cin
		while (getline(cin, line)) {
			strcpy(fullString, line.c_str());
			if (opCount == 0) {
                printTime(outputType, replaceString, line, argc, argv, stringToReplace);
			} else {
			    string theDate;
				cin.getline(fullString, maxLength, '\n');
                printTime(outputType, replaceString, fullString, argc, argv, stringToReplace);

				//call print method
			}
		} // end while getline
	}
	//read from files and send content to print method
	else {
		vector < string > fileContents;
		char type = '0';
		for (int i = 0; i < files.size(); i++) {
            if(verbose == true){
            printVerbose(files[i]);

            }
            fileContents = getFullFile(files[i]);
            for(int j = 0 ; j < fileContents.size(); j++){
            printTime(outputType, replaceString, fileContents[j], argc, argv, stringToReplace);
            }

		}
			//parse file contents into sub strings to send to sub strings to determine output type


			//send fileContents to the print function

		}
		return 0;
}

bool isAllValidCharacters(string myInput) {
	bool validCharacters = true;
	int numberOfDots = 0;
	for (int i = 0; i < ((int) myInput.length()); i++) {
		if (isdigit(myInput[i])) {
		} else if (myInput[i] == '.') {
			numberOfDots++;
		} else if (myInput[i] == '\n') {
			cerr << " newline detected at " << myInput[i] << "in "
					<< programName << "\n";
			exit(1);
		} else {

			cerr << "character " << myInput[i] << " in line containing "
					<< myInput << "\n";
			cerr << "is an invalid character in standard input in program "
					<< programName << "\n";
			exit(1);
			return validCharacters = false;
		}

	}
	if (numberOfDots != 1) {
		cerr
				<< "data is not of correct format, use <number>.<number> with no leading white space or newline in program: \n"
				<< programName << "\n";
		exit(1);
	}
	return validCharacters;
}

bool isLeapYear(int year) {
	bool leapYear = false;
	if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))) {
		leapYear = true;
	} else {
	}
	return leapYear;
}

bool isValidYear(int year) {
	bool validYear = false;
	if ((year < 1) || year > 9999) {
		cerr << "The year is out of range 1 - 9999 in program " << programName
				<< "\n";
		exit(0);
	} else {
		validYear = true;
	}
	return validYear;
}

bool checkValidDay(int day, bool leapYear) {
	bool validDay = true;
	if (day < 1) {
		validDay = false;
		cerr << "the day " << day << " is out of range in program "
				<< programName << "\n";
		exit(0);
	} else if ((leapYear == false) && (day > 365)) {
		cerr << "the day " << day << " is out of range in program "
				<< programName << "\n";
		exit(0);
		validDay = false;
	} else if ((leapYear == true) && (day > 366)) {
		cerr << "the day " << day << " is out of range in program "
				<< programName << "\n";
		exit(0);
		validDay = false;
	}
	return validDay;
}

int determineMonth(bool leapYear, int day) {
	int leapYearMonthsHigh[12] = { 31, 60, 91, 121, 152, 182, 213, 244, 274,
			305, 335, 366 };
	int leapYearMonthsLow[12] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274,
			305, 335 };
	int commonYearMonthsHigh[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273,
			304, 334, 365 };
	int commonYearMonthsLow[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273,
			304, 334 };

	int month;
	if (leapYear == true) {
		if ((day > leapYearMonthsLow[0]) && (day <= leapYearMonthsHigh[0])) {
			month = 1;
		} else if ((day > leapYearMonthsLow[1])
				&& (day <= leapYearMonthsHigh[1])) {
			month = 2;
		} else if ((day > leapYearMonthsLow[2])
				&& (day <= leapYearMonthsHigh[2])) {
			month = 3;
		} else if ((day > leapYearMonthsLow[3])
				&& (day <= leapYearMonthsHigh[3])) {
			month = 4;
		} else if ((day > leapYearMonthsLow[4])
				&& (day <= leapYearMonthsHigh[4])) {
			month = 5;
		} else if ((day > leapYearMonthsLow[5])
				&& (day <= leapYearMonthsHigh[5])) {
			month = 6;
		} else if ((day > leapYearMonthsLow[6])
				&& (day <= leapYearMonthsHigh[6])) {
			month = 7;
		} else if ((day > leapYearMonthsLow[7])
				&& (day <= leapYearMonthsHigh[7])) {
			month = 8;
		} else if ((day > leapYearMonthsLow[8])
				&& (day <= leapYearMonthsHigh[8])) {
			month = 9;
		} else if ((day > leapYearMonthsLow[9])
				&& (day <= leapYearMonthsHigh[9])) {
			month = 10;
		} else if ((day > leapYearMonthsLow[10])
				&& (day <= leapYearMonthsHigh[10])) {
			month = 11;
		} else if ((day > leapYearMonthsLow[11])
				&& (day <= leapYearMonthsHigh[11])) {
			month = 12;
		}
	}

	if (leapYear == false) {
		if ((day > commonYearMonthsLow[0])
				&& (day <= commonYearMonthsHigh[0])) {
			month = 1;
		} else if ((day > commonYearMonthsLow[1])
				&& (day <= commonYearMonthsHigh[1])) {
			month = 2;
		} else if ((day > commonYearMonthsLow[2])
				&& (day <= commonYearMonthsHigh[2])) {
			month = 3;
		} else if ((day > commonYearMonthsLow[3])
				&& (day <= commonYearMonthsHigh[3])) {
			month = 4;
		} else if ((day > commonYearMonthsLow[4])
				&& (day <= commonYearMonthsHigh[4])) {
			month = 5;
		} else if ((day > commonYearMonthsLow[5])
				&& (day <= commonYearMonthsHigh[5])) {
			month = 6;
		} else if ((day > commonYearMonthsLow[6])
				&& (day <= commonYearMonthsHigh[6])) {
			month = 7;
		} else if ((day > commonYearMonthsLow[7])
				&& (day <= commonYearMonthsHigh[7])) {
			month = 8;
		} else if ((day > commonYearMonthsLow[8])
				&& (day <= commonYearMonthsHigh[8])) {
			month = 9;
		} else if ((day > commonYearMonthsLow[9])
				&& (day <= commonYearMonthsHigh[9])) {
			month = 10;
		} else if ((day > commonYearMonthsLow[10])
				&& (day <= commonYearMonthsHigh[10])) {
			month = 11;
		} else if ((day > commonYearMonthsLow[11])
				&& (day <= commonYearMonthsHigh[11])) {
			month = 12;
		}
	}
	return month;
}

string stringMonth(int month) {
	string monthName;
	switch (month) {
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

string determineWeekDay(int year, int month, int day) {
	string weekday1 = "unknown";
	time_t rawtime;
	struct tm *timeinfo;
	const char *weekday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = year - 1900;
	timeinfo->tm_mon = month - 1;
	timeinfo->tm_mday = day;

	mktime(timeinfo);
	weekday1 = weekday[timeinfo->tm_wday];
	return weekday1;
}

int dayOfMonth(int month, int day, bool leapYear) {
	int dayInMonth = 0;
	switch (month) {
	case 1:
		dayInMonth = (day - 0);
		break;
	case 2:
		dayInMonth = (day - 31);
		break;
	case 3:
		if (leapYear == true) {
			dayInMonth = (day - 60);
		} else if (leapYear == false) {
			dayInMonth = (day - 59);
		}
		break;
	case 4:
		if (leapYear == true) {
			dayInMonth = (day - 91);
		} else if (leapYear == false) {
			dayInMonth = (day - 90);
		}
		break;
	case 5:
		if (leapYear == true) {
			dayInMonth = (day - 121);
		} else if (leapYear == false) {
			dayInMonth = (day - 120);
		}
		break;
	case 6:
		if (leapYear == true) {
			dayInMonth = (day - 152);
		} else if (leapYear == false) {
			dayInMonth = (day - 151);
		}
		break;
	case 7:
		if (leapYear == true) {
			dayInMonth = (day - 182);
		} else if (leapYear == false) {
			dayInMonth = (day - 181);
		}
		break;
	case 8:
		if (leapYear == true) {
			dayInMonth = (day - 213);
		} else if (leapYear == false) {
			dayInMonth = (day - 212);
		}
		break;
	case 9:
		if (leapYear == true) {
			dayInMonth = (day - 244);
		} else if (leapYear == false) {
			dayInMonth = (day - 243);
		}
		break;
	case 10:
		if (leapYear == true) {
			dayInMonth = (day - 274);
		} else if (leapYear == false) {
			dayInMonth = (day - 273);
		}
		break;
	case 11:
		if (leapYear == true) {
			dayInMonth = (day - 305);
		} else if (leapYear == false) {
			dayInMonth = (day - 304);
		}
		break;
	case 12:
		if (leapYear == true) {
			dayInMonth = (day - 335);
		} else if (leapYear == false) {
			dayInMonth = (day - 334);
		}
		break;
	}
	return dayInMonth;
}

//should take in a string
vector<string> runStandardDate(char *argv[], string date) {

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
	string previous = "";
	strcpy(fullString, date.c_str());

	//check the input for errors
	//separate incoming string into year and day strings
	//check the string for illegal characters
	ostringstream oss;
	string fullOutput = "";

	//reset values so it doesn't print twice
	day = "";
	monthDay = 0;
	monthName = "";
	monthInt = 0;
	lineNumber++;

	// cout << fullString;
	if (fullString[0] == '\n') {
		cerr << "line contains a new line character and no data in program "
				<< programName << "\n";
		exit(0);
	}
	if (isAllValidCharacters(fullString)) {
		fullString1 = fullString;
	}

	else {
		cerr << fullString1
				<< " does not contain all valid characters in program "
				<< programName << " system exiting" << endl;
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
	day = fullString1.substr(pos + 1);
	stringstream dayString(day);
	dayString >> dayInt;

	//check if all parts of input are valid before printing
	//check if the day is valid
	if ((checkValidDay(dayInt, leapYear) == true) && (validYear == true)) {
		monthInt = determineMonth(leapYear, dayInt);
		monthName = stringMonth(monthInt);

		//convert to proper format
		monthInt = determineMonth(leapYear, dayInt);
		string monthName = stringMonth(monthInt);
		monthDay = dayOfMonth(monthInt, dayInt, leapYear);
		day = determineWeekDay(yearInt, monthInt, monthDay);

		//print date
		oss << day << " " << setw(2) << setfill('0') << monthDay << " "
				<< monthName << " " << setw(4) << setfill('0') << yearInt;
		fullOutput = oss.str();

	}
	if (fullOutput != previous) {
		//cout << fullOutput << "\n";
		fullOutput = previous;
	}
	else {
	}
	vector < string > fullDate;
	fullDate.push_back(to_string(dayInt));
	fullDate.push_back(to_string(monthInt));
	fullDate.push_back(to_string(monthDay));
	fullDate.push_back(to_string(yearInt));
	fullDate.push_back(day);
	return fullDate;
}

vector <string> isToday(char fullString[3000]){
    vector<string> todays;
	int maxLength = 3000;
	string string1 = "today";
	string str;

	string fullString1 = fullString;
	if (case_insensitive_match(string1, fullString1)) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		//add relevant parts to vector
        todays.push_back(to_string(tm.tm_yday));
        todays.push_back(to_string(tm.tm_mon));
        todays.push_back(to_string(tm.tm_mday));
        todays.push_back(to_string(tm.tm_year));
        todays.push_back(to_string(tm.tm_wday));

		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y-%m-%d");
		auto str = oss.str();
	}
	return todays;
}

vector<string> isYesterday(char fullString[3000]){
    vector<string> yesterday;
	int maxLength = 3000;
	string string1 = "yesterday";
	string str = "0";
	string fullString1 = fullString;
	if (case_insensitive_match(string1, fullString1)) {
		time_t now = time(NULL);
		now = now - (24 * 60 * 60);
		auto tm = *std::localtime(&now);

		//add relevant parts to vector
        yesterday.push_back(to_string(tm.tm_yday));
        yesterday.push_back(to_string(tm.tm_mon));
        yesterday.push_back(to_string(tm.tm_mday));
        yesterday.push_back(to_string(tm.tm_year));
        yesterday.push_back(to_string(tm.tm_wday));
	}
	return yesterday;
}

vector<string> isTomorrow(char fullString[3000]){
    vector<string> tomorrow;
	int maxLength = 3000;
	string string1 = "tomorrow";
	string str = "0";
	string fullString1 = fullString;
	if (case_insensitive_match(string1, fullString1)) {
		time_t now = time(NULL);
		now = now + (24 * 60 * 60);
		auto tm = *std::localtime(&now);

		//add relevant parts to vector
        tomorrow.push_back(to_string(tm.tm_yday));
        tomorrow.push_back(to_string(tm.tm_mon));
        tomorrow.push_back(to_string(tm.tm_mday));
        tomorrow.push_back(to_string(tm.tm_year));
        tomorrow.push_back(to_string(tm.tm_wday));
	}
	return tomorrow;
}

int case_insensitive_match(string s1, string s2) {
	//convert s1 and s2 into lower case strings
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0)
		return 1; //The strings are same
	return 0; //not matched
}

string stringReplace(string sentence) {
	string changedOutput;
	time_t t;
	struct tm *tmp;
	char buffer[70];
	char line[70];

	time(&t);

	// using strftime to display time
	//date will be stored in MY_TIME
	strcpy(line, sentence.c_str());
	strftime(buffer, 70, line, tmp);

	changedOutput = buffer;

	return changedOutput;
}

vector<string> canFileOpen(int argc, char *argv[]) {
	vector < string > files;

//process each file
	for (int i = 1; i < argc; i++) {
		//create a file object
		ifstream inFile;
		inFile.open(argv[i]);
		if (!inFile) {
			cerr << "Unable to open file " << argv[i] << " in program "
					<< programName << endl;
		} else {
		    cout << "opening file \n" << argv[i];
			files.push_back(argv[i]);
		}
		//use getline to get the file contents into a single string

		inFile.close();
	}
	return files;
}

//this code is called when hasFiles is true (-v is specified)
//function gets the file names, opens the and gets their contents
vector<string> getFullFile(string fileName) {
	vector < string > fileContent;
	string fileContents;

	//process each file
	//create a file object
	ifstream inFile;

	inFile.open(fileName);
	if (!inFile) {
		cerr << "Unable to open file in getFullFile " << fileName
				<< " in program " << programName << endl;
		exit(1); //
	} else {
		//use getline to get the file contents into a single string
		while (getline(inFile, fileContents)) {
			fileContent.push_back(fileContents);
		}
	}

	inFile.close();
	return fileContent;
}

void printTime(char outputType, bool stringReplace, string date,
		int argc, char *argv[], string toReplace) {
//get values of date
	string weekDay = "";
	int monthDay = 0;
	int year = 0;
	string month = "";
	char myDate[3000];
	strcpy(myDate, date.c_str());
	bool isValidDate = false;
	vector<string> fullDate;
	bool isOkay = false;
	//loop through the date to determine the type
	for(int i = 0 ; i < date.size(); i++){
        if(date[i] == '-'){
            cout << "determined to be dash day\n";
            fullDate = isValidDashDate(date);
            isOkay = true;

        }
        else if(date[i] == '.'){
            cout << "determined to be dot day\n";
            fullDate = runStandardDate(argv, date);
            isOkay = true;
        }
	}
	cout << "Is okay is " << isOkay << endl;
            if(isOkay == false){
             fullDate = isToday(myDate);
             if(fullDate.size() == 0){
                //cout << "determined to not be today day" << endl;
                fullDate = isTomorrow(myDate);
                if(fullDate.size() == 0){
                    //cout << "determined to not be tomorrow\n";
                    fullDate = isYesterday(myDate);
                    //cout << "ran isYesterday\n";
                    if(fullDate.size() == 0){
                        cerr << "Input " << myDate << " is not of valid format in program " << programName << " system exiting" << endl;
                        exit(1);
                    }
                }
             }
        }

  //  cout << "output type is " << outputType << endl;
	//replace the string at argv with quotes
	//replace string is the string to use to replace in the time struct

	//put the valid day into a time struct and send it to strftime
	time_t t;
	struct tm *tmp;
	char buffer[70];
	char line[70];

	time(&t);

	//set the time struct
	tmp->tm_mday = stoi(fullDate[2]);
	tmp->tm_wday = stoi(fullDate[4]);
	tmp->tm_yday = stoi(fullDate[0]);
	tmp->tm_year = stoi(fullDate[3]);
	tmp->tm_mon = stoi(fullDate[1]);

	//if the format is dash date or . date or isYesterday etc.
	if((isOkay == true) || (fullDate.size() != 0)){
            if((stringReplace == true) && (outputType == 'i')){
                cerr << "Both -i and -f format specifiers were provided which are mutually exclusive\n";
                cerr << "in program " << programName << endl;
                exit(1);
            }
        //now that you're in sure the date is set
        //check what kind of output you want: normal, ISO standard or string replace
        if(outputType == 'i'){
            line[0] = '%';
            line[1] = 'Y';
            line[2] = '-';
            line[3] = '%';
            line[4] = 'm';
            line[5] = '-';
            line[6] = '%';
            line[7] = 'd';

        }
        //do string replace
        else if(stringReplace == true){
        strcpy(line, toReplace.c_str());
        }
        //just print normal output
        else{
            line[0] = '%';
            line[1] = 'a';
            line[2] = ' ';
            line[3] = '%';
            line[4] = 'd';
            line[5] = ' ';
            line[6] = '%';
            line[7] = 'h';
            line[8] = ' ';
            line[9] = '%';
            line[10] = 'Y';
        }
	}

	//string replacement code
	if(stringReplace == true){
        if(outputType == 'i'){

            strftime(buffer, 70, line, tmp);
        }
	}
                strftime(buffer, 70, line, tmp);
	            cout << buffer << "\n" << endl;
}

vector<string> isValidDashDate(string date) {
	vector < string > validDashDay;
	bool validDay = false;
	string years = date.substr(0, 4);
	string months = date.substr(5, 2);
	string monthDays = date.substr(8, 2);
	int year = stoi(years);
	int month = stoi(months);
	int monthDay = stoi(monthDays);
	bool isLeap = isLeapYear(year);

	//check valid dash characters
	bool allValidChars = checkValidDashDigits(date);

	//count number of dashes, should be equal to two
	int dashCount = 0;
	for (int i = 0; i < date.length(); i++) {
		if (date[i] == '-') {
			dashCount++;
		}
	}

	if ((!checkAllDigits(years)) || (!checkAllDigits(months))
			|| (!checkAllDigits(monthDays))) {
		cerr << "date is not of the correct format. for input " << date
				<< " system exiting" << endl;
		exit(1);
	}
	//if the format is invalid
	if ((dashCount != 2) && (!allValidChars) && (date.length() != 10)) {
		cerr << "date is not of the correct format. for input " << date
				<< " system exiting" << endl;
		exit(1);
	}

	else {
		//convert monthDay to day of year
		int dayOfYear = monthDayToYearDay(month, monthDay, isLeap);
		if ((isValidYear(year)) && (checkValidDay(dayOfYear, isLeap))
				&& (month <= 12) && (month >= 1)) {
			//get the week day and put it in a vector and return that shit
			string weekDay = determineWeekDay(year, month, dayOfYear);
			validDashDay.push_back(to_string(dayOfYear));
			validDashDay.push_back(to_string(month));
			validDashDay.push_back(to_string(monthDay));
			validDashDay.push_back(to_string(year));
			validDashDay.push_back(weekDay);
		}
	}
	return validDashDay;
}

bool checkAllDigits(string input) {
	bool isallDig = true;
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return isallDig = false;
		}
	}
	return isallDig;
}

int monthDayToYearDay(int month, int monthDay, bool isLeap) {
	int yearDay = 0;
	int myLeapMonthArray[12] =
			{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int myNormMonthArray[12] =
			{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for (int i = 0; i < month - 1; i++) {
		if (isLeap) {
			yearDay = yearDay + myLeapMonthArray[i];
		}
		if (!isLeap) {
			yearDay = yearDay + myNormMonthArray[i];
		}
	}
	return yearDay;
}

bool checkValidMonthDay(int month, int monthDay, bool isLeap) {
	bool isValidMonth = false;
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if ((monthDay <= 31) && (monthDay >= 1)) {
			isValidMonth = true;
		}
		break;

	case 2:
		if ((monthDay <= 28) && (monthDay >= 1) && (!isLeap)) {
			isValidMonth = true;
		}
		if ((monthDay <= 29) && (monthDay >= 1) && (isLeap)) {
			isValidMonth = true;
		}
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		if ((monthDay <= 30) && (monthDay >= 1)) {
			isValidMonth = true;
		}
		break;
	}
	return isValidMonth;
}

bool checkValidDashDigits(string date) {
	bool validChars = true;
	for (int i = 0; i < date.length(); i++) {
		if ((!isdigit(date[i])) && (date[i] != '-')) {
			return validChars = false;
		}
	}
	return validChars;
}


void printVerbose(string inputType) {
    if(inputType == "cin"){
        cout << "*** Processing standard input\n";
    }
    if(inputType != "cin"){
        cout << "*** Processing " << inputType << "\n";
    }
}
