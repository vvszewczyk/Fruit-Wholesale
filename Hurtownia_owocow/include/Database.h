#pragma once
#include <vector>
#include "Customer.h"
#include "Employee.h"
#include "Supplier.h"

class Database 
{
    std::vector<Customer> customers;
    std::vector<Employee> employees;
    std::vector<Supplier> suppliers;
    static Database *database;
    Database();
public:
    // Usuwanie możliwości kopiowania i przypisywania
    Database(Database const&) = delete;
    void operator=(Database const&) = delete;


    static Database* getInstance();
    bool isCustomerExists(std::string p, std::string c);
    bool isEmployeeExists(std::string p, std::string c);
    bool isSupplierExists(std::string p, std::string c);
    Customer loginCustomer(std::string p, std::string c);
    Employee loginEmployee(std::string p, std::string c);
    Supplier loginSupplier(std::string p, std::string c);

    //wczytywanie wszystkich kont z pliku do poszczegolnych wektorow
    void readFolks();

    //wyswietlenie wszystkich ludzi ze wszystkich wektorow
    void showFolks();

    //dodanie nowego klienta do wektora i do bazy danych
    void addCustomer(std::string login, std::string passwd);
};
