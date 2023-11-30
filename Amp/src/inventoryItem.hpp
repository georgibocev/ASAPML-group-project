#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>

class InventoryItem {
private:
    std::string m_itemName;
    int m_quantity;
public:
    InventoryItem(const std::string& name, int quantity);
    std::string getItemName() const;
    int getQuantity() const;
    void setQuantity(const int &quantity);
};

#endif  