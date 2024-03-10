#ifndef SSHAGENT
#define SSHAGENT


#include "config.h"
#include<sys/un.h>
#include<sys/socket.h>

#define ENPASS_SSH_AGENT "enpassSshAgent.sock"

class SSHAgent{
    public:
    int agentSockDesc; // ssh agent socket descriptor
    SSHAgent();
    ~SSHAgent();
    void createSocket();
    void killSocket();
    int32 convertStreamToInt(char * stream);
    int socketFD;
};


#endif