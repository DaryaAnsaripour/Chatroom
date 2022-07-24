#ifndef TABLEFILE_H
#define TABLEFILE_H

#include "../headers/Timestamp.hpp"

class Tablefile
{
public:
    map<string, string> args;
    vector<string> argnames;
    fstream file;
    string addr;
    string name;
    mutex mtx;

    Tablefile(string cmnd);
    void insert_record(string cmnd);
    void delete_record(string cmnd);
    void update_record(string cmnd);
    vector<string>* select_records(string cmnd);
    
    bool check_condition(string line, string condition);
    bool check_condition2(string arg, string type, string oprtr, string value);
};

vector<string> mysplit(string s, int f);
string myjoin(vector<string> v);

#endif