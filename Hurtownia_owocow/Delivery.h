#pragma once
#include "Fruit.h"
#include <map>

class Delivery
{
	std::string id;
	std::map<Fruit, int> deliveredFruits;
public:
	Delivery(const std::string& id, const std::map<Fruit, int>& fruits);
	std::string getId() const;
	int getAmount(const Fruit& fruit) const;
};