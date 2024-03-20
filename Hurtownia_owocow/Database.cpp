#include "Database.h"
#include <iostream>
#include <fstream>
#include <sstream>

Database::Database()
{
    // TO DO
    // Push controll klients
};

Database* Database::getInstance()
{
    if (database == nullptr)
    {
        database = new Database();
    }
    return database;
}

bool Database::isCustomerExists(std::string p, std::string c)
{
    for (auto& e : customers)
    {
        if (e.getLogin() == p && e.getPasswd() == c)
        {
            return true;
        }
    }
    return false;
};

bool Database::isEmployeeExists(std::string p, std::string c) 
{
    for (auto& e : employees)
    {
        if (e.getLogin() == p && e.getPasswd() == c)
        {
            return true;
        }
    }
    return false;
};

bool Database::isSupplierExists(std::string p, std::string c) 
{
    for (auto& e : suppliers)
    {
        if (e.getLogin() == p && e.getPasswd() == c)
        {
            return true;
        }
    }
    return false;
};

Customer Database::loginCustomer(std::string p, std::string c) 
{
    for (auto& e : customers)
    {
        if (e.getLogin() == p && e.getPasswd() == c)
        {
            return e;
        }
    }
    throw std::runtime_error("Customer not found");
};

Employee Database::loginEmployee(std::string p, std::string c)
{
    for (auto& e : employees)
    {
        if (e.getLogin() == p && e.getPasswd() == c)
        {
            return e;
        }
    }
    throw std::runtime_error("Employee not found");
};

Supplier Database::loginSupplier(std::string p, std::string c) 
{
    for (auto& e : suppliers)
    {
        if (e.getLogin() == p && e.getPasswd() == c)
        {
            return e;
        }
    }
    throw std::runtime_error("Supplier not found");
}

void Database::readFolks()
{
    std::fstream file("database.txt", std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Błąd przy otwieraniu pliku" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string login, password, bufor;
        char type;

        std::getline(ss, bufor, ',');
        type = bufor[0];
        ss.ignore();
        std::getline(ss, login, ',');
        ss.ignore();
        std::getline(ss, password, ';');

        switch (type) 
        {
            case 'k':
            {
                customers.push_back(Customer(login, password));
                break;
            }
            case 'p':
            {
                employees.push_back(Employee(login, password));
                break;
            }
            case 'd':
            {
                suppliers.push_back(Supplier(login, password));
                break;
            }
            default:
            {
                std::cerr << "Nieznany typ użytkownika: " << type << std::endl;
                break;
            }
        }
    }
    // Plik zostanie zamknięty automatycznie przez destruktor std::fstream
}

void Database::showFolks()
{
    std::cout << "Klienci:\n";
    for (Customer& k : customers) 
    {
        std::cout << "Login: " << k.getLogin() << ", Haslo: " << k.getPasswd() << "\n";
    }

    std::cout << "\nPracownicy:\n";
    for (Employee& p : employees) 
    {
        std::cout << "Login: " << p.getLogin() << ", Haslo: " << p.getPasswd() << "\n";
    }

    std::cout << "\nDostawcy:\n";
    for (Supplier& d : suppliers) 
    {
        std::cout << "Login: " << d.getLogin() << ", Haslo: " << d.getPasswd() << "\n";
    }
};

void Database::addCustomer(std::string login, std::string passwd)
{
    if (login.empty() || passwd.empty())
    {
        std::cerr << "Login i hasło nie mogą być puste." << std::endl;
        return;
    }

    std::ofstream file("database.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return;
    }

    std::stringstream customerStream;
    customerStream << "k, " << login << ", " << passwd << ";";
    file << customerStream.str() << std::endl;

    this->customers.push_back(Customer(login, passwd));

    file.close();
};
