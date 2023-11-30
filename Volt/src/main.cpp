#include <iostream>
#include <fstream>
#include <sstream>
#include "../../Amp/src/inventoryItem.hpp"
#include "../../SharedData/HardwareComponent/hardwareComponent.hpp"
#include "Volt.hpp"

int main(int argc, char *argv[]) { 
    int command = 0;

    if(argc < 6){
        std::cout << "Usage: program_name <orders.txt> <inventory.txt> <production.txt> <history.txt> <printjobs.txt> " << std::endl;
        return 1;
    }
    
    Volt Volt(argv[1],argv[2],argv[3],argv[4],argv[5]);
    Volt.readall();
    
    std::cout << "Hello, and welcome to ASAPML hardware components!" << std::endl;

    while(command != 5) {
        std::cout << "1. Print all printjobs" << std::endl;
        std::cout << "2. Process everything" << std::endl;
        std::cout << "3. Exit" << std::endl;

        std::cout << "Choose the number of operation you wish to start: ";
        std::cin >> command;

        if(command == 1) {
            Volt.printPrintjobs();
        } else if(command == 2) {
            Volt.magicbutton();
        } else if(command == 3) {
            std::cout << "Goodbye and have a nice day!" << std::endl;
            Volt.uploadAll();
            break;
        } 
    }
    return 0;
}