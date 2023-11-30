#ifndef CLIENTORDER_HPP
#define CLIENTORDER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <vector>

class Order {
    public:
    Order() = default;
    Order(const std::string &name, const int &prio, const std::string &design);
    Order(const std::string& orderid, const std::string& sts,
      const std::string& clientName, const std::string& prty,
      const std::string& designID, const std::vector<std::string>& componentNames)
    : orderId(orderid), sts(sts), clientName(clientName),
      prty(prty), designID(designID), components(componentNames) {}

    enum class Status {
        PENDING = 1,
        UNPROCESSED
    };

    enum class Priority {
        HIGH = 1,
        NORMAL
    };

    static std::string generateOrderID();

    void setID(const std::string &id);

    inline Status getStatus() const { return status; }
    inline std::string getStatus2() const { return sts; }
    inline std::vector<std::string> getcomp() const { return components;}
    inline std::string getOrderID() const { return orderId; }
    inline std::string getID() const { return orderId;}

    inline std::string getName() const { return clientName; }

    inline Priority getPriority() const { return priority; }
    inline std::string getPriority2() const { return prty; }
    inline std::string getDesignID() const { return designID; }
    void setStatus(const std::string& newStatus) {
        sts = newStatus;
    }

    private:
    Status status;
    std::string orderId, clientName, designID,sts,prty,id2;
    
    Priority priority;
    std::vector<std::string> components;
};

bool isHardwareIDFound(const std::string &designID);

bool isElectronicIDFound(const std::string &elid);

Order createOrder();

#endif
