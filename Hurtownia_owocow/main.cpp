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

// Inicjalizacja statycznych wskaźników
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

    std::cout << "Thank you and see you again :)" << std::endl;
    return 0;
}

void runApplication(Database *database, Storage *storage)
{
    bool appRunning = true;
    while (appRunning)
    {
        std::cout << "\n========== MAIN MENU ==========\n";
        std::cout << "1: Customer\n";
        std::cout << "2: Employee\n";
        std::cout << "3: Supplier\n";
        std::cout << "4: Exit\n";
        std::cout << "Select an option: ";
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
            std::cout << "Invalid selection. Please try again.\n";
            break;
        }
    }
}

void enterCredentials(std::string &login, std::string &password)
{
    std::cout << "\n--- Login ---\n";
    std::cout << "Enter login: ";
    std::cin >> login;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << std::endl;
}

void handleCustomer(Database *database, Storage *storage)
{
    bool sessionActive = true;
    std::string login, password;
    std::cout << "\n--- Customer Login ---\n";
    std::cout << "Do you want to create a new account? (1: Yes / 0: No): ";
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
        std::cout << "Invalid login credentials.\n";
        return;
    }
    Customer klient = database->loginCustomer(login, password);
    while (sessionActive)
    {
        std::cout << "\n--- Customer Menu ---\n";
        std::cout << "1. Place an Order\n";
        std::cout << "2. Request Order Return\n";
        std::cout << "3. Log Out\n";
        std::cout << "Select an option: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1: {
            std::cout << "\nAvailable Fruits (Name, Price, Quantity):\n";
            storage->showStorage();

            Order newOrder;
            newOrder.generateOrderID();
            bool ordering = true;
            while (ordering)
            {
                std::string fruitName;
                int amount;
                std::cout << "\nEnter fruit name: ";
                std::cin >> fruitName;
                if (!storage->isInStorage(fruitName))
                {
                    std::cout << "Fruit not available.\n";
                    continue;
                }
                std::cout << "Enter quantity (max " << storage->getAmount(fruitName) << "): ";
                std::cin >> amount;
                newOrder.addToOrder(fruitName, amount, storage);
                storage->updateFruit(fruitName, storage->getPrice(fruitName), storage->getAmount(fruitName) - amount);
                std::cout << "Continue shopping? (1: Yes / 0: No): ";
                int cont;
                std::cin >> cont;
                ordering = (cont == 1);
            }
            newOrder.showOrder();
            std::cout << "\nSelect a payment method:\n";
            std::cout << "1. Bank Transfer\n";
            std::cout << "2. Card Payment\n";
            std::cout << "Any other option cancels the order\n";
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
                std::cout << "Order cancelled.\n";
                newOrder.cancelOrder(*storage);
                break;
            }
            if (paymentSuccess)
            {
                newOrder.addOrder("orders.txt", login);
            }
            else
            {
                std::cout << "Payment failed, order cancelled.\n";
            }
            break;
        }
        case 2: {
            std::cout << "\n--- Order Return ---\n";
            Order::showAllOrders("orders.txt", login);
            std::cout << "Enter the order number for return: ";
            std::string orderId;
            std::cin >> orderId;
            Order oldOrder;
            oldOrder.readOrder(login, orderId);
            oldOrder.updateState(orderId, "Zwrot");
            oldOrder.readOrder(login, orderId);
            oldOrder.showOrder();
            std::cout << "\nZamówienie " << orderId << " zostanie wkrótce zwrócone.\n";
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
    std::cout << "\n--- Employee Login ---\n";
    enterCredentials(login, password);
    if (!database->isEmployeeExists(login, password))
    {
        std::cout << "Invalid login credentials.\n";
        return;
    }
    Employee pracownik = database->loginEmployee(login, password);
    while (sessionActive)
    {
        std::cout << "\n--- Employee Menu ---\n";
        std::cout << "1. Process Order\n";
        std::cout << "2. Process Return\n";
        std::cout << "3. Update Fruit Data\n";
        std::cout << "4. Manage Storage (add/remove/update fruit)\n";
        std::cout << "5. Process Delivery\n";
        std::cout << "6. Show All Orders\n";
        std::cout << "7. Log Out\n";
        std::cout << "Select an option: ";
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
    std::cout << "\n--- Supplier Login ---\n";
    enterCredentials(login, password);
    if (!database->isSupplierExists(login, password))
    {
        std::cout << "Invalid login credentials.\n";
        return;
    }
    Supplier dostawca = database->loginSupplier(login, password);
    while (sessionActive)
    {
        std::cout << "\n--- Supplier Menu ---\n";
        std::cout << "1. Register New Delivery\n";
        std::cout << "2. Show Delivery History\n";
        std::cout << "3. Log Out\n";
        std::cout << "Select an option: ";
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
