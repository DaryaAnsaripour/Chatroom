#ifndef GROUP_H
#define GROUP_H

#include "../headers/User.hpp"

class Group
{
public:
    string name;
    string description;
    map<string, User*> users;
    map<string, User*> banned_users;
    User* admin;
    int users_num;
    

    Group(string name, string description="", int users_num=0);
    void has_premission(User* user);
    void add_member(User* new_member);
    void remove_member(User* remover, User* member);
    void left(User* member);
    void ban_user(User* banner, User* banned);
    void unban_user(User* unbanner, User* unbanned);
    bool is_member(User* user);
};



#endif