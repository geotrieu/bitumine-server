#include "packet.h"
#include <string>
#include <sstream>

/**
 * Packet Class
 * Generic Packet Class to send data across the internet
 * Packet ID for this game is defined as GAME_PACKET_ID
 * Designed and Implemented by George Trieu
**/

template <class T>
Packet<T>::Packet()
{
    this->protocol_id = 0;
}

template <class T>
Packet<T>::Packet(unsigned int protocol_id, T data)
{
    this->protocol_id = protocol_id;
    T data_copy = data;
    this->data = data_copy;
}

template <class T>
unsigned int Packet<T>::getProtocolID() const
{
    return this->protocol_id;
}

template <class T>
T Packet<T>::getData() const
{
    return this->data;
}

// Serialize and Send
// Data MUST be serializable through a stream
template <class T>
bool Packet<T>::serializeAndSend(Socket &socket, const Address &destination) {
    std::ostringstream oss;
    oss << *this;
    std::string serialized = oss.str();
    const char *packet_data = serialized.c_str();
    int packet_size = strlen(packet_data);

    return socket.send(destination, packet_data, packet_size);
}

template <class T>
std::ostream &Packet<T>::serialize(std::ostream &out) const
{
    out << this->protocol_id << "\n"
        << this->data << "\n";
    return out;
}

template <class T>
std::istream &Packet<T>::deserialize(std::istream &in)
{
    if (in) {
        in >> this->protocol_id;
        in >> this->data;
    }
    return in;
}

template <class T>
std::ostream &operator<<(std::ostream &out, const Packet<T> &obj)
{
    obj.serialize(out);
    return out;
}

template <class T>
std::istream &operator>>(std::istream &in, Packet<T> &obj)
{
    obj.deserialize(in);
    return in;
}

// TODO: Remove need to explicitly instantiate different templates
template class Packet<std::string>;
template std::ostream& operator<<(std::ostream&, const Packet<std::string>&);
template std::istream& operator>>(std::istream&, Packet<std::string>&);