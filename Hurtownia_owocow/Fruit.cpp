#include "Fruit.h"

Fruit::Fruit(std::string n, float c) : name(std::move(n)), price(c) {}

std::string Fruit::getName() const 
{
        return this->name;
}

float Fruit::getPrice() const 
{
       return this->price;
}

bool Fruit::operator<(const Fruit& other) const 
{
        if (name == other.name)
        {
            return price < other.price;
        }
        else
        {
            return name < other.name;
        }
}
