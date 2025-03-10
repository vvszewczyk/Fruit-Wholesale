#pragma once
#include "Person.h"

class Employee : public Person
{
  public:
    Employee(std::string l, std::string h);
    void considerReturn();
    void realizeOrder();
    void updateFruit();
    void updateStorage();
    void realizeDelivery(); // TO DO
};
