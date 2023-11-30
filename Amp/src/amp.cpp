#include "amp.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

std::vector<InventoryItem> Amp::inventoryVec;
std::vector<InventoryItem> Amp::configVec;

Amp::Amp(const std::string& configFilePath, const std::string& inventoryFilePath) {
    setConfigFilePath(configFilePath);
    setInventoryFilePath(inventoryFilePath);
    getInventory();
    getConfig();
    setMinQuantities();
    importFromFile();
}

void Amp::setConfigFilePath(const std::string& filePath) {
    m_configFilePath = filePath;
}


void Amp::setInventoryFilePath(const std::string& filePath) {
    m_inventoryFilePath = filePath;
}

void Amp::getConfig() {
    std::ifstream configFile(getConfigPath());
    std::string configLine = "";

    if(configFile.is_open()) {
        while (std::getline(configFile, configLine)) {
            size_t colonPos = configLine.find(':');
            if (colonPos != std::string::npos) {
                std::string itemName = configLine.substr(0, colonPos);
                int quantity = std::stoi(configLine.substr(colonPos + 1));
                configVec.emplace_back(itemName, quantity);
            }
        }
    } else {
        std::cout << "Unable to open cnfg_amp.txt file!" << std::endl;
    }

    configFile.close();
}

void Amp::uploadConfig() {
    std::ofstream configFile(getConfigPath());
    if (!configFile) {
        std::cerr << "Unable to open cnfg_amp.txt for writing." << std::endl;
        return;
    }

    for (const auto& item : configVec) {
        configFile << item.getItemName() << ": " << item.getQuantity() << std::endl;
    }

    configFile.close();

    std::cout << "Config upload completed successfully." << std::endl;
}

void Amp::getInventory() {
    std::ifstream inventory(getInventoryPath());
    std::string itemAvailability = "";

    if(inventory.is_open()) {
        while (std::getline(inventory, itemAvailability)) {
            size_t colonPos = itemAvailability.find(':');
            if (colonPos != std::string::npos) {
                std::string itemName = itemAvailability.substr(0, colonPos);
                int quantity = std::stoi(itemAvailability.substr(colonPos + 1));
                inventoryVec.emplace_back(itemName, quantity);
            }
        }
    } else {
        std::cout << "Unable to open inventory.txt file!" << std::endl;
    }

    inventory.close();

    std::cout << "Inventory upload completed successfully." << std::endl;
}


void Amp::uploadInventory() {
    std::ofstream inventory(getInventoryPath());
    std::string orderLine = "";

    if(inventory.is_open()) {
        for(auto iter = inventoryVec.begin(); iter != inventoryVec.end(); ++iter) {
        inventory << iter->getItemName() << ": " << iter->getQuantity() << std::endl;
        }
    } else {
        std::cout << "Unable to open inventory.txt file!" << std::endl;
    }

    inventory.close();
}

void Amp::printInventory() const {
    for (const InventoryItem& item : inventoryVec) {
        std::cout << item.getItemName() << ": " << item.getQuantity() << std::endl;
    }
}

void Amp::checkAvailabilityMenu() const {
    std::string itemName;
    int quantity;

    std::cout << "Enter the item name: ";
    std::cin >> itemName;

    std::cout << "Enter the quantity: ";
    std::cin >> quantity;

    bool available = checkAvailability(itemName, quantity);

    if (available) {
        std::cout << "There are enough resources in inventory." << std::endl;
    } else {
        std::cout << "Insufficient resources in inventory." << std::endl;
    }
}

bool Amp::checkAvailability(const std::string& itemName, const int &quantity) const {
    for (const InventoryItem& item : inventoryVec) {
        if (item.getItemName() == itemName) {
            return item.getQuantity() >= quantity; 
        }
    }
    return false;  
}

void Amp::placeOrderMenu() {
    std::string itemName;
    int quantity;

    std::cout << "Enter the item name: ";
    std::cin >> itemName;

    if (!isItemInInventory(itemName)) {
        std::cout << "Invalid item name! Item not found in inventory." << std::endl;
        return;
    }

    std::cout << "Enter the quantity: ";
    std::cin >> quantity;

    placeOrder(itemName, quantity);
}

void Amp::placeOrder(const std::string& itemName, const int& quantity) {
    for (InventoryItem& item : inventoryVec) {
        if (item.getItemName() == itemName) {
            item.setQuantity(item.getQuantity() + quantity);
            break;
        }
    }
}

void Amp::setMinQuantities() {
    
    for (const InventoryItem& configItem : configVec) {
        const std::string& itemName = configItem.getItemName();
        const int& desiredQuantity = configItem.getQuantity();

        if (!isItemInInventory(itemName)) {
            if (desiredQuantity > 0) {
                inventoryVec.emplace_back(itemName, desiredQuantity);
            } else {
                inventoryVec.emplace_back(itemName, 0);
            }
            continue;
        }

        for (InventoryItem& inventoryItem : inventoryVec) {
            if (inventoryItem.getItemName() == itemName) {
                const int& currentQuantity = inventoryItem.getQuantity();

                if (currentQuantity < desiredQuantity) {
                    const int& orderQuantity = desiredQuantity - currentQuantity;
                    placeOrder(itemName, orderQuantity);
                }

                break;
            }
        }
    }
}

bool Amp::isItemInInventory(const std::string& itemName) const {
    auto itemFound = std::find_if(inventoryVec.begin(), inventoryVec.end(), [&](const InventoryItem& item) {
        return item.getItemName() == itemName;
    });

    return (itemFound != inventoryVec.end());
}

bool Amp::isItemInConfig(const std::string& itemName) const {
    for (const auto& item : configVec) {
        if (item.getItemName() == itemName) {
            return true;
        }
    }
    return false;
}

void Amp::importFromFile() {
    std::ifstream file("../../SharedData/elcl.txt");
    if (!file) {
        std::cerr << "Failed to open elcl.txt." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::size_t found = line.find("ID:");
        if (found != std::string::npos) {
            std::string itemName = line.substr(found + 3);
            if (!isItemInInventory(itemName)) {
                inventoryVec.emplace_back(itemName, 0);
            }
        }
    }

    file.clear();
    file.seekg(0);

    while (std::getline(file, line)) {
        std::size_t found = line.find("ID:");
        if (found != std::string::npos) {
            std::string itemName = line.substr(found + 3);
            if (!isItemInConfig(itemName)) {
                configVec.emplace_back(itemName, 0);
            }
        }
    }

    std::cout << "Import completed successfully." << std::endl;

    file.close();
}

void Amp::modifyConfigMenu() {         //TO-DO: when this method gets called and a new quantity gets set to automatically check if the desired quantity is in inventoryVec, and if it isn't to order it
    std::string itemName;
    int newQuantity;

    std::cout << "Enter the item name: ";
    std::cin >> itemName;

    if (!isItemInConfig(itemName)) {
        std::cout << "Item not found in the configuration." << std::endl;
        return;
    }

    std::cout << "Enter the new minimum quantity: ";
    std::cin >> newQuantity;

    for (InventoryItem& item : configVec) {
        if (item.getItemName() == itemName) {
            item.setQuantity(newQuantity);
            break;
        }
    }

    std::cout << "Minimum quantity updated successfully." << std::endl;
}