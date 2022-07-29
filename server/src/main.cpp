#include "../headers/Server.hpp"


Server* server = 0;

void exit_app(int sig_num);

int main()
{
    server = new Server();
    signal(SIGINT, exit_app);
    server->get_users_from_db();
    server->get_groups_from_db();
    server->start_listening();
    server->start_accepting();
    exit_app(0);

    
}

void exit_app(int sig_num)
{
    if (server)
        delete server;
    cout<<"...bye..."<<endl;
    exit(sig_num);
}