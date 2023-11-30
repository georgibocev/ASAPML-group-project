#include "inventoryItem.hpp"

InventoryItem::InventoryItem(const std::string& name, int quantity)
    : m_itemName(name), m_quantity(quantity) {}

std::string InventoryItem::getItemName() const {
    return m_itemName;
}

int InventoryItem::getQuantity() const {
    return m_quantity;
}

void InventoryItem::setQuantity(const int &newQuantity) {
    m_quantity = newQuantity;
}

