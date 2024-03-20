#include "Person.h"

Person::Person(std::string l, std::string h) : login(l), password(h) {}

std::string Person::getLogin()
{
    return login;
}

std::string Person::getPasswd()
{
    return password;
}

void Person::changeLogin(std::string l)
{
    login = l;
}

void Person::changePasswd(std::string h)
{
    password = h;
}