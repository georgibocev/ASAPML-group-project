#include "amp.hpp"
#include "inventoryItem.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {

    if(argc < 3){
        std::cout << "Usage: program_name <config_file_path> <inventory_file_path>" << std::endl;
        return 1;
    }

    Amp amp(argv[1], argv[2]);
   

    int command = 0;

    std::cout << "Hello, and welcome to AMP - an automatic inventory managment system" << std::endl;

    while(command != 5) {
        std::cout << "1. Print current inventory" << std::endl;
        std::cout << "2. Check if there are enough resources in inventory" << std::endl;
        std::cout << "3. Order new resources" << std::endl;
        std::cout << "4. Modify config minimum quantities" << std::endl;
        std::cout << "5. Exit" << std::endl;
       

        std::cout << "Choose the number of operation you wish to start: ";
        std::cin >> command;

        if(command == 1) {
            amp.printInventory();
        } else if(command == 2) {
            amp.checkAvailabilityMenu();
        } else if(command == 3) {
            amp.placeOrderMenu();
        } else if(command == 4) {
            amp.modifyConfigMenu();
        } else if (command == 5) {
            amp.uploadInventory();
            amp.uploadConfig();
            std::cout << "Goodbye and have a nice day!" << std::endl;
            break;
        } else {
            std::cout << "Invalid input!" << std::endl;
            break;
        }
    }

    return 0;
}

