#ifndef CONNECTION_HPP
#define CONNECTION_HPP

struct Connection
{
    using ComponentIndex = int;
    using PinIndex = int;

    Connection();
    Connection(
            ComponentIndex fromComponent,
            PinIndex fromPin,
            ComponentIndex toComponent,
            PinIndex toPin
        );

    ComponentIndex fromComponent;
    PinIndex fromPin;
    ComponentIndex toComponent;
    PinIndex toPin;
};


#endif