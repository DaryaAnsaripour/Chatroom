#include "../headers/Group.hpp"

Group::Group(string name, string description)
: name(name), description(description), users_num(0)
{}


void Group::has_premission(User* user)
{
    if(users.find(user->username)!=users.end())
        return;
    throw "You cannot add member to this group.";
}

void Group::add_member(User* user)
{
    if(users.find(user->username)==users.end())
    {
        users[user->username]=user;
        return;
    }
    throw "This user is already a member of group.";
}

bool Group::is_member(User* user)
{
    if(users.find(user->username)!=users.end())
        return true;
    return false;
}

