#include "address.h"
#include <string>
#include <string.h>

/**
 * Address Class
 * Data Structure to store IP Addresses
 * Adopted from Glenn Fiedler's article code found here:
 * https://gafferongames.com/post/sending_and_receiving_packets/
**/

Address::Address()
{
    // Initialize to 0.0.0.0:0 by default
    init(0, 0, 0, 0, 0);
}

//format is 0.0.0.0
//TODO: implement 0.0.0.0:0000 format
Address::Address(char address[])
{
    int ip_address_classes[] = {0, 0, 0, 0};

    char *ip_address_part;
    /* get the first token */
    ip_address_part = strtok(address, ".");

    /* walk through other tokens */
    for (int i = 0; i < 4; i++)
    {
        ip_address_classes[i] = std::stoi(ip_address_part);

        ip_address_part = strtok(NULL, ".");
    }

    init(ip_address_classes[0], ip_address_classes[1], ip_address_classes[2], ip_address_classes[3], 0);
}

Address::Address(char address[], unsigned short port) : Address(address) {
    this->port = port;
}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
    init(a, b, c, d, port);
}

Address::Address(unsigned int address, unsigned short port) : address(address), port(port) {}

unsigned int Address::getAddress() const
{
    return this->address;
}

char* Address::toString() const {
    std::string addr = std::to_string(getA());
    addr += ".";
    addr += std::to_string(getB());
    addr += ".";
    addr += std::to_string(getC());
    addr += ".";
    addr += std::to_string(getD());
    addr += ":";
    addr += std::to_string(this->port);
    char *addr_cstr = new char[addr.length() + 1];
    strcpy(addr_cstr, addr.c_str());
    return addr_cstr;
}

unsigned char Address::getA() const
{
    return this->address >> 24;
}

unsigned char Address::getB() const
{
    return (this->address & 0xFFFF00000000) >> 16;
}

unsigned char Address::getC() const
{
    return (this->address & 0xFFFF0000) >> 8;
}

unsigned char Address::getD() const
{
    return this->address & 0xFFFF;
}

unsigned short Address::getPort() const
{
    return this->port;
}

void Address::init(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
    this->address = (a << 24) | (b << 16) | (c << 8) | d;
    this->port = port;
}