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
    std::cout << "Podaj nowa ilosc owocu: ";
    // TO DO: dodac owoc do bazy danych
    std::cout << "Owoc " << fruitName << " zostal dodany do bazy danych\n";
    std::cin >> newAmount;

    Storage *storage = Storage::getInstance();
    storage->updateFruit(fruitName, newPrice, newAmount);
    std::cout << "Owoc " << fruitName << " zostal zaktualizowany\n";
}

void Employee::updateStorage()
{
}

void Employee::realizeDelivery()
{
}
