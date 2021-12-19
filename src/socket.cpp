#include "socket.h"

/**
 * Socket Class
 * Wrapper Class to Interact with Sockets.
 * Adopted from Glenn Fiedler's article code found here:
 * https://gafferongames.com/post/sending_and_receiving_packets/
**/

Socket::Socket() {

}
        
Socket::~Socket() {

}
        
bool Socket::open(unsigned short port) {

}
        
void Socket::close() {

}

bool Socket::isOpen() const {

}
        
bool Socket::send(const Address & destination, const void * data, int size) {

}
        
int Socket::receive(Address & sender, void * data, int size) {

}