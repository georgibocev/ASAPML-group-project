#include "Repository.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::stringstream;

Repository::Repository()
    : m_elComponents(), m_hwComponents()
{
    ReadElectronicComponents();
    ReadHardwareComponents();
}

HardwareComponent Repository::GetHardwareComponent(const string &id)
{
    auto it = std::find_if(m_hwComponents.begin(), m_hwComponents.end(),
        [&id](const HardwareComponent &comp) { return comp.GetId() == id; });

    return *it;
}

ElectronicComponent Repository::GetElectronicComponent(const string &id)
{
    auto it = std::find_if(m_elComponents.begin(), m_elComponents.end(),
        [&id](const ElectronicComponent &comp) { return comp.GetId() == id; });

    return *it;
}

void Repository::ReadHardwareComponents()
{
    ifstream hw(m_hwCompFilePath);
    if (hw.is_open())
    {
        string s;

        while (getline(hw, s, '@'))
        {
            stringstream ss(s);

            string id, width, height, components, connections;
            getline(ss, id);
            getline(ss, width);
            getline(ss, height);

            if (id == "")
            {
                break;
            }

            getline(ss, components);
            getline(ss, components);
            
            vector<ECInfo> elComps;
            string compId;
            int x, y, rotation;

            do
            {
                for (auto &c : components)
                {
                    if (c == ':' || c == ',' ||
                        c == '(' || c == ')')
                    {
                        c = ' ';
                    }
                }

                stringstream ssComps(components);
                ssComps >> compId >> x >> y >> rotation;
                elComps.emplace_back(compId, x, y, static_cast<ECInfo::Rotation>(rotation));

                getline(ss, components);
            } while (components.find("connections:") == string::npos);
            


            width.erase(0, 6);
            height.erase(0, 7);

            connections = components;
            connections.erase(0, 12);

            for (auto &c : connections)
            {
                if (c == '.' || c == ',' ||
                    c == '(' || c == ')')
                {
                    c = ' ';
                }
            }

            vector<Connection> cons;
            int fromComponent, fromPin, toComponent, toPin;
            stringstream ssCons(connections);

            while (ssCons >> fromComponent >> fromPin >> toComponent >> toPin)
            {
                cons.emplace_back(fromComponent, fromPin, toComponent, toPin);
            }

            m_hwComponents.emplace_back(id, stoi(width), stoi(height), elComps, cons);

            hw.get();
        }
    }
    hw.clear();
    hw.close();
}

void Repository::ReadElectronicComponents()
{
    ifstream el(m_elCompFilePath);
    if (el.is_open())
    {
        while (el)
        {
            string id, width, height, pins;
            getline(el, id);
            getline(el, width);
            getline(el, height);
            getline(el, pins);

            if (id == "")
            {
                break;
            }

            id.erase(0, 3);
            width.erase(0, 6);
            height.erase(0, 7);
            pins.erase(0, 5);

            for (auto &c : pins)
            {
                if (c == '(' || c == ')' || c == ',')
                {
                    c = ' ';
                }
            }

            Pin p;
            stringstream ss(pins);
            vector<Pin> ps;
            while (ss >> p.x >> p.y)
            {
                ps.push_back(p);
            }

            m_elComponents.emplace_back(id, stoi(height), stoi(width), ps);
        }
    }
    
    el.clear();
    el.close();
}