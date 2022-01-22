#include "packet.h"
#include <string>
#include <sstream>

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