#include "packet.h"
#include <string>
#include <sstream>
#include <memory.h>

/**
 * Packet Class
 * Generic Packet Class to send data across the internet
 * Packet ID for this game is defined as GAME_PACKET_ID
 * Designed and Implemented by George Trieu
**/

// sendData
// Sends serialized data to the destination
bool Packet::sendData(Socket &socket, const Address &destination, uint8_t data_type, std::string data_serialized) {
    /* Send Packet Sequence Steps
        1. Create Output String Stream
        2. Send Game Protocol ID onto the stream
        3. Send Packet Identifier (identifies the type of data being sent) onto the stream
        4. Send Packet Data Length onto the stream
        5. Send Packet Data onto the stream
        6. Serialize Output String Stream
        7. Send Serialized Data
    */
    std::ostringstream oss;
    oss << (int) GAME_PACKET_ID;
    oss << (uint8_t) data_type;
    oss << (int) data_serialized.length();
    oss << data_serialized;
    std::string serialized = oss.str();
    const char *packet_data = serialized.c_str();
    int packet_size = strlen(packet_data);
    return socket.send(destination, packet_data, packet_size);
}

bool Packet::sendString(Socket &socket, const Address &destination, std::string payload) {
    return sendData(socket, destination, (uint8_t) STRING_DATA, payload);
}

// DESIGNED AND IMPLEMENTED BY NOAH CABRAL // 
Packet::Packet() {
    unsigned int packetType = 0;
}

Packet::Packet(unsigned int packetType, void *data, unsigned int dataSize) {
    this->packetType = packetType;
    packet_header packetHeader;
    packetHeader.packetID = GAME_PACKET_ID;
    packetHeader.packetType = packetType;
    packetHeader.dataLength = dataSize; // NOTE(Noah): Again, not really important...
    memcpy(this->getHeaderPtr(), &packetHeader, sizeof(packet_header));
    memcpy(this->getDataPtr(), data, dataSize);
}

bool Packet::sendDataWithSocket(
    Socket &socket, 
    const Address &destination
) {
    bool result = socket.send(destination, this->data, this->dataSize);
    return result;
}

void *Packet::getDataPtr() {
    return (void *)((char *)this->data + sizeof(packet_header));
}
void *Packet::getHeaderPtr() {
    return this->data;
}

// DESIGNED AND IMPLEMENTED BY NOAH CABRAL //