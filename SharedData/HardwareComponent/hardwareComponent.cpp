#include "hardwareComponent.hpp"

HardwareComponent::HardwareComponent()
    : id(), width(0), height(0), components(), connections()
{
}

HardwareComponent::HardwareComponent(
        string id,
        int width,
        int height,
        const vector<ECInfo> &components,
        const vector<Connection> &connections
    )
    : id(id), width(width), height(height), components(components), connections(connections)
{
}
HardwareComponent::HardwareComponent(
        const std::string& id,
        int width,
        int height,
        const std::vector<std::string>& componentNames
    )
    : id(id), width(width), height(height), componentnames(componentNames)
{
}

const string &HardwareComponent::GetId() const
{
    return this->id;
}

int HardwareComponent::GetWidth() const
{
    return this->width;
}

int HardwareComponent::GetHeight() const
{
    return this->height; 
}

const vector<ECInfo> &HardwareComponent::GetComponents() const
{
    return this->components;
}

const vector<Connection> &HardwareComponent::GetConnections() const
{
    return this->connections;
}
const std::vector<std::string>& HardwareComponent::GetComponentNames() const {
    return componentnames;
}