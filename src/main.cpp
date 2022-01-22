#include <iostream>
#include <string>
#include <sstream>

#include <server.h>
#include <vector>

int main()
{
    unsigned short port; std::string ip_address = "";

    std::cout << "Enter Server Port:" << std::endl;
    std::cin >> port; 
    
    std::cout << "Enter Server IP Address:" << std::endl;
    std::cin >> ip_address;

    Server server = Server(Address((char *)ip_address.c_str(), port));
    std::vector<Address> players;

    // Receive Packets
    while (true)
    {
        packet_array pArray = server.getPackets();

        for (int i = 0; i < pArray.packetCount; i++) {

            // TODO: Check for new players.
            {

            }

            // TODO:
            // Now take the current packet and send it off to all other players
            // effectively, the server acts as a buffer.
            {

            }

        }

    }
}