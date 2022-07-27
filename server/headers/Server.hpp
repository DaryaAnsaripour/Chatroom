#ifndef SERVER_H
#define SERVER_H

#include "../headers/Tablefile.hpp"
#include "../headers/Group.hpp"

class Server
{
public:
    int unique_id;
    int MAX_LEN;
    int server_socket;
    int pv_id;
    int gp_id;
    mutex print_mtx, clients_mtx;
    map<string, Tablefile*> database;
    map<string, User*> users;
    map<string, Group*> groups;
    map<int, Userserver*> clients;

    // Tablefile* users;
    // Tablefile* groups;
    // Tablefile* user_group;
    // Tablefile* pv_msg;
    // Tablefile* g_msg;
    // Tablefile* buffer;


    Server();
    void start_listening();
    void start_accepting();
    void add_client(Userserver* user_server);
    static void handle_client(Server* server, Userserver* user_server);
    bool login_client(Userserver* user_server);
    int try_get_user(Userserver* user_server, string username, string password);
    int try_add_user(Userserver* user_server, string username, string password1, string password2, string name);
    void do_for_user(User* user, string message);


    void change_name(User* user, string new_name);
    void send_groups(User* user);
    void send_friends(User* user);
    void send_blocked(User* user);
    void create_group(User* user, string groupname);
    void invite_group(User* inviter, string new_member ,string groupname);
    void block_user(User* blocker, string blocked);
    void unblock_user(User* unblocker, string unblocked);
    void send_pv(User* sender, User* receiver, string message);
    void send_gp(User* sender, string groupname, string message);
    void send_buffer(User* user);





    vector<string>* do_command(string cmnd);
    void get_users_from_db();
    void multi_print(string str);
    void send_message(int client_socket, string message);
    void broadcast_message(string message, string sender_username, map<string, User*> dest_users);
    void check_user(string username, bool connected=true);
    void check_group(string groupname);
    void check_blocked(User* sender, User* receiver);
    string curr_time();

    void end_connection(int id);
    void delete_users();
    void close_connection();
    ~Server();
};

#endif