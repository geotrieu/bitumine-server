#include <iostream>
#include <string>
#include <sstream>
#include "socket.h"
#include "packet.h"

unsigned short port;
unsigned short dest_port;

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

        Packet<std::string> p(0xFFFF, phrase);
        p.serializeAndSend(socket, dest_address);
    }
    else
    {
        //receive packets
        while (true)
        {
            Address sender;
            char buffer[256];
            int bytes_read = socket.receive(sender, buffer, sizeof(buffer));
            std::string serialized(buffer);
            std::istringstream iss(serialized);
            Packet<std::string> p;
            iss >> p;

            // process received packet
            if (bytes_read > 0)
            {
                std::cout << bytes_read << std::endl;
                std::cout << "-----------------" << std::endl;
                std::cout << "Protocol ID: " << p.getProtocolID() << std::endl;
                std::cout << p.getData() << std::endl;
            }
        }
    }

    socket.terminate();
}