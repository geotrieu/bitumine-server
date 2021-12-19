#include "socket.h"

/**
 * Socket Class
 * Wrapper Class to Interact with Sockets.
 * Adopted from Glenn Fiedler's article code found here:
 * https://gafferongames.com/post/sending_and_receiving_packets/
**/

Socket::Socket() {
    #if PLATFORM == PLATFORM_WINDOWS
        WSADATA WsaData;
        WSAStartup(MAKEWORD(2,2), &WsaData);
    #endif

    this->handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
}
        
Socket::~Socket() {
    #if PLATFORM == PLATFORM_WINDOWS
        WSACleanup();
    #endif
}
        
bool Socket::open(unsigned short port) {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short) port);

    if (bind(handle, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0) {
        printf( "failed to bind socket\n" );
        return false;
    }

    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

        int nonBlocking = 1;
        if (fcntl( handle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1) {
            printf( "failed to set non-blocking\n" );
            return false;
        }

    #elif PLATFORM == PLATFORM_WINDOWS

        DWORD nonBlocking = 1;
        if (ioctlsocket(handle, FIONBIO, &nonBlocking ) != 0) {
            printf( "failed to set non-blocking\n" );
            return false;
        }

    #endif

    return true;
}
        
void Socket::terminate() {
    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        close(handle);
    #elif PLATFORM == PLATFORM_WINDOWS
        closesocket(handle);
    #endif
}
        
bool Socket::send(const Address & destination, const void * data, int size) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(destination.getAddress());
    addr.sin_port = htons(destination.getPort());

    int sent_bytes = sendto(handle, (const char*)data, size, 0, (sockaddr*)&addr, sizeof(sockaddr_in));

    if (sent_bytes != size) {
        printf( "failed to send packet\n" );
        return false;
    }

    return true;
}
        
int Socket::receive(Address & sender, void * data, int size) {
    #if PLATFORM == PLATFORM_WINDOWS
        typedef int socklen_t;
    #endif

    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int bytes = recvfrom(handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

    unsigned int from_address = ntohl(from.sin_addr.s_addr);

    unsigned int from_port = ntohs(from.sin_port);

    return bytes;
}