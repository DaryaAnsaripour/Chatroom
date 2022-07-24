#include "../headers/Tablefile.hpp"

// make a Tablefile obj and pass CREATE command
Tablefile::Tablefile(string cmnd)
{
    lock_guard<mutex> guard(mtx);
    regex createpat("CREATE TABLE ([a-zA-Z0-9_]+) \\((.+)\\)");
    smatch matches;
    if(regex_search(cmnd, matches, createpat))
    {   
        name=matches[1];
        addr="tables/"+name+".txt";
        string arguments=matches[2];
        file.open(addr, ios::app);
        vector<string> temp;
        temp=mysplit(arguments, 1);
        for(int i=0; i<temp.size(); i++)
        {
            if(i%2==0)
                argnames.push_back(temp[i]);
            else
            {
                args[temp[i-1]]=temp[i];
                file<<temp[i-1]<<":"<<temp[i]<<" ";
            }
        }
        file<<"\n";
        file.close();
    }
}

void Tablefile::insert_record(string cmnd)
{
    lock_guard<mutex> guard(mtx);
    regex insertpat("INSERT INTO ([a-zA-Z0-9_]+) VALUES \\((.+)\\)");
    smatch matches;

    if(regex_search(cmnd, matches, insertpat))
    {
        string vals=matches[2];
        file.open(addr, ios::app);
        // file.seekp(0,ios::end);
        vector<string> temp=mysplit(vals, 0);

        for(int i=0; i<argnames.size(); i++)
        {
            if(args[argnames[i]]=="string")
                file<<temp[i].substr(1,temp[i].length()-2)<<",";
            else if(args[argnames[i]]=="timestamp")
                file<<temp[i].substr(1,temp[i].length()-2)<<",";
            else
                file<<temp[i]<<",";
        }
        file<<"\n";
        file.close();
    }
}

void Tablefile::delete_record(string cmnd)
{
    lock_guard<mutex> guard(mtx);
    regex deletepat("^DELETE FROM ([a-zA-Z0-9_]+) WHERE (.+)$");
    smatch matches;
    file.open(addr, ios::in);

    if(regex_search(cmnd, matches, deletepat))
    {
        string condition=matches[2];
        string line;
        fstream tempfile;
        tempfile.open("tables/temp.txt", ios::out);

        // to get titles
        getline(file, line);
        tempfile<<line<<endl;

        // to get valid records
        while(getline(file, line))
        {
            if(check_condition(line, condition))
            {
                line.replace(line.find(line), line.length(), "");
            }
            if(line!="")
                tempfile<<line<<endl;
        }

        // to remove firstfile and rename tmpfile
        tempfile.close();
        file.close();
        string tempaddr=addr;
        const char * ad=tempaddr.c_str();
        remove(ad);
        rename("tables/temp.txt", ad);

    }
}

void Tablefile::update_record(string cmnd)
{
    lock_guard<mutex> guard(mtx);
    regex updatepat("^UPDATE ([a-zA-Z0-9_]+) SET (.+) WHERE (.+)$");
    smatch matches;
    file.open(addr, ios::in);

    if(regex_search(cmnd, matches, updatepat))
    {
        string condition=matches[3];
        string updates=matches[2];
        vector<string> newvals=mysplit(updates, 0);
        string line;
        fstream tempfile;
        tempfile.open("tables/temp.txt", ios::out);

        // to get titles
        getline(file, line);
        tempfile<<line<<endl;

        // to get valid records
        while(getline(file, line))
        {
            string newline=line;
            if(check_condition(line, condition))
            {
                vector<string> temp=mysplit(line, 0);
                for(string assignment: newvals)
                {
                    regex assignpat("([^=]+)=([^=]+)");
                    smatch assignmatches;
                    if(regex_search(assignment, assignmatches, assignpat))
                    {
                        string title=assignmatches[1]; 
                        string newval=assignmatches[2];
                        int index;
                        for(int i=0; i<argnames.size(); i++)
                            if(argnames[i]==title)
                            {
                                index=i;break;
                            }
                        
                        if(args[argnames[index]]=="string" || args[argnames[index]]=="timestamp")
                            temp[index]=newval.substr(1, newval.length()-2);
                        else
                            temp[index]=newval;   
                    }
                } 
                newline=myjoin(temp);
            }
            tempfile<<newline<<endl;
        } 

        // to remove firstfile and rename tmpfile
        tempfile.close();
        file.close();
        string tempaddr=addr;
        const char * ad=tempaddr.c_str();
        remove(ad);
        rename("tables/temp.txt", ad);
    }
}

vector<string>* Tablefile::select_records(string cmnd)
{
    lock_guard<mutex> guard(mtx);
    regex selectpat1("^SELECT (.+) FROM ([a-zA-Z0-9_]+) WHERE (.+)$");
    regex selectpat2("^SELECT (.+) FROM ([a-zA-Z0-9_]+)$");
    smatch matches;
    vector<string>* validrecords;
    file.open(addr, ios::in);

    if(regex_search(cmnd, matches, selectpat1))
    {
        string condition=matches[3];
        string line;
        string titles=matches[1];

        if(titles=="*")
        {
            getline(file, line);

            while(getline(file, line))
            {
                if(check_condition(line, condition))
                {
                    // for printing
                    // cout<<line<<endl;

                    // for returning
                    validrecords->push_back(line);
                }
            }
        }
        else
        {
            vector<string> selectedtitles=mysplit(titles.substr(1, titles.length()-2), 0);
            vector<int> indexes;
            for(string title: selectedtitles)
                for(int i=0; i<argnames.size(); i++)
                    if(argnames[i]==title)
                    {
                        indexes.push_back(i);
                        break;
                    }

            getline(file, line);

            while(getline(file, line))
            {
                if(check_condition(line, condition))
                {
                    vector<string> record=mysplit(line, 0);
                    string tmp="";

                    // for printing
                    // for(int i=0; i<indexes.size(); i++)
                    //     cout<<record[indexes[i]]<<",";
                    // cout<<endl;

                    // for returning
                    for(int i=0; i<indexes.size(); i++)
                    {
                        tmp+=record[indexes[i]];
                        tmp+=",";
                    }
                    validrecords->push_back(tmp.substr(0, tmp.length()-1));
                }
            }
        } 
    }
    else if(regex_search(cmnd, matches, selectpat2))
    {
        string line;
        string titles=matches[1];

        if(titles=="*")
        {
            getline(file, line);

            while(getline(file, line))
            {
                // for printing
                // cout<<line<<endl;

                // for returning
                validrecords->push_back(line);
            }
        }
        else
        {
            vector<string> selectedtitles=mysplit(titles.substr(1, titles.length()-2), 0);
            vector<int> indexes;
            for(string title: selectedtitles)
                for(int i=0; i<argnames.size(); i++)
                    if(argnames[i]==title)
                    {
                        indexes.push_back(i);
                        break;
                    }

            getline(file, line);

            while(getline(file, line))
            {
                vector<string> record=mysplit(line, 0);
                string tmp="";

                // for printing
                // for(int i=0; i<indexes.size(); i++)
                //     cout<<record[indexes[i]]<<",";
                // cout<<endl;

                // for returning
                for(int i=0; i<indexes.size(); i++)
                {
                    tmp+=record[indexes[i]];
                    tmp+=",";
                }
                validrecords->push_back(tmp.substr(0, tmp.length()-1));
            }
        }
    }
    return validrecords;
}

bool Tablefile::check_condition2(string arg, string type, string oprtr, string value)
{
    if(type=="string")
    {
        if(oprtr=="==")
            return arg==value.substr(1,value.length()-2);
        else if(oprtr=="<")
            return arg<value.substr(1,value.length()-2);
        else
            return arg>value.substr(1,value.length()-2);
    }
    else if(type=="timestamp")
    {
        timestamp t1(arg);
        timestamp t2(value.substr(1,value.length()-2));
        if(oprtr=="==")
            return t1==t2;
        else if(oprtr=="<")
            return t1<t2;
        else
            return t1>t2;
    }
    else
    {
        int left=stoi(arg);
        int right=stoi(value);
        if(oprtr=="==")
            return left==right;
        else if(oprtr=="<")
            return left<right;
        else
            return left>right;
    }
}

bool Tablefile::check_condition(string line, string condition)
{
    regex pat1("^([^<>=&\\|]+)([<>=]+)([^<>=&\\|]+)$");
    regex pat2("^([^<>=&\\|]+)([<>=]+)([^<>=&\\|]+) \\| ([^<>=&\\|]+)([<>=]+)([^<>=&\\|]+)$");
    regex pat3("^([^<>=&\\|]+)([<>=]+)([^<>=&\\|]+) & ([^<>=&\\|]+)([<>=]+)([^<>=&\\|]+)$");
    smatch matches;
    
    if(regex_search(condition, matches, pat1))
    {
        string arg=matches[1];
        string oprtr=matches[2];
        string value=matches[3];
        string type=args[arg];
        int index;
        for(int i=0; i<argnames.size(); i++)
            if(argnames[i]==arg)
            {
                index=i;break;
            }
        
        vector<string> temp=mysplit(line, 0);
        return check_condition2(temp[index], type, oprtr, value);
    }
    else if(regex_search(condition, matches, pat2))
    {
        string arg1=matches[1], arg2=matches[4];
        string oprtr1=matches[2], oprtr2=matches[5];
        string value1=matches[3], value2=matches[6];
        string type1=args[arg1], type2=args[arg2];
        int index1, index2;
        for(int i=0; i<argnames.size(); i++)
        {    
            if(argnames[i]==arg1)
                index1=i;
            if(argnames[i]==arg2)
                index2=i;
        }

        vector<string> temp=mysplit(line, 0);
        return check_condition2(temp[index1], type1, oprtr1, value1) || check_condition2(temp[index2], type2, oprtr2, value2);
    }
    else
    {
        string arg1=matches[1], arg2=matches[4];
        string oprtr1=matches[2], oprtr2=matches[5];
        string value1=matches[3], value2=matches[6];
        string type1=args[arg1], type2=args[arg2];
        int index1, index2;
        for(int i=0; i<argnames.size(); i++)
        {    
            if(argnames[i]==arg1)
                index1=i;
            if(argnames[i]==arg2)
                index2=i;
        }

        vector<string> temp=mysplit(line, 0);
        return check_condition2(temp[index1], type1, oprtr1, value1) && check_condition2(temp[index2], type2, oprtr2, value2);
    }


}


vector<string> mysplit(string s, int f)
{
    if(f)
    {
        string temp = "";
        vector<string>v;
        for(int i=0; i<s.size(); i++)
        {
            if((s[i] != ' ') && (s[i] != ','))
                temp += s[i];
            else
            {
                v.push_back(temp);
                temp = "";
            }
        }
        v.push_back(temp);
        return v;
    }
    else
    {
        string temp = "";
        vector<string>v;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i] != ',')
                temp += s[i];
            else
            {
                v.push_back(temp);
                temp = "";
            }
        }
        v.push_back(temp);
        return v;

    }
}

string myjoin(vector<string> v)
{
    string s = "";
    for(int i=0; i<v.size(); i++)
    {
        s+=v[i];
        s+=",";
    }
    return s;
}