#ifndef USER_H
#define USER_H

#include "../headers/Userserver.hpp"

class User
{
public:
    Userserver* user_server;
    string username;
    string password;
    string name;

    User(string username, string password, string name, Userserver* user_server=0);
};


#endif