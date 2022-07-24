#include "../headers/Timestamp.hpp"


const regex timestamp::timepattern=regex("([0-9][0-9]):([0-9][0-9]):([0-9][0-9])");

timestamp::timestamp(string time)
{
    smatch matches;
    if(regex_search(time, matches, timepattern))
    {
        hour=stoi(matches[1]);
        minute=stoi(matches[2]);
        second=stoi(matches[3]);
    }
}

bool timestamp::operator<(const timestamp &right) const
{
    if(hour<right.hour)
        return true;
    else if((hour==right.hour) && (minute<right.minute))
        return true;
    else if((hour==right.hour) && (minute==right.minute) && (second<right.second))
        return true;
    else
        return false;
}

bool timestamp::operator>(const timestamp &right) const
{
    if(hour>right.hour)
        return true;
    else if((hour==right.hour) && (minute>right.minute))
        return true;
    else if((hour==right.hour) && (minute==right.minute) && (second>right.second))
        return true;
    return false;
}

bool timestamp::operator==(const timestamp &right) const
{
    if((hour==right.hour) && (minute==right.minute) && (second==right.second))
        return true;
    return false;
}
