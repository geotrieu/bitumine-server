#include <iostream>
#include <string>
#include <sstream>
#include "socket.h"
#include "packet.h"

unsigned short port;
unsigned short dest_port;

bool handleStringPacket(std::istringstream &iss);

int main()
{

    std::string ip_address = "";

    std::cout << "Port for Socket" << std::endl;
    std::cin >> port; // Get user input from the keyboard
    std::cout << "Port for Destination Socket" << std::endl;
    std::cin >> dest_port; // Get user input from the keyboard
    std::cout << "IP Address" << std::endl;
    std::cin >> ip_address; // Get user input from the keyboard
    std::cout << "1 for Send, 2 for Receive" << std::endl;
    int mode;
    std::cin >> mode;

    Socket socket;

    if (!socket.open(port))
    {
        printf("failed to create socket\n");
        return false;
    }

    if (mode == 1)
    {
        //send packets
        char *ip_address_cstr = new char[ip_address.length() + 1];
        strcpy(ip_address_cstr, ip_address.c_str());

        Address dest_address(ip_address_cstr, dest_port);

        std::string phrase;
        std::cout << "Enter phrase to send to: " << dest_address.toString() << std::endl;
        std::cin >> phrase;

        Packet::sendString(socket, dest_address, phrase);
    }
    else
    {
        //receive packets
        while (true)
        {
            Address sender;
            char buffer[256];
            int bytes_read = socket.receive(sender, buffer, sizeof(buffer));
            // process received packet
            if (bytes_read > 0) {
                std::string serialized(buffer);
                std::istringstream iss(serialized);
                int packet_id = 0;
                iss >> packet_id;
                if (packet_id != GAME_PACKET_ID) {
                    std::cout << "invalid packet id: " << packet_id;
                    continue;
                }

                uint8_t packet_type = 0;
                iss >> packet_type;
                switch (packet_type) {
                    case STRING_DATA:
                        handleStringPacket(iss);
                        break;
                    default:
                        std::cout << "invalid packet type: " << packet_type;
                        continue;
                }
            }
        }
    }

    socket.terminate();
}

bool handleStringPacket(std::istringstream &iss) {
    int data_length = 0;
    iss >> data_length;
    if (data_length == 0) return false;
    std::string s = "";
    iss >> s;
    
    std::cout << "-----------------" << std::endl;
    std::cout << "String Length: " << data_length << std::endl;
    std::cout << s << std::endl;
    std::cout << "-----------------" << std::endl;
    return true;
}