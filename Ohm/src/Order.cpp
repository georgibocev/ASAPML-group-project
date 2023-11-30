#include "Order.hpp"


Order::Order(const std::string &name, const int &prio, const std::string &design) : orderId(generateOrderID()), status(Status::UNPROCESSED),
    clientName(name), priority(static_cast<Priority> (prio)), designID(design){}

std::string Order::generateOrderID() {
    static int counter = 0;
    long long int currTime = static_cast<long long int> (time(0));

    currTime += counter;

    ++counter;

    std::string hexNumber = ""; 

    while(currTime != 0) {
        int digit = currTime % 16;
        if(digit < 10) {
            hexNumber.push_back(48 + digit);
        } else {
            hexNumber.push_back(55 + digit);
        }
        currTime /= 16;
    }

    std::reverse(hexNumber.begin(), hexNumber.end());

    return hexNumber;
}

void Order::setID(const std::string &id) {
    this->orderId = id;
}

bool isHardwareIDFound(const std::string &designID) { 
    std::ifstream hwFile("../../SharedData/hardwareComp.txt");
    std::string line;
   
    if(hwFile.is_open()) { 
        while(std::getline(hwFile, line)) {
            if(line == designID) {
                std::cout << "Good, we have it" << std::endl;
                return true;
            }
        }
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }

    return false;
}

bool isElectronicIDFound(const std::string &elid) {
    std::string line;
    std::ifstream file("../../SharedData/elcl.txt");

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.find("ID:" + elid) != std::string::npos) {
                file.close();
                return true;
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }

    return false;
}

Order createOrder() {
    std::cout << "Splendid! First, we will need you to enter your name, priority, and component design." << std::endl;
    std::cout << "Enter the details in the following format: clientName priority compDesign width height components connections ELid ELWidth ELHeight ElPins" << std::endl;

    std::string clientName = "", compDesign = "", elID = "", elPins = "";
    int priority = 0, width = 0, height = 0, elWidth = 0, elHeight = 0;
    std::string components = "", connections = "", comps = "";

    std::cin >> clientName >> priority >> compDesign;
    std::ofstream hwFile;
    hwFile.open("../../SharedData/hardwareComp.txt", std::ios_base::app);

    if (isHardwareIDFound(compDesign)) {
        Order order(clientName, priority, compDesign);
        return order;
    } else {
        // Check if there is something after the design ID
        if (std::cin.peek() != '\n') {
            std::string remainingInput = "";
            std::getline(std::cin, remainingInput);
            std::istringstream iss(remainingInput);

            if (!(iss >> width >> height >> components >> connections >> comps)) {
                // If the format is wrong
                std::cout << "Invalid order" << std::endl;
                compDesign = "";
                Order order(clientName, priority, compDesign);
                return order;
            }
        } else {
            std::cout << "Invalid order" << std::endl;
            compDesign = "";
            Order order(clientName, priority, compDesign);
            return order;
        }

        std::cout << "We don't have it" << std::endl;

        hwFile << compDesign << std::endl;
        hwFile << "width:" << width << std::endl;
        hwFile << "height:" << height << std::endl;
        hwFile << "components:" << std::endl;

        std::istringstream componentsStream(components);
        std::string component;

        while (std::getline(componentsStream, component, ';')) {
            hwFile << component << std::endl;
        }

        hwFile << "connections:" << connections << std::endl;
        hwFile << "@" << std::endl;
        hwFile.close();

        std::cout << "Design added!" << std::endl;

        std::ofstream elFile;
        elFile.open("../../SharedData/elcl.txt", std::ios_base::app);

        std::istringstream elStream(comps);
        std::string element;

      
        while (std::getline(elStream, element, ';')) {
            std::istringstream elPartStream(element);
            std::getline(elPartStream, elID, '/');
            elPartStream >> elWidth;
            elPartStream.ignore(1, '/');
            elPartStream >> elHeight;
            elPartStream.ignore(1, '/');
            std::getline(elPartStream, elPins, '/');

            if (!isElectronicIDFound(elID)) {
                elFile << "ID:" << elID << std::endl;
                elFile << "Width:" << elWidth << std::endl;
                elFile << "Height:" << elHeight << std::endl;
                elFile << "Pins:" << elPins << std::endl;
            } else {
                std::cout << "Element already exists in the library: " << elID << std::endl;
            }
        }

        elFile.close();

        std::cout << "Order created and elements stored successfully." << std::endl;
    }

    Order order(clientName, priority, compDesign);
    return order;
} 



