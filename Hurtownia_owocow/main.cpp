#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <vector>

#include "Customer.h"
#include "Database.h"
#include "Delivery.h"
#include "Employee.h"
#include "Fruit.h"
#include "Order.h"
#include "Payment.h"
#include "Person.h"
#include "Storage.h"
#include "Supplier.h"

// Inicjalizacja statycznych wskaznikow
Database *Database::database = nullptr;
Storage *Storage::storage = nullptr;

// Deklaracje funkcji pomocniczych
void enterCredentials(std::string &login, std::string &password);
void runApplication(Database *database, Storage *storage);
void handleCustomer(Database *database, Storage *storage);
void handleEmployee(Database *database, Storage *storage);
void handleSupplier(Database *database, Storage *storage);

int main()
{
    // Wczytanie bazy danych oraz magazynu
    Database *database = Database::getInstance();
    database->readFolks();

    Storage *storage = Storage::getInstance();
    storage->readStorage();

    // Uruchomienie aplikacji
    runApplication(database, storage);

    std::cout << "Dziekuje i do zobaczenia :)" << std::endl;
    return 0;
}

void runApplication(Database *database, Storage *storage)
{
    bool appRunning = true;
    while (appRunning)
    {
        std::cout << "\n========== MENU GLOWNE ==========\n";
        std::cout << "1: Klient\n";
        std::cout << "2: Pracownik\n";
        std::cout << "3: Dostawca\n";
        std::cout << "4: Wyjscie\n";
        std::cout << "Wybierz opcje: ";
        int option;
        std::cin >> option;
        switch (option)
        {
        case 1:
            handleCustomer(database, storage);
            break;
        case 2:
            handleEmployee(database, storage);
            break;
        case 3:
            handleSupplier(database, storage);
            break;
        case 4:
            appRunning = false;
            break;
        default:
            std::cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
            break;
        }
    }
}

void enterCredentials(std::string &login, std::string &password)
{
    std::cout << "\n--- Logowanie ---\n";
    std::cout << "Podaj login: ";
    std::cin >> login;
    std::cout << "Podaj haslo: ";
    std::cin >> password;
    std::cout << std::endl;
}

void handleCustomer(Database *database, Storage *storage)
{
    bool sessionActive = true;
    std::string login, password;
    std::cout << "\n--- Logowanie Klienta ---\n";
    std::cout << "Czy chcesz utworzyc nowe konto? (1: Tak / 0: Nie): ";
    int createAccount;
    std::cin >> createAccount;
    if (createAccount == 1)
    {
        enterCredentials(login, password);
        database->addCustomer(login, password);
        database->readFolks();
    }
    enterCredentials(login, password);
    if (!database->isCustomerExists(login, password))
    {
        std::cout << "Niepoprawne dane logowania.\n";
        return;
    }
    Customer klient = database->loginCustomer(login, password);
    while (sessionActive)
    {
        std::cout << "\n--- Menu Klienta ---\n";
        std::cout << "1. Zloz zamowienie\n";
        std::cout << "2. Zglos zwrot zamowienia\n";
        std::cout << "3. Wyloguj sie\n";
        std::cout << "Wybierz opcje: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1: {
            std::cout << "\nDostepne owoce (Nazwa, Cena, Ilosc):\n";
            storage->showStorage();

            Order newOrder;
            newOrder.generateOrderID();
            bool ordering = true;
            while (ordering)
            {
                std::string fruitName;
                int amount;
                std::cout << "\nPodaj nazwe owocu: ";
                std::cin >> fruitName;
                if (!storage->isInStorage(fruitName))
                {
                    std::cout << "Owoc niedostepny.\n";
                    continue;
                }
                std::cout << "Podaj ilosc (maksymalnie " << storage->getAmount(fruitName) << "): ";
                std::cin >> amount;
                newOrder.addToOrder(fruitName, amount, storage);
                storage->updateFruit(fruitName, storage->getPrice(fruitName), storage->getAmount(fruitName) - amount);
                std::cout << "Kontynuowac zakupy? (1: Tak / 0: Nie): ";
                int cont;
                std::cin >> cont;
                ordering = (cont == 1);
            }
            newOrder.showOrder();
            std::cout << "\nWybierz metode platnosci:\n";
            std::cout << "1. Przelew bankowy\n";
            std::cout << "2. Platnosc karta\n";
            std::cout << "Inna opcja powoduje anulowanie zamowienia\n";
            int paymentChoice;
            std::cin >> paymentChoice;
            bool paymentSuccess = false;
            switch (paymentChoice)
            {
            case 1:
                paymentSuccess = Payment::processPayment(newOrder, "bank");
                break;
            case 2:
                paymentSuccess = Payment::processPayment(newOrder, "card");
                break;
            default:
                std::cout << "Zamowienie anulowane.\n";
                newOrder.cancelOrder(*storage);
                break;
            }
            if (paymentSuccess)
            {
                newOrder.addOrder("orders.txt", login);
            }
            else
            {
                std::cout << "Platnosc nieudana, zamowienie anulowane.\n";
            }
            break;
        }
        case 2: {
            std::cout << "\n--- Zwrot zamowienia ---\n";
            Order::showAllOrders("orders.txt", login);
            std::cout << "Podaj numer zamowienia do zwrotu: ";
            std::string orderId;
            std::cin >> orderId;
            Order oldOrder;
            oldOrder.readOrder(login, orderId);
            oldOrder.updateState(orderId, "Zwrot");
            oldOrder.readOrder(login, orderId);
            oldOrder.showOrder();
            std::cout << "\nZamowienie " << orderId << " zostanie wkrotce zwrocone.\n";
            break;
        }
        case 3:
        default:
            sessionActive = false;
            break;
        }
    }
}

void handleEmployee(Database *database, Storage *storage)
{
    bool sessionActive = true;
    std::string login, password;
    std::cout << "\n--- Logowanie Pracownika ---\n";
    enterCredentials(login, password);
    if (!database->isEmployeeExists(login, password))
    {
        std::cout << "Niepoprawne dane logowania.\n";
        return;
    }
    Employee pracownik = database->loginEmployee(login, password);
    while (sessionActive)
    {
        std::cout << "\n--- Menu Pracownika ---\n";
        std::cout << "1. Realizuj zamowienie\n";
        std::cout << "2. Przetworz zwrot\n";
        std::cout << "3. Aktualizuj dane owocow\n";
        std::cout << "4. Zarzadzaj magazynem (dodaj/usun/aktualizuj owoc)\n";
        std::cout << "5. Realizuj dostawa\n";
        std::cout << "6. Pokaz wszystkie zamowienia\n";
        std::cout << "7. Wyloguj sie\n";
        std::cout << "Wybierz opcje: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            pracownik.realizeOrder();
            break;
        case 2:
            pracownik.considerReturn();
            break;
        case 3:
            pracownik.updateFruit();
            break;
        case 4:
            pracownik.updateStorage();
            break;
        case 5:
            pracownik.realizeDelivery();
            break;
        case 6:
            Order::showAllOrders("orders.txt");
            break;
        case 7:
        default:
            sessionActive = false;
            break;
        }
    }
}

void handleSupplier(Database *database, Storage *storage)
{
    bool sessionActive = true;
    std::string login, password;
    std::cout << "\n--- Logowanie Dostawcy ---\n";
    enterCredentials(login, password);
    if (!database->isSupplierExists(login, password))
    {
        std::cout << "Niepoprawne dane logowania.\n";
        return;
    }
    Supplier dostawca = database->loginSupplier(login, password);
    while (sessionActive)
    {
        std::cout << "\n--- Menu Dostawcy ---\n";
        std::cout << "1. Zarejestruj nowa dostawke\n";
        std::cout << "2. Pokaz historie dostaw\n";
        std::cout << "3. Wyloguj sie\n";
        std::cout << "Wybierz opcje: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            dostawca.registerDelivery();
            break;
        case 2:
            dostawca.showDeliveryHistory();
            break;
        case 3:
        default:
            sessionActive = false;
            break;
        }
    }
}
