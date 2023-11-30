#include "ElectronicComponent.hpp"
#include <iostream>

using std::to_string;

ElectronicComponent::ElectronicComponent(
        const string &id, int height, int width, const vector<Pin> &pins
    )
    : id(id), height(height), width(width), pins(pins)
{
}

string ElectronicComponent::GetId() const
{
    return this->id;
}

int ElectronicComponent::GetHeight() const
{
    return this->height;
}

int ElectronicComponent::GetWidth() const
{
    return this->width;
}

const vector<Pin> &ElectronicComponent::GetPins() const
{
    return this->pins;
}