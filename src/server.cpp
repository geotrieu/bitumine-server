#include <server.h>
#include <string>

/**
 * Server Class
 * Used to store information about the connected server
 * Designed and Implemented by George Trieu
 *  and heavily modified by Noah Cabral
**/

Server::Server(const Address &addr) : Socket(), server_address(addr) {
    // open socket.
    if (!this->open(server_address.getPort()))
    {
        printf("Error: Failed to create socket\n");
    }
}

Server::~Server() {
    this->terminate(); // close the socket.
}

void Server::setServerIP(char ip[])
{
    Address addr(ip);
    this->server_address.setAddresss(addr.getAddress());
}

void Server::setServerIP(unsigned int ip) { this->server_address.setAddresss(ip); }
void Server::setServerPort(unsigned int port) { this->server_address.setPort(port); }
unsigned int Server::getServerIP() const { return this->server_address.getAddress(); }
void Server::setServerAddress(Address &address) { this->server_address = address; }
unsigned int Server::getServerPort() const { return this->server_address.getPort(); }
Address Server::getServerAddress() const { return server_address; };

// listen for incoming packets. Return a list of all such valid packets recieved.
packet_array Server::getPackets() {
    
    packet_array p;
    p.packets = this->_packetStorage;
    p.packetCount = 0;
    Address addr;
    int bytes_recieved = 1;
    
    // We make the assumotion that we get one packet at a time. 
    while (bytes_recieved > 0 && p.packetCount < MAX_PACKETS) {
        Packet &cPacket = p.packets[p.packetCount];
        char *data = (char *)cPacket.getDataPtr();
        bytes_recieved = this->receive(addr, (void *)data, PACKET_DATA_SIZE);
        if (bytes_recieved > 0) {
            packet_header *header = (packet_header *)data;
            if (header->packetID == GAME_PACKET_ID) {
                cPacket.setPacketType(header->packetType);
                cPacket.setDataSize(bytes_recieved);
                p.packetCount++;
            }
        }
    }

    return p;
}

void Server::sendPacket(Address addr, Packet packet) {
    packet.sendDataWithSocket(*this, addr);
}
