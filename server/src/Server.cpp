#include "../headers/Server.hpp"

Server::Server()
{
    unique_id = 0;
    MAX_LEN = 150;
    clients.clear();

    do_command("CREATE TABLE users (username string,password string,name string)");
    do_command("CREATE TABLE groups (name string,description string,usersNum int)");
    do_command("CREATE TABLE user_group (username string,group string)");
    do_command("CREATE TABLE pv_msg (id int,user1 string,user2 string,time timestamp,msg string)");
    do_command("CREATE TABLE g_msg (id int,group string,user string,time timestamp,msg string)");
    do_command("CREATE TABLE buffer (id int,is_group int)");

}

void Server::start_listening()
{
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(-1);
	}

    struct sockaddr_in server;
    server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
    if ((bind(server_socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in))) == -1)
	{
		perror("bind");
		exit(-1);
	}

    if ((listen(server_socket, 5)) == -1)
	{
		perror("listen");
		exit(-1);
	}
    multi_print("... Chat Room start listening ...");   
}

void Server::start_accepting()
{
    struct sockaddr_in client;
    int client_socket;
    unsigned int len = sizeof(sockaddr_in);

    while (true)
    {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client, &len)) == -1)
        {
            perror("accept: ");
			exit(-1);
        } 
        unique_id++;
        Userserver* user_server = new Userserver(unique_id, client_socket);
        thread* client_thread = new thread(handle_client, this, user_server);
        user_server->client_thread = client_thread;
        add_client(user_server);
    }
}

void Server::add_client(Userserver* user_server)
{
    lock_guard<mutex> guard(clients_mtx);
	clients[user_server->id] = user_server;
}

void Server::handle_client(Server* server, Userserver* user_server)
{
    if (server->login_client(user_server))
    {
        char message[server->MAX_LEN];
        int bytes_received;
        while(true)
        { 
            bytes_received = recv(user_server->client_socket, message, sizeof(message), 0);
            if(bytes_received <= 0)
                break; 
            server->multi_print(string(user_server->name) + " : " + string(message));		
            server->do_for_user(server->users[user_server->name], message);
        }
        server->users[user_server->name]->user_server = 0;
    }
    server->end_connection(user_server->id);
}

bool Server::login_client(Userserver* user_server)
{
    while(true)
    {
        char command[1];
        int bytes_received = recv(user_server->client_socket, command, sizeof(command), 0);
        if(bytes_received <= 0)
            return false;

        if(command[0]=='l')
        {
            char username[MAX_LEN], password[MAX_LEN];

            int bytes_received = recv(user_server->client_socket, username, sizeof(username), 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, password, sizeof(password), 0);
            if(bytes_received <= 0)
                return false;
            
            int request_case = try_get_user(user_server, username, password);
    
            if (request_case==0)
            {
                string error_message = "Server | User " + string(username) + " doesn't exist, please try again.";
                send_message(user_server->client_socket, error_message);
                multi_print(error_message);
                continue;
            }
            else if(request_case==1)
            {
                string error_message = "Server | Invalid password for " + string(username);
                send_message(user_server->client_socket, error_message);
                multi_print(error_message);
                continue;

            }
            else
            {
                user_server->name = username;
                string welcome_message = "Server | welcome " + string(username);
                send_message(user_server->client_socket, welcome_message);
                multi_print(welcome_message);
                return true;
            }
        }
        
        else if(command[0]=='s')
        {
            char username[MAX_LEN], password1[MAX_LEN], password2[MAX_LEN], name[MAX_LEN];

            int bytes_received = recv(user_server->client_socket, username, sizeof(username), 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, name, sizeof(name), 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, password1, sizeof(password1), 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, password2, sizeof(password2), 0);
            if(bytes_received <= 0)
                return false;

            int request_case = try_add_user(user_server, username, password1, password2, name);
    
            if(request_case==0)
            {
                string error_message = "Server | Username " + string(username) + " is already taken, please try again.";
                send_message(user_server->client_socket, error_message);
                multi_print(error_message);
                continue;
            }
            else if(request_case==1)
            {
                string error_message = "Server | Passwords must match, please try again.";
                send_message(user_server->client_socket, error_message);
                multi_print(error_message);
                continue;
            }
            else
            {
                user_server->name = username;
                string welcome_message = "Server | welcome " + string(username);
                send_message(user_server->client_socket, welcome_message);
                multi_print(welcome_message);
                return true;
            }
        }
    }
}

int Server::try_get_user(Userserver* user_server, string username, string password)
{
    
    if (users.find(username) != users.end())
    {
        // case successful
        if (users[username]->password == password)
        {
            users[username]->user_server = user_server;
            return 2;
        }
        // case not password matching
        else
            return 1;
    }
    // case not username existed
    else
        return 0;
}

int Server::try_add_user(Userserver* user_server, string username, string password1, string password2, string name)
{
    // case existed username
    if(users.find(username) != users.end())
        return 0;
    // case not same passes
    else if(password1!=password2)
        return 1;
    // case successful
    else
    {
        users[username] = new User(username, password1, name, user_server);
        do_command("INSERT INTO users VALUES (\"" + username + "\",\"" + password1 + "\",\"" + name + "\")");
        return 2;
    }
}

void Server::do_for_user(User* user, string message)
{
    regex changenamepat("change my name to (.+)");
    regex creategppat("create group (.+)");
    regex invitepat("invite (.+) to (.+)");
    regex pvpat("#pv #([^\\s]+) ([^#]+)");
    regex gppat("#gp #([^\\s]+) ([^#]+)");
    smatch matches;
    try
    {
        if(message=="#menu")
        {
            send_message(user->user_server->client_socket, "1. change my name to\n2. show my groups\n3. show my friends\n4. show blocked\n5. exit");
        }
        else if(message=="show my groups")
        {
            send_groups(user);
        }
        else if(message=="show my friends")
        {
            send_friends(user);
        }
        else if(message=="show blocked")
        {

        }
        else if(regex_search(message, matches, changenamepat))
        {
            string new_name=matches[1];
            change_name(user, new_name);
        }
        else if(regex_search(message, matches, creategppat))
        {
            string groupname=matches[1];
            create_group(user, groupname);
        }
        else if(regex_search(message, matches, invitepat))
        {
            string new_member=matches[1];
            string groupname=matches[2];
            invite_group(user, new_member, groupname);
        }
        else if(regex_search(message, matches, pvpat))
        {

        }
        else if(regex_search(message, matches, gppat))
        {
            
        }

    }
    catch(const char* msg)
    {
        
    }
    
}




void Server::change_name(User* user, string new_name)
{
    user->name=new_name;
    do_command("UPDATE users SET name=\"" + new_name + "\" WHERE username==\"" + user->username +"\"");
    send_message(user->user_server->client_socket, "Server | Your name changed succesfully!");
}

void Server::send_groups(User* user)
{
    string message="Server | Groups:";
    int i=1;

    vector<string>* gps=do_command("SELECT group FROM user_group WHERE username==\"" + user->username + "\"");
    
    for(string &group: *gps)
        message+="\n" + to_string(i++) + ": " + group;
    
    if(i==1)
        message+=" You are not a member of any group!";

    send_message(user->user_server->client_socket, message);
}

void Server::send_friends(User* user)
{
    string message="Server | Friends:";
    int i=1;

    vector<string>* friends1=do_command("SELECT user2 FROM pv_msg WHERE user1==\"" + user->username + "\"");
    sort(friends1->begin(), friends1->end());
    friends1->erase(unique(friends1->begin(), friends1->end()), friends1->end());

    vector<string>* friends2=do_command("SELECT user1 FROM pv_msg WHERE user2==\"" + user->username + "\"");
    sort(friends2->begin(), friends2->end());
    friends2->erase(unique(friends2->begin(), friends2->end()), friends2->end());

    for(string &frnd: *friends1)
        message+="\n" + to_string(i++) + ": " + frnd;

    for(string &frnd: *friends2)
        message+="\n" + to_string(i++) + ": " + frnd;

    if(i==1)
        message+=" You have no friends!";
    
    send_message(user->user_server->client_socket, message);
}

// show blocked

void Server::create_group(User* user, string groupname)
{
    if (groups.find(groupname) != groups.end())
        throw "Group name is already taken, try a different group name.";

    char description[MAX_LEN];
    send_message(user->user_server->client_socket, "Enter some descreption :");
    int bytes_received = recv(user->user_server->client_socket, description, sizeof(description), 0);
    if(bytes_received <= 0)
        return;

    Group* new_group=new Group(groupname, description);
    new_group->admin=user;
    new_group->add_member(user);
    do_command("INSERT INTO groups VALUES (\"" + groupname + "\",\"" + description + "\"," + "1)");
    send_message(user->user_server->client_socket, "Server | Group created succesfully!");

}

void Server::invite_group(User* inviter, string new_member ,string groupname)
{
    check_group(groupname);
    check_user(new_member);
    groups[groupname]->has_premission(inviter);
    groups[groupname]->add_member(users[new_member]);
    groups[groupname]->users_num++;
    do_command("INSERT INTO user_group VALUES (\"" + new_member + "\",\"" + groupname + "\")");
    do_command("UPDATE groups SET usersNum=" + to_string(groups[groupname]->users_num) + " WHERE name==\"" + groupname +"\"");

    send_message(inviter->user_server->client_socket, "Server | You invited" + users[new_member]->name);
    broadcast_message("Server | " + inviter->name + " invited" + users[new_member]->name, inviter->username, groups[groupname]->users);
}






vector<string>* Server::do_command(string cmnd)
{
    vector<string>* recs;
    regex createpat("^CREATE TABLE ([a-zA-Z0-9_]+) \\((.+)\\)$");\
    regex insertpat("^INSERT INTO ([a-zA-Z0-9_]+) VALUES \\((.+)\\)$");
    regex deletepat("^DELETE FROM ([a-zA-Z0-9_]+) WHERE (.+)$");
    regex updatepat("^UPDATE ([a-zA-Z0-9_]+) SET (.+) WHERE (.+)$");
    regex selectpat("^SELECT (.+) FROM ([a-zA-Z0-9_]+) WHERE (.+)$");
    smatch matches;

    if(regex_search(cmnd, matches, createpat))
    {
        string tablename=matches[1];
        database[tablename]=new Tablefile(cmnd);
    }
    else if(regex_search(cmnd, matches, insertpat))
    {
        string tablename=matches[1];
        database[tablename]->insert_record(cmnd);
    }
    else if(regex_search(cmnd, matches, deletepat))
    {
        string tablename=matches[1];
        database[tablename]->delete_record(cmnd);
    }
    else if(regex_search(cmnd, matches, updatepat))
    {
        string tablename=matches[1];
        database[tablename]->update_record(cmnd);
    }
    else
    {
        string tablename=matches[2];
        recs=database[tablename]->select_records(cmnd);
    }
    return recs;
}

void Server::get_users_from_db()
{
    vector<string>* records=do_command("SELECT * FROM users");
    for(string &record: *records)
    {
        vector<string> user=mysplit(record, 0);
        users[user[0]]=new User(user[0], user[1], user[2]);
    }
}

void Server::multi_print(string str)
{	
	lock_guard<mutex> guard(print_mtx);
	cout<<str<<endl;
}

void Server::send_message(int client_socket, string message)
{
    send(client_socket, &message[0], MAX_LEN, 0);
}

void Server::broadcast_message(string message, string sender_username, map<string, User*> dest_users)
{
    for(auto &user: dest_users)
    {
        if((user.first != sender_username) && (user.second->user_server))
            send_message(user.second->user_server->client_socket, message);

        // ATTENTION case !user.second->user_server must be handled by writing in buffer
    }

}

void Server::check_user(string name, bool connected)
{
    if (users.find(name) == users.end())
        throw "This user doesn't exist";
    if (connected && !users[name]->user_server)
        throw "This user isn't connected";

    // ATTENTION case !user.second->user_server must be handled by writing in buffer

}

void Server::check_group(string groupname)
{
    if (groups.find(groupname) == groups.end())
        throw "This group doesn't exist";
}





void Server::end_connection(int id)
{
    lock_guard<mutex> guard(clients_mtx);
    if (clients[id])
        delete clients[id];
}

Server::~Server()
{
    delete database["users"];
    delete database["groups"];
    delete database["user_group"];
    delete database["pv_msg"];
    delete database["g_msg"];
    delete database["buffer"];
}
