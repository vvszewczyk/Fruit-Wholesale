#pragma once
#include "Person.h"

class Supplier : public Person
{
  public:
    Supplier(std::string l, std::string h);
    void registerDelivery();
    void showDeliveryHistory();
};
