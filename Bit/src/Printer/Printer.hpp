#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <string>
#include <vector>
#include <utility>
#include "../../../SharedData/HardwareComponent/hardwareComponent.hpp"
#include "../../../SharedData/ElectronicComponent/ElectronicComponent.hpp"
#include "../Repository/Repository.hpp"

using std::pair;
using std::string;
using std::vector;

class Printer
{
public:
    Printer(
        const string &monfigFilePath,
        const string &printJobsFilePath,
        const string &productionFilePath);

    ~Printer();

    void Print();

private:
    const string m_configFilePath;
    const string m_printJobsFilePath;
    const string m_productionFilePath;

    string m_machineFormatLine1;
    vector<string> m_machineFormatLine2;
    string m_machineFormatLine3;

    Repository m_repository;

    HardwareComponent m_hardwareComponent;
    vector<string> m_boardMatrix;

    int m_step;
    int m_milliseconds;
    string m_orderId;

    void PrintBoard();
    void PrintCutBoard();
    void PrintConnections();
    void PrintComponentsMask();
    void PrintComponents();
    void PrintFinalResult();
    void Save();

    int EncodeNumbers(int left, int right);
    void PrintBoardMatrix();

    void makeMachineFormat();

    void PrintConnection(Connection connection);
    void PrintMask(const string &row);

    pair<int, int> CalculateXAndY(int compX, int compY, int x, int y, ECInfo::Rotation rotation);

    void PrintDescriptionFormat();
    void PrintBanner(const string &title);
};

#endif