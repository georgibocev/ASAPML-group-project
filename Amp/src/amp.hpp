#ifndef AMP_HPP
#define AMP_HPP

#include <string>
#include <vector>
#include "inventoryItem.hpp"

class Amp {
private:
    std::string m_configFilePath;
    std::string m_inventoryFilePath;
    
    void setConfigFilePath(const std::string& filePath);
    void setInventoryFilePath(const std::string& filePath);
    void getInventory();
    void getConfig();
    void setMinQuantities();
    void importFromFile();
    void placeOrder(const std::string& itemName, const int& quantity);
    bool isItemInInventory(const std::string& itemName) const;
    bool isItemInConfig(const std::string& itemName) const;
    

public:

    Amp(const std::string& configFilePath, const std::string& inventoryFilePath);
    void modifyConfigMenu();
    void uploadInventory();
    void uploadConfig();
    void printInventory() const;
    void checkAvailabilityMenu() const;
    bool checkAvailability(const std::string& itemName, const int& quantity) const;
    void placeOrderMenu();
    std::string argv[1];
    std::string getConfigPath() const { return m_configFilePath; };
    std::string getInventoryPath() const { return m_inventoryFilePath; };
    static std::vector<InventoryItem> inventoryVec;
    static std::vector<InventoryItem> configVec;
};

#endif  