#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "Console.hpp"

class timestamp
{
protected:
    static const regex timePattern;
    int hour;
    int minute;
    int second;
public:
    timestamp(string time);
    bool operator>(const timestamp &right) const;
    bool operator<(const timestamp &right) const;
    bool operator==(const timestamp &right) const;

    
};

#endif
