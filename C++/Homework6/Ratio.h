#ifndef RATIO_H_INCLUDED
#define RATIO_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>

class Ratio{
    long my_numerator;
    long my_denominator;
public:
    //if the user tries to set the constructor to divide by zero THROW an error
    // //constructor using ints
    Ratio(int value1, int value2);

    //constructor using longs
    Ratio(long value1, long value2);

    //single parameter constructor
    Ratio(long value1);

    //copy constructor
    Ratio(const Ratio &);

    //destructor
    ~Ratio();

    //operator=
    Ratio & operator=(const Ratio &);

    static int get_count();


    //getNumerator function called numerator
    long numerator() const;
    //set numerator function called numerator(long)
    void numerator(long value);
    //get denominator function called denominator
    long denominator() const;
    //set denominator function called denominator(long)
    void denominator(long value);

    //ratio function returns a long double fraction
    double ratio() const;
    //compare function
    int compare(Ratio r) const;
    int compare(long double);
    //check if negative values are present
    void checkNegative();

    //add undefined number of parameters to current ratio
    Ratio & add(Ratio r);
    //gcd function to help
    int gcd(int a, int b) ;
    //other gcd function
    void lowest(int &den3, int &num3);
    //subtract Ratio funciton
    Ratio & subtract(Ratio r);
    //multiply ratio
    Ratio & multiply(Ratio r);
    //divide ratio
    Ratio & divide(Ratio r);

    //hw6 functions
    Ratio & operator+(const Ratio &);
    Ratio & operator-(const Ratio &);
    Ratio & operator*(const Ratio &);
    Ratio & operator/(const Ratio &);

    template <typename Ratio, typename... Others> 
    Ratio add(Ratio &var1, Others... var2) const{ 
    Ratio newRatio = var1 + (add(var2), ...);
    return newRatio;
} 

};

//non member functions
std::ostream& operator<<(std::ostream& os, const Ratio& r);

//overloaded input operator
std::istream & operator>>(std::istream& is, Ratio& r);

#endif // RATIO_H_INCLUDED


//gcd functions found from https://www.geeksforgeeks.org/program-to-add-two-fractions/
