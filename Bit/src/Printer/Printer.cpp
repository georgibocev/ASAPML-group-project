#include "Printer.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <chrono>
#include <thread>
#include <fstream>
#include <limits.h>

using std::cout; 
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::max; 
using std::min;
using std::set;
using std::to_string;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

Printer::Printer(
        const string &configFilePath,
        const string &printJobsFilePath,
        const string &productionFilePath
    )
    : m_configFilePath(configFilePath)
    , m_printJobsFilePath(printJobsFilePath)
    , m_productionFilePath(productionFilePath)
    , m_machineFormatLine1()
    , m_machineFormatLine2()
    , m_machineFormatLine3()
    , m_repository()
    , m_hardwareComponent()
    , m_boardMatrix()
    , m_step(0)
    , m_orderId()
{
    ifstream config(m_configFilePath);
    if (config.is_open())
    {
        config >> m_milliseconds;
    }
    config.clear();
    config.close();

    ifstream printJobs(m_printJobsFilePath);
    if (printJobs.is_open())
    {
        string hwId;
        printJobs >> m_orderId >> hwId;
        m_hardwareComponent = m_repository.GetHardwareComponent(hwId);
    }
    printJobs.clear();
    printJobs.close();
}

Printer::~Printer()
{
    Save();
}

void Printer::Print()
{
    PrintBoard();
    sleep_for(milliseconds(m_milliseconds));
    PrintCutBoard();
    sleep_for(milliseconds(m_milliseconds));
    PrintConnections();
    sleep_for(milliseconds(m_milliseconds));
    PrintComponentsMask();
    sleep_for(milliseconds(m_milliseconds));
    PrintComponents();
    sleep_for(milliseconds(m_milliseconds));
    PrintFinalResult();
}

void Printer::Save()
{
    string order(m_orderId + ' ' + m_hardwareComponent.GetId());

    string printJobsContent;
    ifstream printJobsInFile(m_printJobsFilePath);
    if (printJobsInFile.is_open())
    {
        getline(printJobsInFile, printJobsContent, '\003');
    }
    printJobsInFile.clear();
    printJobsInFile.close();

    size_t index = printJobsContent.find(order);
    if (index != string::npos)
    {
        printJobsContent.erase(index, order.length() + 1);
    }

    ofstream printJobsOutFile(m_printJobsFilePath);
    if (printJobsOutFile.is_open())
    {
        printJobsOutFile << printJobsContent;
        printJobsOutFile.flush();
    }
    printJobsOutFile.clear();
    printJobsOutFile.close();

    ofstream productionFile(m_productionFilePath, ofstream::app);
    if (productionFile.is_open())
    {
        productionFile << "Order ID:" << m_orderId
            << "; id: " << m_hardwareComponent.GetId() << '\n';
        productionFile << "width: " << m_hardwareComponent.GetWidth() << '\n';
        productionFile << "height: " << m_hardwareComponent.GetHeight() << '\n';

        productionFile << "componnets:\n";
        for (const auto &comp : m_hardwareComponent.GetComponents())
        {
            productionFile << comp.id << ": (" << comp.x << ',' << comp.y << "),"
                << static_cast<int>(comp.rotation) << '\n';
        }

        productionFile << "connections: ";
        string connections;
        for (const auto &con : m_hardwareComponent.GetConnections())
        {
            connections += " ("
                + to_string(con.fromComponent) + '.'
                + to_string(con.fromPin) + ','
                + to_string(con.toComponent) + '.'
                + to_string(con.toPin) + "),";
        }
        connections.back() = '\n';
        productionFile << connections;

        productionFile << m_machineFormatLine1 << '\n';
        for (const auto &line : m_machineFormatLine2)
        {
            productionFile << line << '\n';
        }
        productionFile << m_machineFormatLine3 << '\n';

        productionFile << m_hardwareComponent.GetId() << '\n';

        for (const auto &row : m_boardMatrix)
        {
            for (auto col : row)
            {
                productionFile << col;
            }
            productionFile << '\n';
        }

        productionFile << '@' << endl;
    }
    productionFile.clear();
    productionFile.close();
}

void Printer::PrintBoard()
{
    int maxDimension =
        max(m_hardwareComponent.GetHeight(), m_hardwareComponent.GetWidth());

    int size = 0;

    if (maxDimension <= 8) size = 8;
    else if (maxDimension <= 16) size = 16;
    else if (maxDimension <= 24) size = 24;
    else if (maxDimension <= 32) size = 32;
    else if (maxDimension <= 64) size = 64;
    else if (maxDimension <= 128) size = 128;
    else if (maxDimension <= 256) size = 256;
    else if (maxDimension <= 512) size = 512;

    cout << m_hardwareComponent.GetId() << "\n\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << '*';
        }
        cout << endl;
    }
    cout << endl;
}

void Printer::PrintCutBoard()
{
    makeMachineFormat();
    for (int i = 0; i < m_hardwareComponent.GetHeight(); i++)
    {
        m_boardMatrix.emplace_back(m_hardwareComponent.GetWidth(), '*');
    }

    PrintBanner("Cut board");
    cout << m_machineFormatLine1 << '\n' << endl;
    PrintBoardMatrix();
    cout << endl;
}

void Printer::PrintConnections()
{
    const auto &connections = m_hardwareComponent.GetConnections();
    for (long unsigned int i = 0; i < connections.size(); i++)
    {
        PrintBanner("Connection " + to_string(i));
        cout << m_machineFormatLine1 << '\n' << endl;

        PrintConnection(connections.at(i));
        cout << endl;
        sleep_for(milliseconds(m_milliseconds));
    }
}

void Printer::PrintComponentsMask()
{
    PrintBanner("COMPONENTS MASK");

    cout << m_machineFormatLine1 << "\n\n";

    cout << m_machineFormatLine3 << "\n\n";

    for (const auto &ec : m_hardwareComponent.GetComponents())
    {
        auto comp = m_repository.GetElectronicComponent(ec.id);

        auto pair = CalculateXAndY(
                ec.x, ec.y, comp.GetWidth() - 1, comp.GetHeight() - 1, ec.rotation
            );
        
        int x = pair.first, y = pair.second;

        for (int i = min(ec.y, y); i <= max(ec.y, y); i++)
        {
            for (int j = min(ec.x, x); j <= max(ec.x, x); j++)
            {
                m_boardMatrix[i][j] = '1';
            }
        }
    }

    PrintBoardMatrix();
    cout << endl;

    for (const auto &row : m_boardMatrix)
    {
        PrintMask(row);
    }
}

void Printer::PrintComponents()
{
    PrintBanner("COMPONENTS");
    cout << m_machineFormatLine1 << endl;

    for (const auto &comp : m_machineFormatLine2)
    {
        cout << comp << endl;
    }

    for (auto &s : m_boardMatrix)
    {
        for (auto &c : s)
        {
            if (c == '1')
            {
                c = '0';
            }
        }
    }

    cout << endl;
    PrintBoardMatrix();
}

void Printer::PrintFinalResult()
{
    PrintBanner("FINAL RESULT FROM BIT IN ALL 3 FORMATS");
    PrintDescriptionFormat();
    cout << endl;

    cout << m_machineFormatLine1 << endl;
    for (const auto &comp : m_machineFormatLine2)
    {
        cout << comp << endl;
    }
    cout << m_machineFormatLine3 << endl;

    for (const auto &comp : m_hardwareComponent.GetComponents())
    {
        auto pins = m_repository.GetElectronicComponent(comp.id).GetPins();
        for (long unsigned int i = 0; i < pins.size(); i++)
        {
            Pin pin = pins.at(i);

            auto pair = CalculateXAndY(comp.x, comp.y, pin.x, pin.y, comp.rotation);
            int x = pair.first, y = pair.second;
            m_boardMatrix[y][x] = '1' + i;
        }
    }

    cout << endl;
    PrintBoardMatrix();
}

void Printer::PrintBoardMatrix()
{
    for (const auto &row : m_boardMatrix)
    {
        cout << row << endl;
    }
}

void Printer::makeMachineFormat()
{
    set<string> ids;
    m_machineFormatLine1 = m_hardwareComponent.GetId() + ":";
    string electronicInMachine = "";
    string sizeInMachine = std::to_string(
            EncodeNumbers(m_hardwareComponent.GetHeight(), m_hardwareComponent.GetWidth())
        );
    m_machineFormatLine1 += " " + sizeInMachine;

    for (const auto &comp : m_hardwareComponent.GetComponents())
    {
        if (!ids.count(comp.id))
        {
            ids.insert(comp.id);
            int count = 0;
            for (const auto &c : m_hardwareComponent.GetComponents())
            {
                if (c.id == comp.id)
                {
                    ++count;
                    electronicInMachine += to_string(EncodeNumbers(c.y, c.x)) + ' '
                        + to_string(static_cast<int>(c.rotation)) + ' ';
                }
            }

            m_machineFormatLine2.push_back(comp.id + ": " + to_string(count) + ' ' + electronicInMachine);
            electronicInMachine = "";
        }
    }
}

int Printer::EncodeNumbers(int left, int right)
{
    constexpr int mask{0xFF};
    return ((left & mask) << CHAR_BIT) | (right & mask);
}

void Printer::PrintConnection(Connection connection)
{
    ECInfo fromComponent = m_hardwareComponent.GetComponents().at(connection.fromComponent - 1);
    ECInfo toComponent = m_hardwareComponent.GetComponents().at(connection.toComponent - 1);

    Pin fromPin = m_repository.GetElectronicComponent(fromComponent.id).GetPins().at(connection.fromPin - 1);
    Pin toPin = m_repository.GetElectronicComponent(toComponent.id).GetPins().at(connection.toPin - 1);

    auto from = CalculateXAndY(
        fromComponent.x, fromComponent.y, fromPin.x, fromPin.y, fromComponent.rotation);
    int fromX = from.first, fromY = from.second;

    auto to = CalculateXAndY(
        toComponent.x, toComponent.y, toPin.x, toPin.y, toComponent.rotation);
    int toX = to.first, toY = to.second;

    int connection1 = EncodeNumbers(fromX, fromY);
    int connection2 = EncodeNumbers(toY, toX);

    m_machineFormatLine3 += to_string(connection1) + " " + to_string(connection2) + " ";

    cout << m_machineFormatLine3 << "\n\n";

    m_boardMatrix[fromY][fromX] = '1';
    m_boardMatrix[toY][toX] = '1';
    PrintBoardMatrix();
    m_boardMatrix[fromY][fromX] = '*';
    m_boardMatrix[toY][toX] = '*';
}

void Printer::PrintMask(const string &row)
{
    long unsigned int i = 0;
    while (i < row.length())
    {
        int mask = 0;
        for (long unsigned int j = 0; j < 8 && i + j < row.length(); j++)
        {
            if (row[i + j] == '1')
            {
                mask |= 1 << (7 - j);
            }
        }
        i += 8;

        cout << mask << ' ';
    }
    cout << endl;
}

pair<int, int> Printer::CalculateXAndY(int compX, int compY, int x, int y, ECInfo::Rotation rotation)
{
    switch (rotation)
    {
        case ECInfo::Rotation::ZERO:
            return {compX + x, compY + y};
        case ECInfo::Rotation::NINETY:
            return {compX - y, compY + x};
        case ECInfo::Rotation::ONE_EIGHTY:
            return {compX + y, compY - x};
        case ECInfo::Rotation::TWO_SEVENTY:
            return {compX - x, compY - y};
        default:
            return {-1, -1};
    }
}

void Printer::PrintDescriptionFormat()
{
    cout << "id: " << m_hardwareComponent.GetId() << endl;
    cout << "width: " << m_hardwareComponent.GetWidth() << endl;
    cout << "height: " << m_hardwareComponent.GetHeight() << endl;
    cout << "components:" << endl;
    for (const auto &comp : m_hardwareComponent.GetComponents())
    {
        cout << comp.id << ": (" << comp.x << ',' << comp.y << "),"
            << static_cast<int>(comp.rotation) << endl;
    }
    cout << "connections:";
    for (const auto &con : m_hardwareComponent.GetConnections())
    {
        cout << ' ' << '(' << con.fromComponent << '.' << con.fromPin << ','
            << con.toComponent << '.' << con.toPin << "),";
    }
    cout << endl;
}

void Printer::PrintBanner(const string &title)
{
    cout << "\n----------------- STEP " << m_step << ": "
        << title << "\n\n";

    m_step++;
}
