#include "../headers/Group.hpp"

Group::Group(string name, string description, int users_num)
: name(name), description(description), users_num(users_num)
{}


void Group::has_premission(User* user)
{
    if(users.find(user->username)==users.end())
        throw "You are not a member of this group.";
    else if (banned_users.find(user->username)!=banned_users.end())
        throw "You are banned.";
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

void Group::remove_member(User* remover, User* member)
{
    if(remover->username!=admin->username)
        throw "Only admin can remove users.";
    if(users.find(member->username)==users.end())
        throw "This user is not a member of this group.";
    users.erase(member->username);
}

void Group::left(User* member)
{
    if(users.find(member->username)==users.end())
        throw "You are not a member of this group.";
    users.erase(member->username);
}

void Group::ban_user(User* banner, User* banned)
{
    if(banner->username!=admin->username)
        throw "Only admin can ban users.";
    else if(banned_users.find(banned->username)!=banned_users.end())
        throw "This user is already banned.";
    banned_users[banned->username]=banned;
}

void Group::unban_user(User* unbanner, User* unbanned)
{
    if(unbanner->username!=admin->username)
        throw "Only admin can unban users.";
    else if(banned_users.find(unbanned->username)==banned_users.end())
        throw "This user isn't banned.";
    banned_users.erase(unbanned->username);
}

bool Group::is_member(User* user)
{
    if(users.find(user->username)!=users.end())
        return true;
    return false;
}

