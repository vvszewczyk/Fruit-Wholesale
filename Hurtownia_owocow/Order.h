#pragma once
#include "Fruit.h"
#include "Storage.h"
#include <map>

class Order
{
  private:
    std::map<Fruit, int> orderedFruits;
    std::string orderID;
    std::string status;
    float totalCost;

  public:
    Order(float cost = 0, std::string status = "Skladane");
    std::string getorderID();
    std::string getStatus();
    void updateState(const std::string &login, const std::string &orderId, const std::string &newStatus);
    float getTotalCost();
    void generateOrderID();
    void addToOrder(std::string name, int amount, Storage *storage);
    void showOrder() const;
    void cancelOrder(Storage &storage);
    void addOrder(const std::string &filename, const std::string &login) const;
    std::string trim(const std::string &str);
    void readOrder(const std::string &login, const std::string &orderId);
    static void showAllOrders(const std::string &filename);
};
