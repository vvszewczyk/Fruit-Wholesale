#pragma once
#include <string>

class Fruit 
{
private:
    std::string name;
    float price;

public:
    Fruit(std::string n, float c);
    std::string getName() const;
    float getPrice() const;
    bool operator<(const Fruit& other) const;
};
