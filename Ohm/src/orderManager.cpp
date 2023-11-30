#include "orderManager.hpp"

std::vector<Order> OrderManager::orderList;

std::string OrderManager::serialize(const Order &order) {
    std::string stat = order.getStatus() == Order::Status::UNPROCESSED ? "UNPROCESSED" : "PENDING";
    std::string prio = order.getPriority() == Order::Priority::HIGH ? "HIGH" : "NORMAL";

    std::string orderLine = "Order ID:" + order.getOrderID() + ";Status:" + stat + ";Client name:" + 
    order.getName() + ";Priority:" + prio + ";Design ID:" + order.getDesignID();

    return orderLine;
}

Order OrderManager::deserialize(const std::string &orderLine) {
    std::vector<std::string> data;
    std::string sub = "";
    size_t start = 0;
    
    for(size_t i = 0; i <= orderLine.size(); ++i) {
        if(orderLine[i] == ';' || i == orderLine.size()) {
            sub = orderLine.substr(start, i - start);
            sub.erase(0, sub.find_last_of(":") + 1);

            data.push_back(sub);
            start = i + 1;
        }
    }

    int prio = data[3] == "HIGH" ? 1 : 2;

    Order order(data[2], prio, data[4]);

    order.setID(data[0]);

    return order;
}

void OrderManager::getOrders() {
    std::ifstream orders(m_ordersFilePath);
    std::string orderLine = "";

    if(orders.is_open()) {
        while(std::getline(orders, orderLine)) {
            if(orderLine != "") {
                OrderManager::orderList.emplace_back(deserialize(orderLine));
            }
        }
    } else {
        std::cout << "Unable to open file!" << std::endl;
    }

    orders.close();
}

void OrderManager::uploadOrders() {
    std::ofstream orders(m_ordersFilePath);
    std::string orderLine = "";

    if(orders.is_open()) {
        for(auto iter = OrderManager::orderList.begin(); iter != OrderManager::orderList.end(); ++iter) {
            orderLine = serialize(*iter);
            orders << orderLine << std::endl;
        }
    } else {
        std::cout << "Unable to open file!" << std::endl;
    }

    orders.close();
}

void OrderManager::sendToOrders() {
    Order order = createOrder();
    if(order.getDesignID().empty()) {
        return;
    } else {
        OrderManager::orderList.push_back(order);
    }
}

void OrderManager::printOdersByID() {
    for(auto iter = orderList.begin(); iter != orderList.end(); ++iter) {
        std::string stat = iter->getStatus() == Order::Status::UNPROCESSED ? "UNPROCESSED" : "PENDING";
        std::string prio = iter->getPriority() == Order::Priority::HIGH ? "HIGH" : "NORMAL";

        std::cout << "Order ID: " << iter->getOrderID() << "; Status: " << stat << "; Client name: " << 
        iter->getName() << "; Order priority: " << prio << "; Design ID: " << iter->getDesignID() << std::endl;
    }

    std::cout << std::endl;
}

bool predicate(const Order  &order1, const Order &order2) { 
    if (order1.getPriority() < order2.getPriority()) {
        return true;
    } else {
        return false;
    }
}

void OrderManager::printOdersByPriority() {
    std::vector<Order> copy = orderList;
    std::stable_sort(copy.begin(), copy.end(), predicate);

    for(auto iter = copy.begin(); iter != copy.end(); ++iter) {
        std::string stat = iter->getStatus() == Order::Status::UNPROCESSED ? "UNPROCESSED" : "PENDING";
        std::string prio = iter->getPriority() == Order::Priority::HIGH ? "HIGH" : "NORMAL";

        std::cout << "Order ID: " << iter->getOrderID() << "; Status: " << stat << "; Client name: " << 
        iter->getName() << "; Order priority: " << prio << "; Design ID: " << iter->getDesignID() << std::endl;
    }

    std::cout << std::endl;
}

void OrderManager::cancelOrder() {
    std::string id = "";
    std::cout << "Please enter the ID of the order you wish to cancel: ";
    std::cin >> id;

    for(auto iter = orderList.begin(); iter != orderList.end(); ++iter) {
        if(iter->getOrderID() == id) {
            orderList.erase(iter);
        }
    }
}
