#ifndef SSHAGENT
#define SSHAGENT


#include "config.h"
#include<sys/un.h>
#include<sys/socket.h>

#define CLIENT_SOCKET "ClientSocket.sock"

class SSHAgent{
    public:
    int agentSockDesc; // ssh agent socket descriptor
    SSHAgent();
    ~SSHAgent();
    void createSocket();
};


#endif