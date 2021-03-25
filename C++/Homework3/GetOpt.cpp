
void runStandardDate(int argc, char *argv[]){
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

		//check the input for errors
		//separate incoming string into year and day strings
		//check the string for illegal characters
		while (cin) {
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
			if (fullString[0] == '\n') {
				cerr
						<< "line contains a new line character and no data in program "
						<< programName << "\n";
				exit(0);
			}
			if (isAllValidCharacters(fullString)) {
				fullString1 = fullString;
			}

			else {
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
			if ((checkValidDay(dayInt, leapYear) == true)
					&& (validYear == true)) {
				monthInt = determineMonth(leapYear, dayInt);
				monthName = stringMonth(monthInt);

				//convert to proper format
				monthInt = determineMonth(leapYear, dayInt);
				string monthName = stringMonth(monthInt);
				monthDay = dayOfMonth(monthInt, dayInt, leapYear);
				day = determineWeekDay(yearInt, monthInt, monthDay);

				//print date
				oss << day << " " << setw(2) << setfill('0') << monthDay << " "
						<< monthName << " " << setw(4) << setfill('0')
						<< yearInt;
				fullOutput = oss.str();

			}
			if (fullOutput != previous) {
				cout << fullOutput << "\n";
				fullOutput = previous;
			} else {
			}

		}    //end while loop
}
