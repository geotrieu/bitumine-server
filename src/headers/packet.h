#ifndef PACKET_H
#define PACKET_H

#include <sstream>
#include "address.h"
#include "socket.h"

#define GAME_PACKET_ID 0x592F78C1
#define STRING_DATA 0x1

struct packet_header {
    int packetID;
    unsigned int packetType;
    unsigned int dataLength; // in bytes.
};

class Packet
{
    public:

        static bool sendData(Socket &socket, const Address &destination, uint8_t data_type, std::string data_serialized);
        static bool sendString(Socket &socket, const Address &destination, std::string payload);

        Packet(); 
        Packet(unsigned int packetType, void *data, unsigned int dataSize);
        bool sendDataWithSocket(Socket &socket, const Address &destination);
        void *getHeaderPtr();
        void *getDataPtr();
    
    private:
        unsigned int packetType; // Implementation defined, 0 is reserved.
        // NOTE(Noah): Each packet object stores this data as a static array. This is to avoid calling malloc.
        char data[2048]; // includes packet data as recieved (header + data)
        char dataSize; // defined as total packet data amount (header + data)
        bool disconnectReq = false;

};

#endif