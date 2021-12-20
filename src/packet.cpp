#include "packet.h"

/**
 * Packet Class
 * Generic Packet Class to send data across the internet
 * Packet ID for this game is defined as GAME_PACKET_ID
 * Designed and Implemented by George Trieu
**/

template <class T>
Packet<T>::Packet() {
    Packet(0, __null);
}

template <class T>
Packet<T>::Packet(unsigned int protocol_id, T data) {
    this->protocol_id = protocol_id;
    T data_copy = data;
    this->data = data_copy;
}

template <class T>
unsigned int Packet<T>::getProtocolID() const {
    return this->protocol_id;
}

template <class T>
T Packet<T>::getData() const {
    return this->data;
}