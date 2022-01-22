#include <iostream>
#include <string>
#include <sstream>

#include <server.h>
#include <vector>

// TODO(Noah): 
/*
The idea is that the server won't actually need to know anything about any of the structures inside of
the game.

It simply needs to know the addr's that the packets came from.
So that it can send out all incoming packages to all unique addr's.
    - Alas! This is where the problem comes in! This assumes that each client is on a different addr.
    But in testing, this is actually not the case.
    - Each client is only identitifed by the uid in the player data and inside the packet.

So ultimately. I don't think we can get away with having the server now know the actual internals
of the packets.   

So the grand solution is to have this common header file.
- I can include player_packet.h, which is raylib independent.

*/

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