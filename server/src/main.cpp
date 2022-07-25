#include "../headers/Server.hpp"

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

    // Tablefile tf("CREATE TABLE employee (name string,leaveTime timestamp,income int)");
    // tf.insert_record("INSERT INTO employee VALUES (\"Hamid\",\"17:05:00\",45000)");
    // tf.insert_record("INSERT INTO employee VALUES (\"darya\",\"14:05:00\",200000)");
    // tf.insert_record("INSERT INTO employee VALUES (\"negar\",\"15:05:00\",350000)");
    // // tf.delete_record("DELETE FROM employee WHERE income>45000");
    // tf.update_record("UPDATE employee SET leaveTime=\"15:00:00\" WHERE leaveTime==\"14:05:00\"");
    // vector<string> * recs=tf.select_records("SELECT name FROM employee WHERE income>45000");
    // for(int i=0; i<recs->size(); i++)
    //     cout<<recs->at(i)<<endl;
}

void exit_app(int sig_num)
{
    if (server)
        delete server;
    cout<<"...bye..."<<endl;
    exit(sig_num);
}