#ifndef PACKET_H
#define PACKET_H

#include <sstream>
#include "address.h"
#include "socket.h"

#define GAME_PACKET_ID 0x592F78C1

template <class T> class Packet;

template <class T> std::ostream &operator<<(std::ostream &out, const Packet<T> &obj);
template <class T> std::istream &operator>>(std::istream &in, Packet<T> &obj);

template <class T>
class Packet
{
private:
    unsigned int protocol_id;
    T data;

public:
    Packet();

    Packet(unsigned int protocol_id, T data);

    unsigned int getProtocolID() const;

    T getData() const;

    bool serializeAndSend(Socket &socket, const Address &destination);

    std::ostream &serialize(std::ostream &out) const;
    friend std::ostream &operator<<<>(std::ostream &out, const Packet &obj);
    std::istream &deserialize(std::istream &in);
    friend std::istream &operator>><>(std::istream &in, Packet &obj);
};

#endif