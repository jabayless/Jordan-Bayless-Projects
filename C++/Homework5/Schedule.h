#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED
#include "Event.h"
#include <iostream>
#include <fstream>

//this is a container class for Events, should be stored in chronological order
class Schedule{
    private:
        int size;
        std::vector<Event> schedule;


    public:
        Schedule(std::istream &);

        Schedule(std::ifstream &);

        Schedule(std::string fileName);

        Schedule(char * fileName);

        bool empty();

        int size();

        void clear();

        void read(std::istream &);

};


#endif