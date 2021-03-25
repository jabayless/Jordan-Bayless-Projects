#ifndef RATIO_H_INCLUDED
#define RATIO_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>

class Ratio{
private:
    long numerator;
    long denominator;
public:
    //if the user tries to set the constructor to divide by zero THROW an error
    //constructor using ints
    Ratio(int value1, int value2);

    //constructor using longs
    Ratio(long value1, long value2);

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

    //get denominator function called denominator

    //set denominator function called denominator(long)

    //ratio function returns a long double fraction


    //destructor

};

//non member functions



#endif // RATIO_H_INCLUDED
