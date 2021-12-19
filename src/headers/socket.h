#ifndef SOCKET_H
#define SOCKET_H
#include "address.h"

class Socket {
    private:
        int handle;

    public:
        Socket();
        
        ~Socket();
        
        bool open(unsigned short port);
        
        void close();
        
        bool isOpen() const;
        
        bool send(const Address & destination, const void * data, int size);
        
        int receive(Address & sender, void * data, int size);
};

#endif