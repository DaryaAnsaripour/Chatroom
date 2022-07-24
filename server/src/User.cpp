#include "../headers/User.hpp"

User::User(string username, string password, string name, Userserver* user_server)
: user_server(user_server), username(username), password(password), name(name)
{}