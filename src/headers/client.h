#ifndef CLIENT_H
#define CLIENT_H

#define CLIENT_KEEP_ALIVE_MS 10000

#include <ctime>

class Client {
    private:
        unsigned int client_id;
        unsigned int client_ip;
        unsigned int client_port;
        char* last_receive_time;

    public:
        Client(unsigned int client_id, unsigned int client_ip, unsigned int client_port);

        Client(unsigned int client_id, unsigned int client_ip, unsigned int client_port, char* last_receive_time);
        
        unsigned int getClientID() const;

        unsigned int getClientIP() const;

        unsigned int getClientPort() const;

        char* getLastReceiveTime() const;

        bool isTimeout() const;
};

#endif