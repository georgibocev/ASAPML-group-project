#ifndef EC_INFO_HPP
#define EC_INFO_HPP

#include <string>

using std::string;

struct ECInfo
{
    enum class Rotation
    {
        ZERO,
        NINETY,
        ONE_EIGHTY,
        TWO_SEVENTY
    };

    ECInfo(const string &id, int x, int y, Rotation rotation);

    string id;
    int x;
    int y;
    Rotation rotation;
};

#endif