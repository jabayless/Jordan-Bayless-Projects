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
int determineWeekDay(int yearInt, int monthInt, int dayInt);
int determineMonth(bool leapYear, int day);
string stringMonth(int month);
int dayOfMonth(int month, int day, bool leapYear);

//new functions
vector<int> runStandardDate(char *argv[], string date);
int case_insensitive_match(string s1, string s2);
vector<int> isYesterday(string date);
vector<int> isTomorrow(string date);
vector<int> isToday(string date);
vector<string> getFullFile(string fileName);
vector<string> canFileOpen(int argc, char *argv[]);
void printTime(char outputType, bool stringReplace, string date,
		int argc, char *argv[], string toReplace);
bool checkAllDigits(string input);
vector<int> isValidDashDate(string date);
int monthDayToYearDay(int month, int monthDay, bool isLeap);
bool checkValidMonthDay(int month, int monthDay);
bool checkValidDashDigits(string date);
void printVerbose(string inputType);

//main begins right here
string programName;
int main(int argc, char *argv[]) {
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
	//check the commandLine for files to open
	vector < string > files = canFileOpen(argc, argv);
	char fullString[3000];
        string verboseType = "cin";
        if(verbose == true){
        printVerbose(verboseType);
        }
        //use cin
        cout << "number of files read from is " << files.size() << '\n';
        if ((files.size() == 0))  {
        cout << "Input was now determined to be cin\n";
		//use cin instead
		int opCount = 0;
		string line;
		int maxLength = 3000;
		cout << "before while loop \n";
		//if not files, read from cin
		while (getline(cin, line)) {
            cout << "in getline while loop iteration is " << opCount << "\n";
			strcpy(fullString, line.c_str());
			cout << fullString << " was typed into standard input\n";
			if (opCount == 0) {
                printTime(outputType, replaceString, line, argc, argv, stringToReplace);
			} else {
			    string theDate;
				cin.getline(fullString, maxLength, '\n');
                printTime(outputType, replaceString, fullString, argc, argv, stringToReplace);

				//call print method
			}
		}
    } // end while getline
	//read from files and send content to print method
        if(files.size() > 0) {
        cout << "reading from files\n";
		vector < string > fileContents;
		char type = '0';
		for (int i = 0; i < files.size(); i++) {
            if(verbose == true){
            printVerbose(files[i]);

            }
            fileContents = getFullFile(files[i]);
            for(int j = 0 ; j < fileContents.size(); j++){
            cout << fileContents.at(j) << "\n";
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

int determineWeekDay(int year, int month, int day) {
	string weekday1 = "unknown";
	time_t myRawtime;
	struct tm *timeinfo1;
	const char *weekday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	time(&myRawtime);
	timeinfo1 = localtime(&myRawtime);
	timeinfo1->tm_year = year - 1900;
	timeinfo1->tm_mon = month - 1;
	timeinfo1->tm_mday = day;

	mktime(timeinfo1);
	int dayOfWeek;
	weekday1 = weekday[timeinfo1->tm_wday];
	//cout << "in determine week day, current week day is " <<  weekday1 << endl;

	if(weekday1 == "Sun"){
        dayOfWeek = 1;
	}
	if(weekday1 == "Mon"){
        dayOfWeek = 2;
	}
	if(weekday1 == "Tue"){
        dayOfWeek = 3;
	}
	if(weekday1 == "Wed"){
        dayOfWeek = 4;
	}
	if(weekday1 == "Thu"){
        dayOfWeek = 5;
	}
	if(weekday1 == "Fri"){
        dayOfWeek = 6;
	}
	if(weekday1 == "Sat"){
        dayOfWeek = 7;
	}
	return dayOfWeek;
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
vector<int> runStandardDate(char *argv[], string date) {

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
	int myDay = determineWeekDay(yearInt, monthInt, monthDay);
	//cout << "week day is " << myDay << endl;


	vector < int > fullDate;
	fullDate.push_back(dayInt);
	fullDate.push_back(monthInt -1);
	fullDate.push_back(monthDay);
	fullDate.push_back(yearInt - 1900);
	fullDate.push_back(myDay);
	return fullDate;
}

vector <int> isToday(string fullString){
    vector<int> todays;
	string string1 = "today";

	string fullString1 = fullString;
	if (case_insensitive_match(string1, fullString)) {
        //cout << "date determined to be today\n";
		time_t now;
		struct tm * timeinfo;

        time(&now);
		timeinfo = localtime(&now);

		//add relevant parts to vector
        todays.push_back(timeinfo->tm_yday);
        todays.push_back(timeinfo->tm_mon);
        todays.push_back(timeinfo->tm_mday);
        todays.push_back(timeinfo->tm_year);
        todays.push_back(timeinfo->tm_wday);
	}
	return todays;
}

vector<int> isYesterday(string fullString){
    vector<int> yesterday;
	string string1 = "yesterday";
	if (case_insensitive_match(string1, fullString)) {
        //cout << "date determined to be yesterday\n";
		time_t now;
		struct tm * timeinfo;

        time(&now);
		now = now - (24 * 60 * 60);
		timeinfo = localtime(&now);

		//add relevant parts to vector

        yesterday.push_back(timeinfo->tm_yday);
        yesterday.push_back(timeinfo->tm_mon);
        yesterday.push_back(timeinfo->tm_mday);
        yesterday.push_back(timeinfo->tm_year);
        yesterday.push_back(timeinfo->tm_wday);
	}
	return yesterday;
}

vector<int> isTomorrow(string fullString){
    vector<int> tomorrow;
	string string1 = "tomorrow";
	if (case_insensitive_match(string1, fullString)) {
        //cout << "date determined to be tomorrow\n";
		//cout << "date determined to be yesterday\n";
		time_t now;
		struct tm * timeinfo;

        time(&now);
		now = now + (24 * 60 * 60);
		timeinfo = localtime(&now);

		//add relevant parts to vector
        tomorrow.push_back(timeinfo->tm_yday);
        tomorrow.push_back(timeinfo->tm_mon);
        tomorrow.push_back(timeinfo->tm_mday);
        tomorrow.push_back(timeinfo->tm_year);
        tomorrow.push_back(timeinfo->tm_wday);
	}
	return tomorrow;
}

int case_insensitive_match(string s1, string s2) {
	//convert s1 and s2 into lower case strings
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0){
        return 1; //The strings are same
	}
	else{
        return 0; //not matched
	}

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
		    cout << "opening file called " << argv[i] << "\n";
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
            //check if it is today or tomorrow or yesterday
            vector<int> fullInput;
            cout << "printTime received value:" << date << "\n";
            if(isToday(date).size() != 0){
                cout << "today was true\n";
                fullInput = isToday(date);
            }
            else if(isTomorrow(date).size() != 0){
                cout << "tomorrow was true\n";
                fullInput = isTomorrow(date);
            }
            else if(isYesterday(date).size() != 0){
                cout << "yesterday was true\n";
                fullInput = isYesterday(date);
            }
            //try to run the other ones
            else if(runStandardDate(argv, date).size() == 0){
                cout << "valid . standard day\n";
                fullInput = runStandardDate(argv, date);
            }
            else if(isValidDashDate(date).size() == 0){
                cout << "valid dash day\n";
                fullInput = isValidDashDate(date);
            }

            //if the date works, set the time struct to it and print it
            if(fullInput.size() != 0){
                    char outputString[100];
                cout << "full input is set\n";
                struct tm *fullTime;
                fullTime->tm_yday = fullInput[0];
                fullTime->tm_mon = fullInput[1];
                fullTime->tm_mday = fullInput[2];
                fullTime->tm_year = fullInput[3];
                fullTime->tm_wday = fullInput[4];
                cout << "time struct is set\n";

                //print the time in the output format type
                if(stringReplace == true){
                    strcpy(outputString, toReplace.c_str());
                }
                //ISO formatted output
                else if(outputType == 'i'){
                    toReplace = {'%','Y','-','%','m','-','%','d'};
                    strcpy(outputString, toReplace.c_str());
                }
                //other unspecified output
                else{
                    toReplace = "%a %d %b %Y";
                    strcpy(outputString, toReplace.c_str());
                }
                //print the date
                char printString[100];
                strftime(printString, 100, outputString, fullTime);
                cout << "printing final date ";
                cout << printString << "\n";
            }
            else{
                cerr << "Input " << date << " is not correct format in program " << programName << "system exiting\n" << endl;
                exit(1);
            }
}





vector<int> isValidDashDate(string date) {
	vector < int > validDashDay;
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
		cerr << "Date is not of the correct format. for input " << date
				<< " system exiting" << endl;
		exit(1);
	}

	else {
		//convert monthDay to day of year
		int dayOfYear = monthDayToYearDay(month, monthDay, isLeap);
		if ((isValidYear(year)) && (checkValidDay(dayOfYear, isLeap))
				&& (month <= 12) && (month >= 1)) {
			//get the week day and put it in a vector and return that shit
			int weekDay = determineWeekDay(year, month, dayOfYear);
			validDashDay.push_back(dayOfYear);
			validDashDay.push_back(month -1);
			validDashDay.push_back(monthDay);
			validDashDay.push_back(year - 1900);
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
