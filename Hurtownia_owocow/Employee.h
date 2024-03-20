#pragma once
#include "Person.h"

class Employee : public Person
{
public:
    Employee(std::string l, std::string h);
    void considerReturn(); // TO DO
    void realizeOrder(); // TO DO
    void updateFruit(); // TO DO
    void updateStorage(); // TO DO
    void realizeDelivery(); // TO DO
};
