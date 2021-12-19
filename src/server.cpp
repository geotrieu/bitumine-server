#include <iostream>
#include <string>
#include "socket.h"

unsigned short port;
unsigned short dest_port;

int main() {

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

    if (!socket.open(port)) {
        printf( "failed to create socket\n" );
        return false;
    }

    if (mode == 1) {
        //send packets
        int ip_address_classes[] = {0, 0, 0, 0};

        char *ip_address_part;
        /* get the first token */
        char * ip_address_cstr = new char [ip_address.length()+1];
        strcpy(ip_address_cstr, ip_address.c_str());
        ip_address_part = strtok(ip_address_cstr, ".");
        
        /* walk through other tokens */
        for (int i = 0; i < 4; i++) {
            ip_address_classes[i] = std::stoi(ip_address_part);
            
            ip_address_part = strtok(NULL, ".");
        }
        Address dest_address(ip_address_classes[0], ip_address_classes[1], ip_address_classes[2], ip_address_classes[3], dest_port);

        std::string phrase;
        std::cout << "Enter phrase to send to: " << ip_address_classes[0] << "." << ip_address_classes[1] << "." << ip_address_classes[2] << "." << ip_address_classes[3] << std::endl;
        std::cin >> phrase;
        const char* packet_data = phrase.c_str();
        int packet_size = strlen(phrase.c_str());

        socket.send(dest_address, packet_data, packet_size);
    } else {
        //receive packets
        while (true) {
            Address sender;
            unsigned char buffer[256];
            int bytes_read = socket.receive(sender, buffer, sizeof(buffer));

            // process received packet
            if (bytes_read > 0) {
                std::cout << bytes_read << std::endl;
                for (int i = 0; i < bytes_read; i++) {
                    std::cout << buffer[i];
                }
                std::cout << std::endl;
            }
        }
    }
}