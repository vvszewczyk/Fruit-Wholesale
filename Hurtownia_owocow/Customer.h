#pragma once
#include "Person.h"
#include "Order.h"
#include <string>
#include <vector>

class Customer : public Person
{
public:
    Customer(std::string l, std::string h);
};