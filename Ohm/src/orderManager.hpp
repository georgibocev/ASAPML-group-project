#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Order.hpp"

class OrderManager {
    public:
    OrderManager(const std::string ordersFilePath) : m_ordersFilePath(ordersFilePath) {}

    void sendToOrders();

    void printOdersByID();

    void printOdersByPriority();

    void cancelOrder();

    void getOrders();

    void uploadOrders();

    std::string serialize(const Order &order);

    Order deserialize(const std::string &order);

    static std::vector<Order> orderList;

    private:
    const std::string m_ordersFilePath;
};

#endif