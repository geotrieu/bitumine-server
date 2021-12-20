#include "packet.h"

/**
 * Packet Class
 * Generic Packet Class to send data across the internet
 * Designed and Implemented by George Trieu
**/

Packet::Packet() {
    Packet(0, __null);
}

Packet::Packet(unsigned int protocol_id, void * data) : protocol_id(protocol_id), data(data) {}
        
unsigned int Packet::getProtocolID() const {
    return this->protocol_id;
}

void * Packet::getData() const {
    return this->data;
}