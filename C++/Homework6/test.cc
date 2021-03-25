#include "Ratio.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
cout << "Program running\n";
cout << "Creating ratio object using 4 and 2\n";

Ratio *myRatio = new Ratio(4,2);

cout << "The numerator is " << myRatio->numerator() << ". The denominator is " << myRatio->denominator() <<  "\n";
cout << "Setting numerator to 6 and denominator to 3\n";
long newNumer = 6;
long newDenom = 3;
myRatio->numerator(newNumer);
myRatio->denominator(newDenom);
cout << "The new numerator is " << myRatio->numerator() << ". The new denominator is " << myRatio->denominator() << "\n\n";

cout << "Creating ratio 2 with values 4 and 5\n";
Ratio myRatio2 = Ratio(4,5);
cout << "Setting ratio 1 equal to ratio 2\n";
*myRatio = myRatio2;
cout << "The new values of ratio 1 are numerator: " << myRatio->numerator() << " denominator: " << myRatio->denominator() << "\n" << endl;

cout << "The ratio of ratio 1 in decimal format is " << myRatio->ratio() << "\n";

cout << "Adding ratio1 to ratio2 should equal to 8/5. \n";
Ratio addedRatio = myRatio->add(myRatio2);
cout << "New ratio from first two added is numerator: " << addedRatio.numerator() << " denominator: " << addedRatio.denominator() << "\n\n";

cout << "Subtracting ratio1 from ratio2 should be equal to 0\n";
Ratio subtractedRatio = myRatio->subtract(myRatio2);
cout << "New ratio from first two subtracted is numerator: " << subtractedRatio.numerator() << " denominator " << subtractedRatio.denominator() << "\n\n";

cout << "Multiplying ratio1 by ratio2 should be equal to 16/25\n";
Ratio multiplied = myRatio->multiply(myRatio2);
cout << "Mulitplied numerator is " << multiplied.numerator() << ". Multiplied denominator is " << multiplied.denominator() << endl;

cout << "Dividing ratio1 by ratio2, should be 40/40 or 1\n";
Ratio divided = myRatio->divide(myRatio2);
cout << "Divided numerator is " << divided.numerator() << ". Divided denominator is " << divided.denominator() << endl;
Ratio printRat(4,5);

cout << "Printing ratio should say 4/5: " << printRat << "\n";

cout << "Adding using operator+\n";
Ratio addFirst = Ratio(3,5);
Ratio addSecond = Ratio(1,5);
Ratio operatorAdded = addFirst + addSecond;
cout << "Added is " << operatorAdded << "\n";

}
