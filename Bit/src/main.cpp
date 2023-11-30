#include <iostream>
#include "Printer/Printer.hpp"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: program_name <config_file_path> <print_jobs_file_path> <production_file_path>" << std::endl;
        return 1;
    }
    
    Printer printer(argv[1], argv[2], argv[3]);

    printer.Print();

    return 0;
}