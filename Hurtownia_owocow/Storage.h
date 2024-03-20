#pragma once
#include <map>
#include "Fruit.h"

class Storage 
{
private:
    std::map<Fruit, int> fruits;
    static Storage* storage;
    Storage();
public:
    // Usuwanie możliwości kopiowania i przypisywania
    Storage(Storage const&) = delete;
    void operator=(Storage const&) = delete;

    static Storage* getInstance();
    float getPrice(const std::string& name) const;
    int getAmount(const std::string& name) const;
    Fruit getFruit(const std::string& name) const;
    bool isInStorage(const std::string& name) const;

    void addFruit(std::string name, float price, int amount);
    void deleteFruit(const std::string& name);
    void updateFruit(const std::string& name, float newPrice, int newAmount);

    void readStorage();
    void showStorage();
};
