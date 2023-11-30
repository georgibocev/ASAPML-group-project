#include "Volt.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

Volt::Volt(const std::string orderfile,
    const std::string inventoryfile,
    const std::string productionfile,
    const std::string historyfile,
    const std::string printjobsfile)
    :orderfile(orderfile),
    inventoryfile(inventoryfile),
    productionfile(productionfile),
    historyfile(historyfile),
    printjobsfile(printjobsfile){}

void Volt::deserializeOrders() {
    std::ifstream file(orderfile);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string temp;

        std::getline(iss, temp, ':');
        std::string orderID;
        std::getline(iss, orderID, ';');

        std::getline(iss, temp, ':');
        std::string status;
        std::getline(iss, status, ';');

        std::getline(iss, temp, ':');
        std::string clientName;
        std::getline(iss, clientName, ';');

        std::getline(iss, temp, ':');
        std::string priority;
        std::getline(iss, priority, ';');

        std::getline(iss, temp, ':');
        std::string designID;
        std::getline(iss, designID);

        std::vector<std::string> componentNames;
        for (const auto& component : allcomponents) {
            if (component.GetId() == designID) {
                componentNames = component.GetComponentNames();
                break;
            }
        }

        Order order(orderID, status, clientName, priority, designID, componentNames);
        orders.push_back(order);
    }

    file.close();
}

void Volt::deserializeHardwareComponents(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::string designID;
    std::string componentLine;
    std::vector<std::string> componentNames;
    int width, height;
    bool readingComponents = false;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "@") {
            allcomponents.emplace_back(designID, width, height, componentNames);
            designID.clear();
            width = 0;
            height = 0;
            componentNames.clear();
            readingComponents = false;
            continue;
        }

        if (line.find(':') == std::string::npos) {
            designID = line; 
        } else {
            std::istringstream iss(line);
            std::string key, value;
            std::getline(iss, key, ':');
            std::getline(iss, value);

            if (key == "width") {
                width = std::stoi(value);
            } else if (key == "height") {
                height = std::stoi(value);
            } else if (key == "components") {
                readingComponents = true;
                continue;
            }

            if (readingComponents && !line.empty() && key != "connections") {
                std::string componentName;
                std::istringstream componentIss(line);
                std::getline(componentIss, componentName, ':');
                componentNames.push_back(componentName);
            }
        }
    }

    inputFile.close();
}


void Volt::readInventory() {
     std::ifstream file(inventoryfile);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string resourceName;
        std::getline(iss, resourceName, ':');

        int quantity;
        iss >> quantity;

        InventoryItem item(resourceName, quantity);
        inventory.push_back(item);
    }

    file.close();
}

void Volt::processOrders() {
    for (auto& order : orders) {
        if (order.getStatus2() == unprocessed || order.getStatus2() == pending) {
            bool allComponentsAvailable = true;
            int maxDimension = 0;
            bool boardAvailable = false;

            for (const auto& component : order.getcomp()) {
                bool componentAvailable = false;
                for (auto& item : inventory) {
                    if (component == item.getItemName()) {
                        if (item.getQuantity() > 0) {
                            item.setQuantity(item.getQuantity() - 1);
                            componentAvailable = true;
                            break;
                        } else {
                            allComponentsAvailable = false;
                            break;
                        }
                    }
                }
                if (!componentAvailable) {
                    allComponentsAvailable = false;
                    break;
                }
            }

            if (allComponentsAvailable) {
                std::string designID = order.getDesignID();
                const HardwareComponent* selectedComponent = nullptr;

                for (const auto& component : allcomponents) {
                    if (component.GetId() == designID) {
                        selectedComponent = &component;
                        break;
                    }
                }

                if (selectedComponent) {
                    int dimension = std::max(selectedComponent->GetWidth(), selectedComponent->GetHeight());
                    if (dimension > maxDimension) {
                        maxDimension = dimension;
                    }

                    std::string board = "";
                    if (maxDimension <= 8) board = "Board_8";
                    else if (maxDimension <= 16) board = "Board_16";
                    else if (maxDimension <= 24) board = "Board_24";
                    else if (maxDimension <= 32) board = "Board_32";
                    else if (maxDimension <= 64) board = "Board_64";
                    else if (maxDimension <= 128) board = "Board_128";
                    else if (maxDimension <= 256) board = "Board_256";
                    else if (maxDimension <= 512) board = "Board_512";

                    for (auto& item : inventory) {
                        if (board == item.getItemName()) {
                            if (item.getQuantity() > 0) {
                                item.setQuantity(item.getQuantity() - 1);
                                boardAvailable = true;
                                break;
                            }
                        }
                    }
                }
            }

            if (allComponentsAvailable && boardAvailable) {
                order.setStatus(printing);
            } else {
                order.setStatus(pending);
            }
        }
    }
}

void Volt::createPrintjob() {
    printjobs.clear(); 

    for (const auto& order : orders) {
        if (order.getStatus2() == printing) {
            printjobs.push_back(std::make_pair(order.getID(), order.getDesignID()));
        }
    }
}

void Volt::printPrintjobs(){
    for(const auto& printjob : printjobs) {
        std::cout << "Order ID:" << printjob.first << " Design ID:" << printjob.second << std::endl;
    }
}
const std::vector<Order>& Volt::getOrders() const {
    return orders;
}
const std::vector<InventoryItem>& Volt::getInventory() const {
    return inventory;
}
const std::vector<HardwareComponent>& Volt::getHWcomponents() const{
    return allcomponents;
}
const std::vector<std::pair<std::string,std::string>>& Volt::getPrintjobs() const{
    return printjobs;
}
void Volt::magicbutton(){
    processOrders();
    createPrintjob();
    
}
void Volt::readall(){
    deserializeHardwareComponents("../../SharedData/hardwareComp.txt");
    deserializeOrders();
    readInventory();
    readProduction(); 
    

}
void Volt::uploadInventory(){
    std::ofstream configFile(inventoryfile);
    if (!configFile) {
        std::cerr << "Unable to open inventory.txt for writing." << std::endl;
        return;
    }

    for (const auto& item : inventory) {
        configFile << item.getItemName() << ": " << item.getQuantity() << std::endl;
    }

    configFile.close();

    std::cout << "Inventory upload completed successfully." << std::endl;
}

void Volt::uploadPrintjobs(){
    std::ofstream printjobfilee(printjobsfile);

    for(const auto& printjob : printjobs) {
        printjobfilee <<printjob.first << " " << printjob.second << std::endl;
    }

}

void Volt::readProduction() { 
    std::ifstream file(productionfile);
    std::string line;

    while (std::getline(file, line)) {
        productionVec.push_back(line); 
    }

    file.close();
}

void Volt::uploadHistory() {
    while (true) {
    auto it = std::find(productionVec.begin(), productionVec.end(), "@");
    if (it == productionVec.end()) {
        break;  
    }

    std::vector<Order> historyVec;
    std::vector<std::string> orderIDs;

    auto lineIt = productionVec.begin();
    while (lineIt != it) {
        const std::string& line = *lineIt;
        if (line.find("Order ID:") == 0) {
            std::istringstream iss(line);
            std::string temp, orderID;
            std::getline(iss, temp, ':');
            std::getline(iss, orderID, ';');

            orderIDs.push_back(orderID);
        }
        lineIt++;
    }

    for (const auto& orderID : orderIDs) {
        auto orderIt = std::find_if(orders.begin(), orders.end(), [&orderID](const Order& order) {
            return order.getID() == orderID;
        });
        if (orderIt != orders.end()) {
            historyVec.push_back(*orderIt);
            orders.erase(orderIt);  
        }
    }

    
    std::ofstream file(historyfile, std::ios::app);
    for (const auto& order : historyVec) {
        file << "Order ID: " << order.getID() << std::endl;
        file << "Client Name: " << order.getName() << std::endl;
        file << "Priority: " << order.getPriority2() << std::endl;
        file << "Design ID: " << order.getDesignID() << std::endl;
        file << "----------------------" << std::endl;
    }
    file.close();

    productionVec.erase(productionVec.begin(), it + 1);  
    }
}

void Volt::uploadProduction() {
    std::ofstream file(productionfile);

    for (const auto& line : productionVec) {
        file << line << std::endl;
    }

    file.close();
}

void Volt::uploadOrders() {
    std::ofstream file(orderfile);

    for (const auto& order : orders) {
        file << "Order ID:" << order.getID() << ";Status:" << order.getStatus2() << ";Client name:" << order.getName()
             << ";Priority:" << order.getPriority2() << ";Design ID:" << order.getDesignID() << std::endl;
    }

    file.close();
}
void Volt::uploadAll(){
    uploadInventory();
    uploadPrintjobs();
    uploadHistory();
    uploadProduction();
    uploadOrders();
}