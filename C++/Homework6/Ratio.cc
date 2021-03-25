#include "Ratio.h"

using namespace std;

int ratioCount = 0;

//regular constructor
Ratio::Ratio(long value1, long value2): my_numerator((long)value1), my_denominator((long)value2){
    Ratio::checkNegative();
    try {
        if(denominator() ==  0){
		throw std::runtime_error("Error division by 0\n");
        }
	}
	catch (std::exception &e) {}

ratioCount++;
}

//regular constructor
Ratio::Ratio(int value1, int value2) : my_numerator((long)value1), my_denominator((long)value2)
{
    Ratio::checkNegative();
    try
    {
        if (denominator() == 0)
        {
            throw std::runtime_error("Error division by 0\n");
        }
    }
    catch (std::exception &e)
    {
    }
    ratioCount++;
}

//single argument constructor
Ratio::Ratio(long value1){
Ratio::checkNegative();
my_denominator = 1;
my_numerator = value1;
ratioCount++;
}


//copy constructor
Ratio::Ratio(const Ratio &rhs) : my_numerator(rhs.my_numerator), my_denominator(rhs.my_denominator){
    Ratio::checkNegative();
   try {
        if(denominator() ==  0){
		throw std::runtime_error("Error division by 0\n");
	}
	catch (std::exception &e) {}
    ratioCount++;
}
    //destructor
    Ratio::~Ratio(){
    ratioCount--;
    }

    //operator=
    Ratio & Ratio::operator=(const Ratio &rhs){
        Ratio::checkNegative();
   try {
        if(denominator() ==  0){
		throw std::runtime_error("Error division by 0\n");
	}
	catch (std::exception &e) {}
    my_numerator = rhs.my_numerator;
    my_denominator = rhs.my_denominator;
    return *this;
    }

    //accessor for numerator
    long Ratio::numerator() const{
        return my_numerator;
    }
    //mutator for numerator
    void Ratio::numerator(long value){
        my_numerator = value; 
    }

    //accessor for denominator
    long Ratio::denominator() const{
        return my_denominator;
    }
    //mutator for denominator
    void Ratio::denominator(long value){
        Ratio::checkNegative();
        try {
        if(denominator() ==  0){
		throw std::runtime_error("Error division by 0\n");
	}
	catch (std::exception &e) {}
        my_denominator = value;
    }
    //get count funtaion
    int Ratio::get_count(){
        return ratioCount;
    }

    //ratio funtion
    double Ratio::ratio() const{
        double ratio = ((double)my_numerator / (double)my_denominator);
        return ratio;
    }

//addition operator
Ratio &Ratio::add(Ratio r) {

    int den1 = my_denominator;
    int den2 = r.denominator();
    int num1 = my_numerator;
    int num2 = r.numerator();
    // Finding gcd of den1 and den2 
    int den3 = gcd(den1,den2); 
  
    // Denominator of final fraction obtained 
    // finding LCM of den1 and den2 
    // LCM * GCD = a * b  
    den3 = (den1*den2) / den3; 
  
    // Changing the fractions to have same denominator 
    // Numerator of the final fraction obtained 
    int num3 = (num1)*(den3/den1) + (num2)*(den3/den2); 
  
    // Calling function to convert final fraction 
    // into it's simplest form 
    lowest(den3,num3);

    Ratio *returnValue = new Ratio(num3, den3);
    return *returnValue;
}

Ratio & Ratio::subtract(Ratio r){
    int den1 = my_denominator;
    int den2 = r.denominator();
    int num1 = my_numerator;
    int num2 = r.numerator();
    // Finding gcd of den1 and den2 
    int den3 = gcd(den1,den2); 
  
    // Denominator of final fraction obtained 
    // finding LCM of den1 and den2 
    // LCM * GCD = a * b  
    den3 = (den1*den2) / den3; 
  
    // Changing the fractions to have same denominator 
    // Numerator of the final fraction obtained 
    int num3 = (num1)*(den3/den1) - (num2)*(den3/den2);
  
    // Calling function to convert final fraction 
    // into it's simplest form 
    lowest(den3,num3);

    Ratio *returnValue = new Ratio(num3, den3);
    return *returnValue;
}

Ratio & Ratio::multiply(Ratio r){
    int newNum = (my_numerator * r.numerator());
    int newDen = (my_denominator * r.denominator());
    lowest(newDen, newNum);
    long lNum = (long)newNum;
    long lDen = (long)newDen;
    Ratio * returnValue = new Ratio(lNum, lDen);
    return *returnValue;
}

void Ratio::checkNegative(){
    if((denominator() < 0 ) && (numerator() > 0)){
        numerator(-1*numerator());
    }
    else if((denominator() < 0 && (numerator() < 0) )){
        numerator(-1*numerator());
        denominator(-1*denominator());
    }
}

Ratio & Ratio::divide(Ratio r){
    int num = (my_numerator * r.denominator());
	int denom = (my_denominator * r.numerator());
    lowest(denom, num);
    Ratio * returnValue = new Ratio((long)num, (long)denom);
    return *returnValue;
}

int Ratio::compare(long double x){
    if(this->ratio() < x){
        return -1;
    }
    else if(this->ratio() > x){
        return 1;
    }
    else{
        return 0;
    } 
}

int Ratio::compare(Ratio r) const{
    if(this->ratio() < r.ratio()){
        return -1;
    }
    else if(this->ratio() > r.ratio()){
        return 1;
    }
    else{
        return 0;
    }
}


Ratio & Ratio::operator+(const Ratio &rhs) {
    Ratio retval = Ratio::add(rhs);
    return *retval;
}


// Function to return gcd of a and b 
int Ratio::gcd(int a, int b) { 
    if (a == 0) 
        return b; 
    return gcd(b%a, a); 
}

// Function to convert the obtained fraction 
// into it's simplest form 
void Ratio::lowest(int &den3, int &num3){ 
    // Finding gcd of both terms 
    int common_factor = gcd(num3,den3); 
  
    // Converting both terms into simpler  
    // terms by dividing them by common factor  
    den3 = den3/common_factor; 
    num3 = num3/common_factor; 
} 

//non member functions
//overloaded ouptut operator
std::ostream& operator<<(std::ostream& os, const Ratio& r){
    //if numerator or denominator is negative but not both
    //make the numerator negative and the denominator positive
    os << r.numerator() << '/' << r.denominator();
    return os;
}

//overloaded input operator
std::istream & operator>>(std::istream& is, Ratio& r){
    //parse input string to number character number
    
    //check if character is '/'

    //second number is just number

    //check for divide by 0
    long n;
    long d;
    string s;
    is >> n >> s >> d;
    r.numerator(n);
    r.denominator(d);
    return is;
}
