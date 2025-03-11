#include "Supplier.h"
#include "Storage.h"
#include <fstream>
#include <iostream>
#include <sstream>

Supplier::Supplier(std::string l, std::string h) : Person(std::move(l), std::move(h))
{
}

void Supplier::registerDelivery()
{
    std::string deliveryID;
    std::cout << "Podaj identyfikator dostawy: ";
    std::cin >> deliveryID;

    int numFruits;
    std::cout << "Ile rodzajów owoców znajduje siê w dostawie? ";
    std::cin >> numFruits;

    Storage *storage = Storage::getInstance();
    std::stringstream deliveryStream;
    deliveryStream << getLogin() << "; " << deliveryID << "; ";

    for (int i = 0; i < numFruits; ++i)
    {
        std::string fruitName;
        float price;
        int amount;
        std::cout << "\nDla owocu " << i + 1 << ":\n";
        std::cout << "Nazwa: ";
        std::cin >> fruitName;
        std::cout << "Cena: ";
        std::cin >> price;
        std::cout << "Iloœæ: ";
        std::cin >> amount;

        if (storage->isInStorage(fruitName))
        {
            int currentAmount = storage->getAmount(fruitName);
            storage->updateFruit(fruitName, price, currentAmount + amount);
        }
        else
        {
            storage->addFruit(fruitName, price, amount);
        }

        deliveryStream << fruitName << ", " << price << ", " << amount << "; ";
    }

    std::ofstream outFile("deliveries.txt", std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Nie mo¿na otworzyæ pliku deliveries.txt do zapisu." << std::endl;
        return;
    }
    outFile << deliveryStream.str() << std::endl;
    outFile.close();

    std::cout << "\nDostawa " << deliveryID << " zosta³a zarejestrowana.\n";
}

void Supplier::showDeliveryHistory()
{
    std::ifstream file("deliveries.txt");
    if (!file.is_open())
    {
        std::cerr << "Nie mo¿na otworzyæ pliku deliveries.txt do odczytu." << std::endl;
        return;
    }
    std::cout << "\n--- Historia dostaw dla: " << getLogin() << " ---\n";
    std::string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string supplierLogin;
        getline(ss, supplierLogin, ';');

        supplierLogin.erase(0, supplierLogin.find_first_not_of(" \t"));
        supplierLogin.erase(supplierLogin.find_last_not_of(" \t") + 1);

        if (supplierLogin == getLogin())
        {
            std::cout << line << std::endl;
        }
    }
    file.close();
}
