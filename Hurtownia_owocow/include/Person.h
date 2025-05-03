#pragma once
#include <string>

class Person 
{
    std::string login;
    std::string password;
public:
    Person(std::string l, std::string h);
    
    virtual std::string getLogin();
    virtual std::string getPasswd();
    virtual void changeLogin(std::string l);
    virtual void changePasswd(std::string h);
};