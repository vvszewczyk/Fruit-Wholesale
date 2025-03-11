#include "Supplier.h"
#include "Storage.h"
#include <fstream>
#include <iostream>
#include <sstream>

Supplier::Supplier(std::string l, std::string h) : Person(std::move(l), std::move(h))
{
}

// Pomocnicza funkcja usuwaj�ca bia�e znaki
static std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

void Supplier::registerDelivery()
{
    std::string deliveryID;
    std::cout << "Podaj ID dostawy: ";
    std::cin >> deliveryID;

    // Opcjonalnie: sprawd�, czy dostawa o tym ID ju� istnieje
    std::ifstream infile("deliveries.txt");
    if (infile.is_open())
    {
        std::string line;
        while (getline(infile, line))
        {
            std::stringstream ss(line);
            std::string existingSupplier, existingID;
            getline(ss, existingSupplier, ';');
            ss.ignore(1);
            getline(ss, existingID, ';');
            existingID = trim(existingID);
            if (existingID == deliveryID)
            {
                std::cout << "Dostawa o ID " << deliveryID << " ju� istnieje. Nie mo�na jej ponownie zarejestrowa�."
                          << std::endl;
                infile.close();
                return;
            }
        }
        infile.close();
    }

    int numFruits;
    std::cout << "Ile rodzaj�w owoc�w znajduje si� w dostawie? ";
    std::cin >> numFruits;

    std::stringstream deliveryStream;
    // Zapisujemy login dostawcy oraz ID dostawy
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
        std::cout << "Ilo��: ";
        std::cin >> amount;

        // Zapisujemy dane owocu w formacie: "fruitName, price, amount;"
        deliveryStream << fruitName << ", " << price << ", " << amount << "; ";
    }

    // Na starcie dostawa nie jest zrealizowana � wi�c nie dodajemy flagi REALIZED

    // Zapis do pliku deliveries.txt (dopisywanie do istniej�cego pliku)
    std::ofstream outfile("deliveries.txt", std::ios::app);
    if (!outfile.is_open())
    {
        std::cerr << "Nie mo�na otworzy� pliku deliveries.txt do zapisu." << std::endl;
        return;
    }
    outfile << deliveryStream.str() << std::endl;
    outfile.close();

    std::cout << "\nDostawa o ID " << deliveryID << " zosta�a zarejestrowana." << std::endl;
}

void Supplier::showDeliveryHistory()
{
    std::ifstream file("deliveries.txt");
    if (!file.is_open())
    {
        std::cerr << "Nie mo�na otworzy� pliku deliveries.txt do odczytu." << std::endl;
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
