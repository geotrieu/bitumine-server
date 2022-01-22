/*
So like. What is the common "server" functionality between the client and the full-blown, centralized server?

Both must receive player packets.
And both must send out packets
    - Now the client simply sends out the packet for itself.
    - But the server will send out packets to all players regarding all player information.

We finally note that a "server" is simply an object that allows for the high-level wrapping around a socket,
while leveraging Address's and Packets. And it provides the aforementioned functionality.
*/

#ifndef SERVER_H
#define SERVER_H

#include <socket.h>
#include <address.h>
#include <packet.h>

#define MAX_PACKETS 10

struct packet_array {
    Packet *packets;
    unsigned int packetCount;
};

class Server : Socket {

public:
    // void init_socket(unsigned short port); 
    // void close_socket();
    Server(const Address &addr);
    ~Server(); // must explicitly close_socket.
    
    void setServerIP(char *ip);
    void setServerIP(unsigned int ip);
    void setServerPort(unsigned int port);
    void setServerAddress(Address &address);
    unsigned int getServerIP() const;
    unsigned int getServerPort() const;
    Address getServerAddress() const;

    packet_array getPackets(); // Listen for incoming packets. Return a list of all such valid packets recieved.
    void sendPacket(Address, Packet);

private:
    
    Address server_address; // defined as the address of this server, not as any external server 
    Packet _packetStorage[MAX_PACKETS];   

};

#endif