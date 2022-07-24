#ifndef CLIENT_H
#define CLIENT_H

#include "Console.hpp"

class Client
{
public:
    int MAX_LEN;
    int client_socket;
    bool logged_in;
    bool exited;
    char* username;
    char* password;
    char* name;
    string menu;
    mutex print_mtx;
    thread* send_thread;
    thread* recv_thread;


    Client();
    void start_connecting();
    void start_communicating();
    void login();
    void send_handler(Client* client);

    void multi_print(string message, bool you=true);
    ~Client();
};



#endif