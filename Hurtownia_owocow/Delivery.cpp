#include "Delivery.h"
#include <string>
#include <map>

Delivery::Delivery(const std::string& id, const std::map<Fruit, int>& fruits = {}) : id(id), deliveredFruits(fruits) {}

std::string Delivery::getId() const
{
	return this->id;
}

int Delivery::getAmount(const Fruit& fruit) const
{
    auto it = deliveredFruits.find(fruit);
    if (it != deliveredFruits.end())
    {
        return it->second;
    }
    else
    {
        return 0;
    }
}
