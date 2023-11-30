#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include <string>
#include <vector>
#include <utility>

#include "../Connection/Connection.hpp"
#include "../ECInfo/ECInfo.hpp"

using std::string;
using std::vector;
using std::pair;

class HardwareComponent
{
public:
    HardwareComponent();

    HardwareComponent(string id, int width, int height,
        const vector<ECInfo> &components, const vector<Connection> &connections);//Constru
    HardwareComponent(const std::string& id, int width, int height,
        const std::vector<std::string>& componentNames);//constructor for Volt
    
    const string &GetId() const;
    int GetWidth() const;
    int GetHeight() const;
    const vector<ECInfo> &GetComponents() const;
    const vector<Connection> &GetConnections() const;
    const std::vector<std::string>& GetComponentNames() const;

private:
    string id;
    int width;
    int height;
    vector<ECInfo> components;
    vector<Connection> connections;
    vector<string> componentnames;
    vector<string> connections2;
};

#endif