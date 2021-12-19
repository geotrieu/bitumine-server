#include <iostream>
#include <string>
#include "address.h"

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
    #include <fcntl.h>
#endif

#if PLATFORM == PLATFORM_WINDOWS
    #pragma comment( lib, "wsock32.lib" )
#endif

bool InitializeSockets() {
    #if PLATFORM == PLATFORM_WINDOWS
        WSADATA WsaData;
        return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
    #else
        return true;
    #endif
}

void ShutdownSockets() {
    #if PLATFORM == PLATFORM_WINDOWS
        WSACleanup();
    #endif
}

unsigned short PORT;
unsigned short dest_port;

int main() {

    std::cout << "Port for Socket" << std::endl;
    std::cin >> PORT; // Get user input from the keyboard
    std::cout << "Port for Destination Socket" << std::endl;
    std::cin >> dest_port; // Get user input from the keyboard
    std::cout << "1 for Send, 2 for Receive" << std::endl;
    int mode;
    std::cin >> mode;

    InitializeSockets();

    int handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

    if ( handle <= 0 ) {
        printf( "failed to create socket\n" );
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = 
        htons( (unsigned short) PORT );

    if ( bind( handle, 
               (const sockaddr*) &address, 
               sizeof(sockaddr_in) ) < 0 )
    {
        printf( "failed to bind socket\n" );
        return false;
    }

    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

        int nonBlocking = 1;
        if ( fcntl( handle, 
                    F_SETFL, 
                    O_NONBLOCK, 
                    nonBlocking ) == -1 )
        {
            printf( "failed to set non-blocking\n" );
            return false;
        }

    #elif PLATFORM == PLATFORM_WINDOWS

        DWORD nonBlocking = 1;
        if ( ioctlsocket( handle, 
                          FIONBIO, 
                          &nonBlocking ) != 0 )
        {
            printf( "failed to set non-blocking\n" );
            return false;
        }

    #endif

    if (mode == 1) {
        Address dest_address(127, 0, 0, 1, dest_port);

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl( dest_address.getAddress() );
        addr.sin_port = htons( dest_address.getPort() );

        std::string phrase;
        std::cout << "Enter phrase to send" << std::endl;
        std::cin >> phrase;
        const char* packet_data = phrase.c_str();
        int packet_size = strlen(phrase.c_str());

        int sent_bytes = 
            sendto( handle, 
                    (const char*)packet_data, 
                    packet_size,
                    0, 
                    (sockaddr*)&addr, 
                    sizeof(sockaddr_in) );

        if ( sent_bytes != packet_size )
        {
            printf( "failed to send packet\n" );
            return false;
        }
    } else {
        while ( true ) {
            unsigned char packet_data[256];

            unsigned int max_packet_size = 
                sizeof( packet_data );

            #if PLATFORM == PLATFORM_WINDOWS
            typedef int socklen_t;
            #endif

            sockaddr_in from;
            socklen_t fromLength = sizeof( from );

            int bytes = recvfrom( handle, 
                                (char*)packet_data, 
                                max_packet_size,
                                0, 
                                (sockaddr*)&from, 
                                &fromLength );

            unsigned int from_address = 
                ntohl( from.sin_addr.s_addr );

            unsigned int from_port = 
                ntohs( from.sin_port );

            // process received packet
            if ( bytes > 0 ) {
                std::cout << bytes << std::endl;
                for (int i = 0; i < bytes; i++) {
                    std::cout << packet_data[i];
                }
                std::cout << std::endl;
            }
        }
    }

    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    close( handle );
    #elif PLATFORM == PLATFORM_WINDOWS
    closesocket( handle );
    #endif

    ShutdownSockets();
}