# ASAPML-group-project
ASAPML is a collection of interconnected and interacting programs that form an abstract simulation of a software system for automating the order and production process of hardware components. The project comprises the following programs:

* ASAPML Ω (Ohm - Order "Harmony" Manager):
  - Handles customer orders, allowing them to place orders for specific hardware components by providing blueprint files describing the component's design.
 Features:
  - Efficient file handling: Deserializes "Orders" file at startup, updating it with the latest changes upon program exit.
  - Order creation and processing: Supports order creation, printing orders by ID or priority, and canceling orders based on their ID.
 
* ASAPML Amp (Asset Monitoring Program):
  - Manages inventory by automating tracking of available electronic components. Places orders for the required quantities and types of electronic components.
Features:
  - Smart inventory management: Dynamically sets minimum quantities and handles orders accordingly.
  - Electronic library integration: Loads and updates the electronic library to ensure accurate inventory tracking.
  - User-friendly interface: Allows users to print the current inventory, check availability, order new resources, and modify configuration.
    
* ASAPML Bit (Bitwise Integration Transfer):
  - Simulates the operation of a machine for printing hardware components.
Features:
  - Step-wise component printing: Prints components in multiple steps, including board, connections, and final assembly.
  - Flexible output formats: Supports descriptive, machine, and visual formats for each printing step.
  - File management: Updates library and production files upon completing printing steps.
    
* ASAPML Volt (Virtual Operations and Logistics Tool):
  - Orchestrates the processing of print jobs and order management.
Features:
  - Seamless order processing: Checks inventory for required resources and processes orders accordingly.
  - Production monitoring: Tracks completed components and updates orders and history accordingly.
  - Efficient file management: Deserializes and updates files to reflect changes upon program exit.
    
This project provides an abstract representation of an automated process for printing hardware modules. Instead of working with real machines and physical products, the simulation involves individual programs and files.

# Program Structure
# Amp Program
The Amp program consists of the following classes:

* AssetMonitor: Manages inventory, checks and orders electronic components.
* ConfigurationManager: Handles configuration settings for inventory.
* FileHandlerUtils: Utility class for file handling operations.
* InventoryManager: Manages the inventory of electronic components.
  
# Bit Program
The Bit program includes the following classes:

* Bit: Simulates the hardware component printing process.
* ElectricComponent: Represents an electronic component.
* HardwareComp: Represents a hardware component and manages connections.
* Pin: Represents a pin on an electronic component.
* PinConnections: Manages connections between pins.

# Ohm Program
The Ohm program is structured with the following classes:

* Order: Represents a customer order.
* OrderManagement: Manages orders, inventory, and the printing process.
  
# Volt Program
The Volt program includes the following classes:

* Inventory: Represents an item in inventory.
* OrderManagement: Manages orders, inventory, and order processing.
* TextFileUtils: Utility class for handling text files.
  
# Makefile
The project includes a Makefile for building and compiling the programs. The Makefile is organized with targets for each program (amp, bit, ohm, volt) and rules for compilation. To compile a specific program, use commands like make amp or make bit. The make clean command is available to remove generated object files and executables.

# Instructions for Use
1. Compile All Programs:
  - Run 'make all' to compile all programs (amp, bit, ohm, volt).
2. Compile Individual Programs:
  - Run make amp to compile the Amp program.
  - Run make bit to compile the Bit program.
  - Run make ohm to compile the Ohm program.
  - Run make volt to compile the Volt program.
3. Clean Build:
  - Run make clean to remove generated object files and executables.

