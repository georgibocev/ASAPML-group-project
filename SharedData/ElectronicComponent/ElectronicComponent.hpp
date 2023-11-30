#ifndef ELECTRONIC_COMPONENT_H
#define ELECTRONIC_COMPONENT_H

#include <string>
#include <vector>

#include "../Pin/Pin.hpp"

using std::string;
using std::vector;
using std::pair;

class ElectronicComponent
{
public:
    ElectronicComponent(
            const string &id, int height, int width, const vector<Pin> &pins
        );

    string GetId() const;
    int GetHeight() const;
    int GetWidth() const;
    const vector<Pin> &GetPins() const;

private:
    string id;
    int height;
    int width;
    vector<Pin> pins;
};

#endif