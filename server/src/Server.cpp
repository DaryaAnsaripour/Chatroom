#include "../headers/Server.hpp"

Server::Server()
{
    unique_id = 0;
    pv_id = 0;
    gp_id = 0;
    MAX_LEN = 200;
    clients.clear();

    do_command("CREATE TABLE users (username string,password string,name string)");
    do_command("CREATE TABLE blocks (blocker string,blocked string)");
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

    // while(bind(server_socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in)))
    // {
    //     cout<<"couldn't bind to ip and port trying again..."<<endl;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

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
            bytes_received = recv(user_server->client_socket, message, server->MAX_LEN, 0);
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
        char command[MAX_LEN];
        int bytes_received = recv(user_server->client_socket, command, MAX_LEN, 0);
        if(bytes_received <= 0)
            return false;

        if(command[0]=='l')
        {
            char username[MAX_LEN], password[MAX_LEN];

            int bytes_received = recv(user_server->client_socket, username, MAX_LEN, 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, password, MAX_LEN, 0);
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
                do_for_user(users[username], "#menu");
                send_buffer(users[username]);
                return true;
            }
        }
        
        else if(command[0]=='s')
        {
            char username[MAX_LEN], password1[MAX_LEN], password2[MAX_LEN], name[MAX_LEN];

            int bytes_received = recv(user_server->client_socket, username, MAX_LEN, 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, name, MAX_LEN, 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, password1, MAX_LEN, 0);
            if(bytes_received <= 0)
                return false;
            bytes_received = recv(user_server->client_socket, password2, MAX_LEN, 0);
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
                do_for_user(users[username], "#menu");
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
    regex changenamepat("change my name to ([^\\s]+)");
    regex creategppat("create group ([^\\s]+)");
    regex invitepat("invite ([^\\s]+) to ([^\\s]+)");
    regex blockuserpat("^block ([^\\s]+)");
    regex unblockuserpat("^unblock ([^\\s]+)");
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
            send_blocked(user);

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
        else if(regex_search(message, matches, blockuserpat))
        {
            string blocked=matches[1];
            block_user(user, blocked);
        }
        else if(regex_search(message, matches, unblockuserpat))
        {
            string unblocked=matches[1];
            unblock_user(user, unblocked);
        }
        else if(regex_search(message, matches, pvpat))
        {
            string receiver=matches[1];
            string msg=matches[2];
            check_user(receiver, false);
            send_pv(user, users[receiver], msg);
        }
        else if(regex_search(message, matches, gppat))
        {
            string groupname=matches[1];
            string msg=matches[2];
            send_gp(user, groupname, msg);
        }
        else
            throw "The command is not executable";

    }
    catch(const char* msg)
    {
        send_message(user->user_server->client_socket, "Server | There is a problem ( " + string(msg) + " )");
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

    vector<string>* gps=new vector<string>();
    gps=do_command("SELECT (group) FROM user_group WHERE username==\"" + user->username + "\"");
    
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

    vector<string>* friends1=new vector<string>();
    friends1=do_command("SELECT (user2) FROM pv_msg WHERE user1==\"" + user->username + "\"");
    sort(friends1->begin(), friends1->end());
    friends1->erase(unique(friends1->begin(), friends1->end()), friends1->end());

    vector<string>* friends2=new vector<string>();
    friends2=do_command("SELECT (user1) FROM pv_msg WHERE user2==\"" + user->username + "\"");
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

void Server::send_blocked(User* user)
{
    string message="Server | Blocked:";
    int i=1;

    vector<string>* blocked=new vector<string>();
    blocked=do_command("SELECT (blocked) FROM blocks WHERE blocker==\"" + user->username + "\"");

    for(string &usr: *blocked)
        message+="\n" + to_string(i++) + ": " + usr;
    
    if(i==1)
        message+=" You have not blocked anyone.";

    send_message(user->user_server->client_socket, message);
}

void Server::create_group(User* user, string groupname)
{
    if (groups.find(groupname) != groups.end())
        throw "Group name is already taken, try a different group name.";

    char description[MAX_LEN];
    send_message(user->user_server->client_socket, "Enter some descreption :");
    int bytes_received = recv(user->user_server->client_socket, description, MAX_LEN, 0);
    if(bytes_received <= 0)
        return;

    Group* new_group=new Group(groupname, description);
    new_group->admin=user;
    new_group->add_member(user);
    groups[new_group->name]=new_group;
    do_command("INSERT INTO groups VALUES (\"" + groupname + "\",\"" + description + "\"," + "1)");
    do_command("INSERT INTO user_group VALUES (\"" + user->username + "\",\"" + groupname + "\"," + "1)");
    send_message(user->user_server->client_socket, "Server | Group created succesfully!");

}

void Server::invite_group(User* inviter, string new_member ,string groupname)
{
    check_group(groupname);
    check_user(new_member, false);
    check_blocked(inviter, users[new_member]);
    groups[groupname]->has_premission(inviter);
    groups[groupname]->add_member(users[new_member]);
    groups[groupname]->users_num++;
    do_command("INSERT INTO user_group VALUES (\"" + new_member + "\",\"" + groupname + "\")");
    do_command("UPDATE groups SET usersNum=" + to_string(groups[groupname]->users_num) + " WHERE name==\"" + groupname +"\"");

    send_message(inviter->user_server->client_socket, "Server | You invited " + users[new_member]->name);
    broadcast_message("Server | " + inviter->name + " invited " + users[new_member]->name, inviter->username, groups[groupname]->users);
}

void Server::block_user(User* blocker, string blocked)
{
    check_user(blocked, false);
    if(blocker->blocks.find(blocked) !=  blocker->blocks.end())
        throw "You have already blocked this user.";
    blocker->blocks[blocked]=users[blocked];
    do_command("INSERT INTO blocks VALUES (\"" + blocker->username + "\",\"" + blocked + "\")" );

    send_message(blocker->user_server->client_socket, "Server | You blocked " + users[blocked]->name);
}

void Server::unblock_user(User* unblocker, string unblocked)
{
    check_user(unblocked, false);
    if(unblocker->blocks.find(unblocked) ==  unblocker->blocks.end())
        throw "This user isn't blocked.";
    unblocker->blocks[unblocked]=users[unblocked];
    do_command("DELETE FROM blocks WHERE blocker==\"" + unblocker->username + "\" & blocked==\"" + unblocked + "\")" );

    send_message(unblocker->user_server->client_socket, "Server | You unblocked " + users[unblocked]->name);
}

void Server::send_pv(User* sender, User* receiver, string message)
{
    string time=curr_time();
    try
    {
        check_blocked(sender, receiver);
        check_user(receiver->username);
        pv_id++;
        string msg="PV | " + sender->name+ " : " + message + " (" + time + ")";
        do_command("INSERT INTO pv_msg VALUES (" + to_string(pv_id) + ",\"" + sender->username + "\",\"" + receiver->username + "\",\"" + time + "\",\"" + message + "\")");
        send_message(receiver->user_server->client_socket, msg);
        // send_message(sender->user_server->client_socket, "Server | You To " + receiver->name+ " : " + message + " (" + time + ")");
    }
    catch(const char* err)
    {
        if(string(err)=="This user isn't connected.")
        {
            pv_id++;
            do_command("INSERT INTO buffer VALUES (" + to_string(pv_id) + ",0)");
            do_command("INSERT INTO pv_msg VALUES (" + to_string(pv_id) + ",\"" + sender->username + "\",\"" + receiver->username + "\",\"" + time + "\",\"" + message + "\")");
            
            // send_message(sender->user_server->client_socket, "Server | You To " + receiver->name+ " : " + message + " (" + time + ")");
        }
    }
}

void Server::send_gp(User* sender, string groupname, string message)
{
    check_group(groupname);
    gp_id++;
    string time=curr_time();
    string msg="GROUP " + groupname + " | " + sender->name + " : " + message + " (" + time + ")";
    do_command("INSERT INTO g_msg VALUES (" + to_string(gp_id) + ",\"" + groupname + "\",\"" + sender->username + "\",\"" + time + "\",\"" + message + "\")");
    broadcast_message(msg, sender->username, groups[groupname]->users);
}

void Server::send_buffer(User* user)
{
    vector<string>* pv=new vector<string>();
    vector<string>* gp=new vector<string>();
    // vector<string> all_missed_msgs;

    pv=do_command("SELECT (id) FROM buffer WHERE is_group==0");
    gp=do_command("SELECT (id) FROM buffer WHERE is_group==1");
    


    for(string &id: *pv)
    {
        vector<string>* user_pv=new vector<string>();
        user_pv=do_command("SELECT * FROM pv_msg WHERE id==" + id + " & user2==\"" + user->username + "\"");

        for(string &rec: *user_pv)
        {
            vector<string> tmp=mysplit(rec, 0);
            string msg="PV | " + tmp[1] + " : " + tmp[4] + " (" + tmp[3] + ")";
            send_message(user->user_server->client_socket, msg);
        }
        if(!user_pv->empty())
            do_command("DELETE FROM buffer WHERE id==" + id + " & is_group==0");   
    }

    for(string &id: *gp)
    {
        vector<string>* gp_names=new vector<string>();
        gp_names=do_command("SELECT (group) FROM g_msg WHERE id==" + id);
        if(groups[gp_names->at(0)]->is_member(user))
        {
            vector<string>* user_gp=new vector<string>();
            user_gp=do_command("SELECT * FROM g_msg WHERE id==" + id);
            
            for(string &rec: *user_gp)
            {
                vector<string> tmp=mysplit(rec, 0);
                string msg="GROUP " + tmp[1] + " | " + tmp[2] + " : " + tmp[4] +" (" + tmp[3] + ")";
                send_message(user->user_server->client_socket, msg);
            }
            if(!user_gp->empty())
                do_command("DELETE FROM buffer WHERE id==" + id + " & is_group==1"); 
        }
    }
}




vector<string>* Server::do_command(string cmnd)
{
    vector<string>* recs=new vector<string>();
    regex createpat("CREATE TABLE ([a-zA-Z0-9_]+) \\((.+)\\)");\
    regex insertpat("INSERT INTO ([a-zA-Z0-9_]+) VALUES \\((.+)\\)");
    regex deletepat("DELETE FROM ([a-zA-Z0-9_]+) WHERE (.+)");
    regex updatepat("UPDATE ([a-zA-Z0-9_]+) SET (.+) WHERE (.+)");
    regex selectpat("SELECT (.+) FROM ([a-zA-Z0-9_]+)");
    smatch matches;

    if(regex_search(cmnd, matches, createpat))
    {
        // string tablename=matches[1];
        Tablefile* tf=new Tablefile(cmnd);
        database[tf->name]=tf;
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
    else if(regex_search(cmnd, matches, selectpat))
    {
        string tablename=matches[2];
        recs=database[tablename]->select_records(cmnd);
    }
    else
    {
        throw "no match";
    }
    return recs;
}

void Server::get_users_from_db()
{
    vector<string>* records=new vector<string>();
    records=do_command("SELECT * FROM users");
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
        else if((user.first != sender_username) && (!user.second->user_server))
        {
            do_command("INSERT INTO buffer VALUES (" + to_string(gp_id) + ",1)");
        }

        // ATTENTION case !user.second->user_server must be handled by writing in buffer
    }

}

void Server::check_user(string username, bool connected)
{
    if (users.find(username) == users.end())
        throw "This user doesn't exist.";
    if (connected && !users[username]->user_server)
        throw "This user isn't connected.";

    // ATTENTION case !user.second->user_server must be handled by writing in buffer

}

void Server::check_group(string groupname)
{
    if (groups.find(groupname) == groups.end())
        throw "This group doesn't exist";
}

void Server::check_blocked(User* sender, User* receiver)
{
    vector<string>* records1=new vector<string>();
    records1=do_command("SELECT * FROM blocks WHERE blocker==\"" + sender->username + "\" & blocked==\"" + receiver->username + "\"");
    if(!records1->empty())
        throw "You have blocked " + receiver->username + ".";

    vector<string>* records2=new vector<string>();
    records2=do_command("SELECT * FROM blocks WHERE blocked==\"" + sender->username + "\" & blocker==\"" + receiver->username + "\"");
    if(!records2->empty())
        throw receiver->username + " has blocked you.";
}

string Server::curr_time()
{
    time_t curr_time;
	tm * curr_tm;
	char time_string[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
    strftime(time_string, 50, "%T", curr_tm);
    return time_string;
}




void Server::end_connection(int id)
{
    lock_guard<mutex> guard(clients_mtx);
    if (clients[id])
        delete clients[id];
}

void Server::delete_users()
{
    for (auto & u : clients)
    {
        delete u.second;
    }
    clients.clear();
    for (auto & u : users)
    {
        delete u.second;
    }
    users.clear();
}

void Server::close_connection()
{
    close(server_socket);
}

Server::~Server()
{
    delete database["users"];
    delete database["groups"];
    delete database["user_group"];
    delete database["pv_msg"];
    delete database["g_msg"];
    delete database["buffer"];
    delete_users();
    close_connection();
}
