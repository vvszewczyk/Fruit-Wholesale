#include "pch.h"
#include "CppUnitTest.h"

#include "../Hurtownia_Owocow/Customer.h"
#include "../Hurtownia_Owocow/Person.h"
#include "../Hurtownia_Owocow/Employee.h"
#include "../Hurtownia_Owocow/Supplier.h"
#include "../Hurtownia_Owocow/Fruit.h"
#include "../Hurtownia_Owocow/Database.h"
#include "../Hurtownia_Owocow/Storage.h"
#include "../Hurtownia_Owocow/Order.h"
#include "../Hurtownia_Owocow/Delivery.h"

#include "../Hurtownia_Owocow/Customer.cpp"
#include "../Hurtownia_Owocow/Person.cpp"
#include "../Hurtownia_Owocow/Employee.cpp"
#include "../Hurtownia_Owocow/Supplier.cpp"
#include "../Hurtownia_Owocow/Fruit.cpp"
#include "../Hurtownia_Owocow/Database.cpp"
#include "../Hurtownia_Owocow/Storage.cpp"
#include "../Hurtownia_Owocow/Order.cpp"
#include "../Hurtownia_Owocow/Delivery.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Database* Database::database = nullptr;
Storage* Storage::storage = nullptr;

namespace Tests
{
	TEST_CLASS(LoggingPeopleTests)
	{
	public:
		TEST_METHOD(TestPerson)
		{
			std::string login = "testLogin", password = "testPassword";
			Person person(login, password);
			Assert::AreEqual(person.getLogin(), login);
			Assert::AreEqual(person.getPasswd(), password);
		}

		TEST_METHOD(TestEmployee)
		{
			std::string login = "testLogin", password = "testPassword";
			Employee Employee(login, password);
			Assert::AreEqual(Employee.getLogin(), login);
			Assert::AreEqual(Employee.getPasswd(), password);
		}

		TEST_METHOD(TestCustomer)
		{
			std::string login = "testLogin", password = "testPassword";
			Customer customer(login, password);
			Assert::AreEqual(customer.getLogin(), login);
			Assert::AreEqual(customer.getPasswd(), password);
		}

		TEST_METHOD(TestSupplier)
		{
			std::string login = "testLogin", password = "testPassword";
			Supplier supplier(login, password);
			Assert::AreEqual(supplier.getLogin(), login);
			Assert::AreEqual(supplier.getPasswd(), password);

		};
	};

	TEST_CLASS(DatabaseTests)
	{
	public:

		TEST_METHOD(AddCustomerTest)
		{

			Database* database = Database::getInstance();
			std::string login = "TestUser";
			std::string passwd = "TestPassword";
			database->addCustomer(login, passwd);
			bool customerExists = database->isCustomerExists(login, passwd);
			Assert::IsTrue(customerExists);

		}
	};

	TEST_CLASS(StorageTests)
	{
	public:

		TEST_METHOD(TestSingletonInstance)
		{
			Storage* instance1 = Storage::getInstance();
			Storage* instance2 = Storage::getInstance();

			Assert::IsTrue(instance1 == instance2);
		}

		TEST_METHOD(TestAddAndGetFruit)
		{
			Storage* storage = Storage::getInstance();
			storage->addFruit("Apple", 1.5f, 100);

			Assert::IsTrue(storage->isInStorage("Apple"));
			Assert::AreEqual(storage->getAmount("Apple"), 100);
			Assert::AreEqual(storage->getPrice("Apple"), 1.5f);
		}
	};

	TEST_CLASS(OrderTests)
	{
	public:

		TEST_METHOD(TestGenerateOrderID)
		{
			Order order;
			order.generateOrderID();
			std::string id1 = order.getorderID();

			Order anotherOrder;
			anotherOrder.generateOrderID();
			std::string id2 = anotherOrder.getorderID();

			Assert::AreNotEqual(id1, id2);
		}

		TEST_METHOD(TestAddToOrder)
		{
			Storage* storage = Storage::getInstance();
			storage->addFruit("Apple", 1.5f, 100);

			Order order;
			order.addToOrder("Apple", 10, storage);

			Assert::AreEqual(order.getTotalCost(), 15.0f);
			Assert::AreEqual(storage->getAmount("Apple"), 100);
		}

	};

	TEST_CLASS(FruitTests)
	{
	public:

		TEST_METHOD(TestFruitCreationAndAccessors)
		{
			Fruit apple("Apple", 1.5f);

			Assert::AreEqual(apple.getName(), std::string("Apple"));
			Assert::AreEqual(apple.getPrice(), 1.5f);
		}

	};

	TEST_CLASS(DeliveryTests)
	{
	public:

		TEST_METHOD(TestDeliveryCreation)
		{
			std::string testEmail = "test@example.com";
			std::map<Fruit, int> testFruits = {
				{Fruit("Apple", 1.5f), 10},
				{Fruit("Banana", 0.8f), 5}
			};

			Delivery delivery(testEmail, testFruits);

			Assert::AreEqual(testEmail, delivery.getId());


			for (const auto& pair : testFruits) {
				Assert::AreEqual(pair.second, delivery.getAmount(pair.first));
			}
		}
	};
}
