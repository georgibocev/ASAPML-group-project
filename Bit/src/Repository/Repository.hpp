#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include <vector>
#include <string>
#include "../../../SharedData/ElectronicComponent/ElectronicComponent.hpp"
#include "../../../SharedData/HardwareComponent/hardwareComponent.hpp"

using std::string;
using std::vector;

class Repository
{
public:
    Repository();

    HardwareComponent GetHardwareComponent(const string &id);
    ElectronicComponent GetElectronicComponent(const string &id);

private:
    string m_hwCompFilePath = "../../SharedData/hardwareComp.txt";
    string m_elCompFilePath = "../../SharedData/elcl.txt";

    vector<ElectronicComponent> m_elComponents;
    vector<HardwareComponent> m_hwComponents;

    void ReadHardwareComponents();
    void ReadElectronicComponents();
};

#endif