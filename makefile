CC := g++

CFLAGS := -std=c++11 -Wall -Wextra

# Directory structure
BASE_DIR :=.
AMP_DIR := $(BASE_DIR)/Amp
BIT_DIR := $(BASE_DIR)/Bit
OHM_DIR := $(BASE_DIR)/Ohm
VOLT_DIR := $(BASE_DIR)/Volt
SHARED_DIR := $(BASE_DIR)/SharedData

# Amp program
AMP_SRCS := $(AMP_DIR)/src/amp.cpp $(AMP_DIR)/src/inventoryItem.cpp $(AMP_DIR)/src/main.cpp
AMP_OBJS := $(AMP_DIR)/obj/amp.o $(AMP_DIR)/obj/inventoryItem.o $(AMP_DIR)/obj/main.o
AMP_EXE := $(AMP_DIR)/build/amp.exe

# Bit program
BIT_SRCS := $(BIT_DIR)/src/main.cpp $(BIT_DIR)/src/Printer/Printer.cpp $(BIT_DIR)/src/Repository/Repository.cpp $(SHARED_DIR)/HardwareComponent/hardwareComponent.cpp $(SHARED_DIR)/ElectronicComponent/ElectronicComponent.cpp $(SHARED_DIR)/Pin/Pin.cpp $(SHARED_DIR)/ECInfo/ECInfo.cpp $(SHARED_DIR)/Connection/Connection.cpp
BIT_OBJS := $(BIT_DIR)/obj/main.o $(BIT_DIR)/obj/Printer.o $(BIT_DIR)/obj/Repository.o $(BIT_DIR)/obj/hardwareComponent.o $(BIT_DIR)/obj/ElectronicComponent.o $(BIT_DIR)/obj/Pin.o $(BIT_DIR)/obj/ECInfo.o $(BIT_DIR)/obj/Connection.o
BIT_EXE := $(BIT_DIR)/build/bit.exe

# Ohm program
OHM_SRCS := $(OHM_DIR)/src/Order.cpp $(OHM_DIR)/src/orderManager.cpp $(OHM_DIR)/src/main.cpp
OHM_OBJS := $(OHM_DIR)/obj/Order.o $(OHM_DIR)/obj/orderManager.o $(OHM_DIR)/obj/main.o
OHM_EXE := $(OHM_DIR)/build/ohm.exe

# Volt program
VOLT_SRCS := $(VOLT_DIR)/src/main.cpp $(VOLT_DIR)/src/Volt.cpp
VOLT_OBJS := $(VOLT_DIR)/obj/main.o $(VOLT_DIR)/obj/Volt.o
VOLT_EXE := $(VOLT_DIR)/build/volt.exe

.PHONY: all amp bit ohm volt clean

all: amp bit ohm volt

amp: $(AMP_EXE)

bit: $(BIT_EXE)

ohm: $(OHM_EXE)

volt: $(VOLT_EXE)

$(AMP_EXE): $(AMP_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(AMP_DIR)/obj/amp.o: $(AMP_DIR)/src/amp.cpp $(AMP_DIR)/src/amp.hpp
	$(CC) $(CFLAGS) -c -o $@ $(AMP_DIR)/src/amp.cpp

$(AMP_DIR)/obj/inventoryItem.o: $(AMP_DIR)/src/inventoryItem.cpp $(AMP_DIR)/src/inventoryItem.hpp
	$(CC) $(CFLAGS) -c -o $@ $(AMP_DIR)/src/inventoryItem.cpp

$(AMP_DIR)/obj/main.o: $(AMP_DIR)/src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $(AMP_DIR)/src/main.cpp

$(AMP_DIR)/src/inventoryItem.o: $(AMP_DIR)/src/inventoryItem.cpp $(AMP_DIR)/src/inventoryItem.hpp
	$(CC) $(CFLAGS) -c -o $@ $(AMP_DIR)/src/inventoryItem.cpp

$(BIT_EXE): $(BIT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BIT_DIR)/obj/main.o: $(BIT_DIR)/src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $(BIT_DIR)/src/main.cpp

$(BIT_DIR)/obj/Printer.o: $(BIT_DIR)/src/Printer/Printer.cpp $(BIT_DIR)/src/Printer/Printer.hpp
	$(CC) $(CFLAGS) -c -o $@ $(BIT_DIR)/src/Printer/Printer.cpp

$(BIT_DIR)/obj/Repository.o: $(BIT_DIR)/src/Repository/Repository.cpp $(BIT_DIR)/src/Repository/Repository.hpp
	$(CC) $(CFLAGS) -c -o $@ $(BIT_DIR)/src/Repository/Repository.cpp

$(BIT_DIR)/obj/hardwareComponent.o: $(SHARED_DIR)/HardwareComponent/hardwareComponent.cpp $(SHARED_DIR)/HardwareComponent/hardwareComponent.hpp
	$(CC) $(CFLAGS) -c -o $@ $(SHARED_DIR)/HardwareComponent/hardwareComponent.cpp

$(BIT_DIR)/obj/ElectronicComponent.o: $(SHARED_DIR)/ElectronicComponent/ElectronicComponent.cpp $(SHARED_DIR)/ElectronicComponent/ElectronicComponent.hpp
	$(CC) $(CFLAGS) -c -o $@ $(SHARED_DIR)/ElectronicComponent/ElectronicComponent.cpp
	
$(BIT_DIR)/obj/Pin.o: $(SHARED_DIR)/Pin/Pin.cpp $(SHARED_DIR)/Pin/Pin.hpp
	$(CC) $(CFLAGS) -c -o $@ $(SHARED_DIR)/Pin/Pin.cpp

$(BIT_DIR)/obj/ECInfo.o: $(SHARED_DIR)/ECInfo/ECInfo.cpp $(SHARED_DIR)/ECInfo/ECInfo.hpp
	$(CC) $(CFLAGS) -c -o $@ $(SHARED_DIR)/ECInfo/ECInfo.cpp

$(BIT_DIR)/obj/Connection.o: $(SHARED_DIR)/Connection/Connection.cpp $(SHARED_DIR)/Connection/Connection.hpp
	$(CC) $(CFLAGS) -c -o $@ $(SHARED_DIR)/Connection/Connection.cpp

$(OHM_EXE): $(OHM_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OHM_DIR)/obj/Order.o: $(OHM_DIR)/src/Order.cpp $(OHM_DIR)/src/Order.hpp
	$(CC) $(CFLAGS) -c -o $@ $(OHM_DIR)/src/Order.cpp

$(OHM_DIR)/obj/orderManager.o: $(OHM_DIR)/src/orderManager.cpp $(OHM_DIR)/src/orderManager.hpp
	$(CC) $(CFLAGS) -c -o $@ $(OHM_DIR)/src/orderManager.cpp

$(OHM_DIR)/obj/main.o: $(OHM_DIR)/src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $(OHM_DIR)/src/main.cpp

$(VOLT_EXE): $(VOLT_OBJS) $(VOLT_DIR)/obj/Volt.o $(SHARED_DIR)/HardwareComponent/hardwareComponent.o $(AMP_DIR)/src/inventoryItem.o
	$(CC) $(CFLAGS) -o $@ $^

$(VOLT_DIR)/obj/main.o: $(VOLT_DIR)/src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $(VOLT_DIR)/src/main.cpp

$(VOLT_DIR)/obj/Volt.o: $(VOLT_DIR)/src/Volt.cpp $(VOLT_DIR)/src/Volt.hpp $(SHARED_DIR)/HardwareComponent/hardwareComponent.cpp $(SHARED_DIR)/HardwareComponent/hardwareComponent.hpp $(AMP_DIR)/src/inventoryItem.cpp $(AMP_DIR)/src/inventoryItem.hpp
	$(CC) $(CFLAGS) -c -o $@ $(VOLT_DIR)/src/Volt.cpp

$(SHARED_DIR)/HardwareComponent/hardwareComponent.o: $(SHARED_DIR)/HardwareComponent/hardwareComponent.cpp $(SHARED_DIR)/HardwareComponent/hardwareComponent.hpp
	$(CC) $(CFLAGS) -c -o $@ $(SHARED_DIR)/HardwareComponent/hardwareComponent.cpp

clean:
	rm -rf $(AMP_DIR)/obj/*.o $(AMP_EXE) $(BIT_DIR)/obj/*.o $(BIT_EXE) $(OHM_DIR)/obj/*.o $(OHM_EXE) $(VOLT_DIR)/obj/*.o $(VOLT_EXE)