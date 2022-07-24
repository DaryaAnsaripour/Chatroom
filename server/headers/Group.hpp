#ifndef GROUP_H
#define GROUP_H

#include "../headers/User.hpp"

class Group
{
public:
    string name;
    string description;
    map<string, User*> users;
    User* admin;
    int users_num;
    

    Group(string name, string description="");
    void has_premission(User* user);
    void add_member(User* new_member);
};



#endif