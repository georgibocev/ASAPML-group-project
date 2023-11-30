#include "Connection.hpp"

Connection::Connection()
    : fromComponent(0)
    , fromPin(0)
    , toComponent(0)
    , toPin(0)
{
}

Connection::Connection(
        ComponentIndex fromComponent,
        PinIndex fromPin,
        ComponentIndex toComponent,
        PinIndex toPin
    )
    : fromComponent(fromComponent)
    , fromPin(fromPin)
    , toComponent(toComponent)
    , toPin(toPin)
{
}