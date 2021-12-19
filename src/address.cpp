#include "address.h"

/**
 * Address Class
 * Data Structure to store IP Addresses
 * Adopted from Glenn Fiedler's article code found here:
 * https://gafferongames.com/post/sending_and_receiving_packets/
**/

Address::Address() {
    // Initialize to 0.0.0.0:0 by default
    Address(0, 0, 0, 0, 0);
}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port) {
    this->address = (a << 24) | (b << 16) | (c << 8) | d;
    this->port = port;
}

Address::Address(unsigned int address, unsigned short port) : address(address), port(port) {}

unsigned int Address::getAddress() const {
    return this->address;
}

unsigned char Address::getA() const {
    return this->address >> 24;
}

unsigned char Address::getB() const {
    return (this->address & 0xFFFF00000000) >> 16;
}

unsigned char Address::getC() const {
    return (this->address & 0xFFFF0000) >> 8;
}

unsigned char Address::getD() const {
    return this->address & 0xFFFF;
}

unsigned short Address::getPort() const {
    return this->port;
}