#ifndef PACKET_H
#define PACKET_H

#include <sstream>
#include "address.h"
#include "socket.h"

#define GAME_PACKET_ID 0x592F78C1

#define STRING_DATA 0x1

class Packet
{
    public:
        static bool sendData(Socket &socket, const Address &destination, uint8_t data_type, std::string data_serialized);
        static bool sendString(Socket &socket, const Address &destination, std::string payload);
};

#endif