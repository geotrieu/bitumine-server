#include "client.h"

/**
 * Client Class
 * Used to manage and store information about a connecting client
 * Designed and Implemented by George Trieu
**/

Client::Client(unsigned int client_id, unsigned int client_ip, unsigned int client_port) {
    std::time_t curr_time = std::time(nullptr);
    Client(client_id, client_ip, client_port, std::asctime(std::localtime(&curr_time)));
}

Client::Client(unsigned int client_id, unsigned int client_ip, unsigned int client_port, char* last_receive_time) : 
    client_id(client_id),
    client_ip(client_ip),
    client_port(client_port),
    last_receive_time(last_receive_time) {}

unsigned int Client::getClientID() const {
    return this->client_id;
}

unsigned int Client::getClientIP() const {
    return this->client_ip;
}

unsigned int Client::getClientPort() const {
    return this->client_port;
}

char* Client::getLastReceiveTime() const {
    return this->last_receive_time;
}

bool Client::isTimeout() const {
    std::time_t curr_time = std::time(nullptr);
    if (std::asctime(std::localtime(&curr_time)) - this->last_receive_time >= CLIENT_KEEP_ALIVE_MS)
        return false;
    return true;
}