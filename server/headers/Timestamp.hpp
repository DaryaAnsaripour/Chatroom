#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "Console.hpp"

class timestamp
{
public:
    static const regex timepattern;
    int hour;
    int minute;
    int second;

    timestamp(string time);
    bool operator>(const timestamp &right) const;
    bool operator<(const timestamp &right) const;
    bool operator==(const timestamp &right) const;

    
};

#endif
