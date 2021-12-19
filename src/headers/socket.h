#ifndef SOCKET_H
#define SOCKET_H
#include "address.h"
#include <iostream>

// platform detection

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM PLATFORM_MAC
#else
    #define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
    #include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h> // NOTE(Noah): Needed for socket close.
    #include <fcntl.h>
#endif

#if PLATFORM == PLATFORM_WINDOWS
    #pragma comment( lib, "wsock32.lib" )
#endif

class Socket {
    private:
        int handle;

    public:
        Socket();
        
        ~Socket();
        
        bool open(unsigned short port);
        
        void terminate(); // NOTE(Noah): cannot be named close as gets mixed up with socket library close function.
        
        bool send(const Address & destination, const void * data, int size);
        
        int receive(Address & sender, void * data, int size);
};

#endif