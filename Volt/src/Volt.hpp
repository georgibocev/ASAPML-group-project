#pragma once

#include <string>
#include <vector>
#include "../../Ohm/src/Order.hpp"
#include "../../Amp/src/inventoryItem.hpp"
#include "../../SharedData/HardwareComponent/hardwareComponent.hpp"

class Volt {
public:
    Volt(const std::string orderfile,
    const std::string inventoryfile,
    const std::string productionfile,
    const std::string historyfile,
    const std::string printjobsfile);
    void deserializeOrders();
    void deserializeHardwareComponents(const std::string& filename);
    void readInventory();
    void processOrders();
    void createPrintjob();
    void printPrintjobs();
    void magicbutton();
    void readall();
    void uploadInventory();
    void uploadPrintjobs(); 
    void uploadHistory();
    void uploadOrders(); 
    void readProduction(); 
    void uploadProduction();
    void uploadAll(); 
    const std::vector<Order>& getOrders() const;
    const std::vector<InventoryItem>& getInventory() const;
    const std::vector<HardwareComponent>& getHWcomponents() const;
    const std::vector<std::pair<std::string,std::string>>& getPrintjobs() const;
    

private:
    std::vector<std::string> productionVec;
    std::vector<std::pair<std::string,std::string>> printjobs;
    std::vector<Order> orders;
    std::vector<InventoryItem> inventory;
    std::vector<HardwareComponent> allcomponents;
    std::string unprocessed="UNPROCESSED";
    std::string printing="PRINTING";
    std::string pending="PENDING";
    const std::string orderfile;
    const std::string inventoryfile;
    const std::string productionfile;
    const std::string historyfile;
    const std::string printjobsfile;
  
    
};
