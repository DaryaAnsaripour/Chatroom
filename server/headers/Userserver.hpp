#ifndef USERSERVER_H
#define USERSERVER_H

#include "../headers/Console.hpp"

class Userserver
{
public:
    int id;
    int client_socket;
    thread* client_thread;
    string name;

    Userserver(int id, int client_socket);
    ~Userserver();
};


#endif