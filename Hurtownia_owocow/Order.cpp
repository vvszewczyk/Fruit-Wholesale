#include "Order.h"
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

Order::Order(float cost, std::string status) : totalCost(cost), status(std::move(status))
{
}

std::string Order::getorderID()
{
    return this->orderID;
}

float Order::getTotalCost()
{
    return this->totalCost;
}

std::string Order::getStatus()
{
    return this->status;
}

// generator numerow zamowienia
void Order::generateOrderID()
{
    std::string newOrderID = "HU";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1000000, 9999999);

    // Generowanie losowej liczby
    int randomNumber = distrib(gen);
    newOrderID += std::to_string(randomNumber);
    this->orderID = newOrderID;
}

// dodanie do zamowienia
void Order::addToOrder(std::string name, int amount, Storage *storage)
{
    if (storage->isInStorage(name) && storage->getAmount(name) >= amount)
    {
        float cost = amount * storage->getPrice(name);
        this->totalCost += cost;

        Fruit fruit = storage->getFruit(name);
        this->orderedFruits[fruit] += amount;
    }
    else
    {
        std::cout << "Brak podanego owocu lub niewystarczajaca ilosc owocow w magazynie" << std::endl;
        return;
    }
}

// wyswietlenie zawartosci zamowienia
void Order::showOrder() const
{
    std::cout << "Zamowienie ID: " << orderID << std::endl;
    std::cout << "Status: " << status << std::endl;
    std::cout << "Szczegoly zamowienia:" << std::endl;

    for (const auto &fruit : orderedFruits)
    {
        std::cout << "Nazwa: " << fruit.first.getName() << ", Cena: " << fruit.first.getPrice()
                  << " PLN, Ilosc: " << fruit.second << std::endl;
    }
    std::cout << "Calkowity koszt: " << totalCost << " PLN" << std::endl;
}

// przy anulowaniu zamowienia - wraca wartosci z pworotem do pliku i usuwa je z mapy
void Order::cancelOrder(Storage &storage)
{
    for (const auto &item : orderedFruits)
    {
        const std::string &fruitName = item.first.getName();
        int amountToRestore = item.second;
        int currentAmountInStorage = storage.getAmount(fruitName);
        if (currentAmountInStorage != -1)
        {
            storage.updateFruit(fruitName, item.first.getPrice(), currentAmountInStorage + amountToRestore);
        }
        else
        {
            // Opcjonalnie: obsługa sytuacji, gdy owoc nie istnieje w magazynie
        }
    }
    orderedFruits.clear();
}

// dodanie zamowienia do bazy danych z zamowieniami
void Order::addOrder(const std::string &filename, const std::string &login) const
{
    std::ofstream fileOut(filename, std::ios::app);

    if (!fileOut.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku do zapisu.\n";
        return;
    }

    std::stringstream orderStream;
    orderStream << login << "; " << orderID << "; " << status << "; " << totalCost << "; ";

    // Dodawanie informacji o owocach
    orderStream << "[";
    for (const auto &item : orderedFruits)
    {
        orderStream << item.first.getName() << ", " << item.first.getPrice() << ", " << item.second << "; ";
    }
    orderStream << "]";
    fileOut << orderStream.str() << std::endl;
    fileOut.close();
}

// trymowanie bialych znakow
std::string Order::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// wczytanie odpowiedniego zamowienia z bazy zamowien na podstawie loginu i id zamowienia
void Order::readOrder(const std::string &login, const std::string &orderId)
{
    std::ifstream file("orders.txt");

    if (!file.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string currentLogin, currentOrderId, fruitSection, fruitData, fruitName, bufor;
        float fruitPrice;
        int quantity;

        getline(ss, currentLogin, ';');
        ss.ignore(1);
        getline(ss, currentOrderId, ';');
        ss.ignore(1);

        if (currentLogin == login && currentOrderId == orderId)
        {
            this->orderID = currentOrderId;
            getline(ss, this->status, ';');
            ss.ignore(1);
            getline(ss, bufor, ';');
            this->totalCost = stof(bufor);
            ss.ignore(2);

            // Wczytaj sekcję owoców
            getline(ss, fruitSection, ']');

            std::stringstream fruitStream(fruitSection);
            while (getline(fruitStream, fruitData, ';'))
            {
                fruitData = trim(fruitData); // Usuń białe znaki z danych owocu

                std::stringstream fruitDataStream(fruitData);
                if (!fruitDataStream) // Sprawdzenie, czy stream jest w stanie dobrym
                {
                    break;
                }

                getline(fruitDataStream, fruitName, ',');
                fruitName = trim(fruitName);
                if (!fruitDataStream)
                {
                    break;
                }

                getline(fruitDataStream, bufor, ',');
                if (!fruitDataStream)
                {
                    break;
                }
                fruitPrice = stof(bufor);

                getline(fruitDataStream, bufor);
                if (!fruitDataStream)
                {
                    break;
                }
                quantity = stoi(bufor);

                this->orderedFruits[Fruit(fruitName, fruitPrice)] = quantity;
            }
            break;
        }
    }
    file.close();
}

void Order::updateState(const std::string &orderId, const std::string &newStatus)
{
    std::ifstream fileIn("orders.txt");
    std::stringstream bufor;
    std::string line;

    if (!fileIn.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku orders.txt do odczytu." << std::endl;
        return;
    }

    // Odczytuj i modyfikuj linie pliku
    while (getline(fileIn, line))
    {
        std::stringstream lineStream(line);
        std::string currentLogin, currentOrderId, currentStatus;
        getline(lineStream, currentLogin, ';');
        lineStream.ignore(1);
        getline(lineStream, currentOrderId, ';');
        currentOrderId.erase(0, currentOrderId.find_first_not_of(" \t"));
        currentOrderId.erase(currentOrderId.find_last_not_of(" \t") + 1);
        lineStream.ignore(1);
        getline(lineStream, currentStatus, ';');
        currentStatus.erase(0, currentStatus.find_first_not_of(" \t"));
        currentStatus.erase(currentStatus.find_last_not_of(" \t") + 1);

        if (currentOrderId == orderId)
        {
            // Znaleziono odpowiednie zamówienie, zmień jego status
            std::string resztaLinii;
            getline(lineStream, resztaLinii);
            bufor << currentLogin << "; " << currentOrderId << "; " << newStatus << "; " << resztaLinii << std::endl;
        }
        else
        {
            bufor << line << std::endl;
        }
    }
    fileIn.close();

    // Zapisz zmodyfikowane dane z powrotem do pliku
    std::ofstream fileOut("orders.txt", std::ofstream::out | std::ofstream::trunc);
    if (!fileOut.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku orders.txt do zapisu." << std::endl;
        return;
    }
    fileOut << bufor.str();
    fileOut.close();
}

// wyswietlenie wszystkich zamowien z pliku
void Order::showAllOrders(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku do odczytu." << std::endl;
        return;
    }
    std::cout << "\n--- Wszystkie zamówienia ---\n";
    std::string line;
    while (getline(file, line))
    {
        if ()
            std::cout << line << std::endl;
    }
    file.close();
}

// sprawdzenie czy zamowienie o danym id istnieje
bool Order::isOrderExists(const std::string &filename, const std::string &orderId)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Nie mozna otworzyc pliku do odczytu." << std::endl;
        return false;
    }
    std::string line;
    while (getline(file, line))
    {
        // Format: login; orderID; status; totalCost; [szczegóły]
        std::stringstream ss(line);
        std::string currentLogin, currentOrderId;
        getline(ss, currentLogin, ';');
        ss.ignore(1);
        getline(ss, currentOrderId, ';');

        // Usuń białe znaki z loginu i id zamówienia
        currentOrderId.erase(0, currentOrderId.find_first_not_of(" \t"));
        currentOrderId.erase(currentOrderId.find_last_not_of(" \t") + 1);

        if (currentOrderId == orderId)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
