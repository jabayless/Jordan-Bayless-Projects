#include "Ratio.h"

using namespace std;

int ratioCount = 0;

//regular constructor
Ratio::Ratio(long value1, long value2): numerator(value1), denominator(value2){
ratioCount++;
}

//single argument constructor
Ratio::Ratio(long value1, denominator = 1): numerator(value1){
ratioCount++;
}


//copy constructor
Ratio::Ratio(const Ratio &rhs) : numerator(rhs.numerator), denominator(rhs.denominator){
    ratioCount++;
}
    //destructor
    Ratio::~Ratio(){
    ratioCount--;
    }

    //operator=
    Ratio & Ratio::operator=(const Ratio &rhs){
    numerator = rhs.numerator;
    denominator = rhs.denominator;
    return *this;
    }

    //accessor for numerator
    long Complex::numerator() const {
    return numerator;
    }

    static int get_count();
