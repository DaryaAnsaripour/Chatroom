#include "../headers/Userserver.hpp"

Userserver::Userserver(int id, int client_socket)
: id(id), client_socket(client_socket), name("Anonymous")
{}

Userserver::~Userserver()
{
    if (client_thread)
    {
        if (client_thread->joinable())
        {
            client_thread->detach();
            delete client_thread;
        }
        client_thread = 0;
    }
    if (client_socket)
        close(client_socket);
}