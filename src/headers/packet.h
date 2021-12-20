#ifndef PACKET_H
#define PACKET_H

class Packet {
    private:
        unsigned int protocol_id;
        void * data;

    public:
        Packet();

        Packet(unsigned int protocol_id, void * data);
        
        unsigned int getProtocolID() const;

        void * getData() const;
};

#endif