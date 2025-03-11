#include "Employee.h"
#include "Order.h"
#include "Storage.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Employee::Employee(std::string l, std::string h) : Person(std::move(l), std::move(h))
{
}

void Employee::considerReturn()
{
    std::string orderID;
    std::cout << "Podaj numer zamowienia do rozpatrzenia zwrotu: ";
    std::cin >> orderID;
    Storage *storage = Storage::getInstance();

    if (!Order::isOrderExists("orders.txt", orderID))
    {
        std::cout << "Zamowienie o ID: " << orderID << " nie istnieje.";
    }

    Order order;
    if (!(order.getStatus() == "Zwrot"))
    {
        std::cout << "Zamowienie o ID: " << orderID << " nie jest przeznaczone do zwrotu.\n";
        return;
    }

    order.updateState(orderID, "Zwrot");
    std::cout << "Zamowienie " << orderID << " zosta³o oznaczone jako zwrot.\n";
}

void Employee::realizeOrder()
{
    std::string orderID;
    std::cout << "Podaj numer zamowienia do realizacji: ";
    std::cin >> orderID;

    if (!Order::isOrderExists("orders.txt", orderID))
    {
        std::cout << "Zamowienie o ID: " << orderID << " nie istnieje.";
        return;
    }

    Order order;
    if (order.getStatus() == "Zrealizowane")
    {
        std::cout << "Zamowienie o ID: " << orderID << " zostalo ju¿ zrealizowane.\n";
        return;
    }
    else if (order.getStatus() == "Zwrot")
    {
        std::cout << "Zamowienie o ID: " << orderID << " zostalo zwrócone.\n";
        return;
    }
    else if (order.getStatus() == "Anulowane")
    {
        std::cout << "Zamowienie o ID: " << orderID << " zostalo anulowane.\n";
        return;
    }

    order.updateState(orderID, "Zrealizowane");
    std::cout << "Zamowienie " << orderID << " zostalo zrealizowane\n";
}

void Employee::updateFruit()
{
    std::string fruitName;
    float newPrice;
    int newAmount;
    std::cout << "Podaj nazwe owocu do aktualizcji: ";
    std::cin >> fruitName;
    std::cout << "Podaj nowa cene owocu: ";
    std::cin >> newPrice;
    std::cout << "Podaj nowa ilosc owocow: ";
    std::cin >> newAmount;

    Storage *storage = Storage::getInstance();
    storage->updateFruit(fruitName, newPrice, newAmount);
    std::cout << "Owoc " << fruitName << " zostal zaktualizowany\n";
}

void Employee::updateStorage()
{
    std::cout << "Wybierz opcje:\n1 - dodaj owoc\n2 - usun owoc\n3 - aktualizuj owoc\n";
    int option;
    std::cin >> option;
    switch (option)
    {
    case 1: {
        std::string name;
        float price;
        int amount;
        std::cout << "Podaj nazwe owocu: ";
        std::cin >> name;
        std::cout << "Podaj cene owocu: ";
        std::cin >> price;
        std::cout << "Podaj ilosc owocow: ";
        std::cin >> amount;
        Storage *storage = Storage::getInstance();
        storage->addFruit(name, price, amount);
        std::cout << "Owoc " << name << " zostal dodany do magazynuh\n";
        break;
    }
    case 2: {
        std::string name;
        std::cout << "Podaj nazwe owocu do usuniecia: ";
        std::cin >> name;
        Storage *storage = Storage::getInstance();
        storage->deleteFruit(name);
        std::cout << "Owoc " << name << " zostal usuniety z magazynu\n";
        break;
    }
    case 3: {
        std::string name;
        float price;
        int amount;
        std::cout << "Podaj nazwe owocu do aktualizacji: ";
        std::cin >> name;
        std::cout << "Podaj nowa cene owocu: ";
        std::cin >> price;
        std::cout << "Podaj nowa ilosc owocow: ";
        std::cin >> amount;
        Storage *storage = Storage::getInstance();
        storage->updateFruit(name, price, amount);
        std::cout << "Owoc " << name << " zostal zaktualizowany\n";
        break;
    }
    default: {
        std::cout << "Niepoprawna opcja\n";
        break;
    }
    }
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

void Employee::realizeDelivery()
{
    std::string deliveryID;
    std::cout << "Podaj ID dostawy: ";
    std::cin >> deliveryID;

    // Wczytujemy wszystkie linie z deliveries.txt
    std::ifstream infile("deliveries.txt");
    if (!infile.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku deliveries.txt" << std::endl;
        return;
    }
    std::vector<std::string> deliveries;
    std::string line;
    bool found = false;
    bool alreadyRealized = false;
    int targetIndex = -1;
    for (int i = 0; getline(infile, line); i++)
    {
        deliveries.push_back(line);
        std::stringstream ss(line);
        std::string supplierLogin, dID, fruitData;
        getline(ss, supplierLogin, ';');
        ss.ignore(1);
        getline(ss, dID, ';');
        dID = trim(dID);

        if (dID == deliveryID)
        {
            found = true;
            if (line.find("Zrealizowana") != std::string::npos)
            {
                alreadyRealized = true;
            }
            targetIndex = i;
        }
    }
    infile.close();

    if (!found)
    {
        std::cout << "Dostawa o ID: " << deliveryID << " nie istnieje." << std::endl;
        return;
    }
    if (alreadyRealized)
    {
        std::cout << "Dostawa o ID: " << deliveryID << " zostala juz zrealizowana." << std::endl;
        return;
    }

    // supplierLogin; deliveryID; fruit1, price, amount; fruit2, price, amount; ... ; (flaga)
    std::string deliveryLine = deliveries[targetIndex];
    std::stringstream ss(deliveryLine);
    std::string supplierLogin, dID;
    getline(ss, supplierLogin, ';');
    ss.ignore(1);
    getline(ss, dID, ';');

    std::vector<std::string> fruitTokens;
    std::string token;
    while (getline(ss, token, ';'))
    {
        token = trim(token);
        if (!token.empty())
            fruitTokens.push_back(token);
    }
    // Jeœli ostatni token to "Zrealizowana" (lub zawiera tê frazê), usuwamy go z listy
    if (!fruitTokens.empty() && fruitTokens.back().find("Zrealizowana") != std::string::npos)
    {
        fruitTokens.pop_back();
    }

    Storage *storage = Storage::getInstance();

    // "fruitName, price, amount"
    for (auto &ft : fruitTokens)
    {
        std::stringstream fruitSS(ft);
        std::string fruitName, priceStr, amountStr;
        getline(fruitSS, fruitName, ',');
        getline(fruitSS, priceStr, ',');
        getline(fruitSS, amountStr, ',');
        fruitName = trim(fruitName);
        float newPrice = std::stof(trim(priceStr));
        int amount = std::stoi(trim(amountStr));

        if (storage->isInStorage(fruitName))
        {
            float currentPrice = storage->getPrice(fruitName);
            int currentAmount = storage->getAmount(fruitName);
            if (currentPrice != newPrice)
            {
                std::cout << "Cena owocu " << fruitName << " rozni siê (magazyn: " << currentPrice
                          << ", dostawa: " << newPrice << "). Podaj nowa cene: ";
                float updatedPrice;
                std::cin >> updatedPrice;
                newPrice = updatedPrice;
            }
            storage->updateFruit(fruitName, newPrice, currentAmount + amount);
        }
        else
        {
            storage->addFruit(fruitName, newPrice, amount);
        }
    }

    deliveries[targetIndex] += "Zrealizowana";

    std::ofstream outfile("deliveries.txt", std::ios::trunc);
    for (const auto &line : deliveries)
    {
        outfile << line << std::endl;
    }
    outfile.close();

    std::cout << "Dostawa zosta³a zrealizowana i magazyn zaktualizowany." << std::endl;
}
