#include <gtest/gtest.h>

#include "../Hurtownia_owocow/Customer.h"
#include "../Hurtownia_owocow/Person.h"
#include "../Hurtownia_owocow/Employee.h"
#include "../Hurtownia_owocow/Supplier.h"
#include "../Hurtownia_owocow/Fruit.h"
#include "../Hurtownia_owocow/Database.h"
#include "../Hurtownia_owocow/Storage.h"
#include "../Hurtownia_owocow/Order.h"
#include "../Hurtownia_owocow/Delivery.h"

Storage* Storage::storage = nullptr;
Database* Database::database = nullptr;

// -----------------------------
// LoggingPeopleTests
// -----------------------------
TEST(LoggingPeopleTests, TestPerson)
{
    std::string login = "testLogin", password = "testPassword";
    Person person(login, password);

    // GTest domyślnie oczekuje: ASSERT_EQ(expected, actual)
    ASSERT_EQ(login,   person.getLogin());
    ASSERT_EQ(password,person.getPasswd());
}

TEST(LoggingPeopleTests, TestEmployee)
{
    std::string login = "testLogin", password = "testPassword";
    Employee employee(login, password);

    ASSERT_EQ(login,   employee.getLogin());
    ASSERT_EQ(password,employee.getPasswd());
}

TEST(LoggingPeopleTests, TestCustomer)
{
    std::string login = "testLogin", password = "testPassword";
    Customer customer(login, password);

    ASSERT_EQ(login,   customer.getLogin());
    ASSERT_EQ(password,customer.getPasswd());
}

TEST(LoggingPeopleTests, TestSupplier)
{
    std::string login = "testLogin", password = "testPassword";
    Supplier supplier(login, password);

    ASSERT_EQ(login,    supplier.getLogin());
    ASSERT_EQ(password, supplier.getPasswd());
}

// -----------------------------
// DatabaseTests
// -----------------------------
TEST(DatabaseTests, AddCustomerTest)
{
    Database* database = Database::getInstance();
    std::string login = "TestUser";
    std::string passwd = "TestPassword";

    database->addCustomer(login, passwd);
    bool customerExists = database->isCustomerExists(login, passwd);

    ASSERT_TRUE(customerExists);
}

// -----------------------------
// StorageTests
// -----------------------------
TEST(StorageTests, TestSingletonInstance)
{
    Storage* instance1 = Storage::getInstance();
    Storage* instance2 = Storage::getInstance();

    ASSERT_TRUE(instance1 == instance2);
}

TEST(StorageTests, TestAddAndGetFruit)
{
    Storage* storage = Storage::getInstance();
    storage->addFruit("Apple", 1.5f, 100);

    ASSERT_TRUE(storage->isInStorage("Apple"));
    ASSERT_EQ(100, storage->getAmount("Apple"));
    ASSERT_FLOAT_EQ(1.5f, storage->getPrice("Apple"));
}

// -----------------------------
// OrderTests
// -----------------------------
TEST(OrderTests, TestGenerateOrderID)
{
    Order order;
    order.generateOrderID();
    std::string id1 = order.getorderID();

    Order anotherOrder;
    anotherOrder.generateOrderID();
    std::string id2 = anotherOrder.getorderID();

    // MSTest: AreNotEqual -> GTest: ASSERT_NE
    ASSERT_NE(id1, id2);
}

TEST(OrderTests, TestAddToOrder)
{
    Storage* storage = Storage::getInstance();
    storage->addFruit("Apple", 1.5f, 100);

    Order order;
    order.addToOrder("Apple", 10, storage);

    ASSERT_FLOAT_EQ(15.0f, order.getTotalCost());
    ASSERT_EQ(100, storage->getAmount("Apple"));
}

// -----------------------------
// FruitTests
// -----------------------------
TEST(FruitTests, TestFruitCreationAndAccessors)
{
    Fruit apple("Apple", 1.5f);
    ASSERT_EQ(std::string("Apple"), apple.getName());
    ASSERT_FLOAT_EQ(1.5f, apple.getPrice());
}

// -----------------------------
// DeliveryTests
// -----------------------------
TEST(DeliveryTests, TestDeliveryCreation)
{
    std::string testEmail = "test@example.com";
    std::map<Fruit, int> testFruits = {
        { Fruit("Apple", 1.5f), 10 },
        { Fruit("Banana", 0.8f), 5 }
    };

    Delivery delivery(testEmail, testFruits);

    ASSERT_EQ(testEmail, delivery.getId());

    for (const auto& pair : testFruits)
    {
        ASSERT_EQ(pair.second, delivery.getAmount(pair.first));
    }
}
