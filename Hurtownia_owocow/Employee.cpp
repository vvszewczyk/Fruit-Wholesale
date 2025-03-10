#include "Employee.h"
#include "Order.h"
#include <iostream>

Employee::Employee(std::string l, std::string h) : Person(std::move(l), std::move(h))
{
}

void Employee::considerReturn()
{
    std::string orderID;
    std::cout << "Podaj numer zamowienia do rozpatrzenia zwrotu: ";
    std::cin >> orderID;
    Order order;
    order.updateState(getLogin(), orderID, "Zwrot");
    std::cout << "Zamowienie " << orderID << " zosta³o oznaczone jako zwrot\n";
}

void Employee::realizeOrder()
{
    std::string orderID;
    std::cout << "Podaj numer zamowienia do realizacji: ";
    std::cin >> orderID;
    Order order;
    order.updateState(getLogin(), orderID, "Zrealizowane");
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
    std::cout << "Owoc " << fruitName << " zostal dodany do bazy danych\n";
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

void Employee::realizeDelivery()
{
}
