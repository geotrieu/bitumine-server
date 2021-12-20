#ifndef PACKET_H
#define PACKET_H

#define GAME_PACKET_ID 0x592F78C1

template <class T>
class Packet {
    private:
        unsigned int protocol_id;
        T data;

    public:
        Packet();

        Packet(unsigned int protocol_id, T data);
        
        unsigned int getProtocolID() const;

        T getData() const;
};

#endif