#include "../headers/Server.hpp"



// int main()
// {
//     Tablefile tf("CREATE TABLE users (username string,password string,name string)");
//     tf.insert_record("INSERT INTO users VALUES (\"Hamid\",\"5445\",\"hh\")");
//     tf.insert_record("INSERT INTO users VALUES (\"darya\",\"444\",\"dd\")");
//     tf.insert_record("INSERT INTO users VALUES (\"negar\",\"555\",\"nn\")");
//     // tf.delete_record("DELETE FROM employee WHERE income>45000");
//     // tf.update_record("UPDATE users SET leaveTime=\"15:00:00\" WHERE leaveTime==\"14:05:00\"");
//     // vector<string> * recs=tf.select_records("SELECT (name) FROM employee WHERE income>45000");
// }


Server* server = 0;

void exit_app(int sig_num);

int main()
{
    server = new Server();
    signal(SIGINT, exit_app);
    server->get_users_from_db();
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