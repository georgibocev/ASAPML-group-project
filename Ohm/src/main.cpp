#include <iostream>
#include "orderManager.hpp"


int main(int argc, char* argv[]) {
    
    if(argc < 2){
        std::cout << "Usage: program_name <Orders_file_path>" << std::endl;
        return 1;
    }

    int command = 0;
    OrderManager manager(argv[1]);
    manager.getOrders();
    
    std::cout << "Hello, and welcome to ASAPML hardware components!" << std::endl;

    while(command != 5) {
        std::cout << "1. Create an order" << std::endl;
        std::cout << "2. Show orders by ID" << std::endl;
        std::cout << "3. Show orders by priority" << std::endl;
        std::cout << "4. Cancel an order" << std::endl;
        std::cout << "5. Exit" << std::endl;

        std::cout << "Choose the number of operation you wish to start: ";
        std::cin >> command;

        if(command == 1) {
            manager.sendToOrders();
        } else if(command == 2) {
            manager.printOdersByID();
        } else if(command == 3) {
            manager.printOdersByPriority();
        } else if(command == 4) {
            manager.cancelOrder();
        } else if(command == 5) {
            manager.uploadOrders();
            std::cout << "Goodbye and have a nice day!" << std::endl;
            break;
        } else {
            std::cout << "Invalid input!" << std::endl;
            break;
        }
    }

    return 0;
}