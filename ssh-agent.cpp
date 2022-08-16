#include"ssh-agent.h"
#include<iostream>
#include<unistd.h>

SSHAgent::SSHAgent(){
    std::cout<<"initializing SSH Agent and generating client socket"<<std::endl;
}

SSHAgent::~SSHAgent(){
    std::cout<<"cleaning socket and cleaning SSH Agent"<<std::endl;
    killSocket();
}


void SSHAgent::createSocket(){
    
    int ack = 1;
    
    struct sockaddr_un  socketAddr;
    socketFD = socket(AF_UNIX, SOCK_STREAM, 0);

    if(socketFD < 1){
        ack = 0;
        std::cout<<"socket not created."<<std::endl;
    }


    unlink(CLIENT_SOCKET);
    if(ack){
        bzero( (char *)&socketAddr, sizeof(socketAddr) );
        socketAddr.sun_family = AF_UNIX;
        strcpy( socketAddr.sun_path , CLIENT_SOCKET);
        unlink(CLIENT_SOCKET);
        if( bind(socketFD, (struct sockaddr *)&socketAddr, sizeof(socketAddr) ) < 0 )
        {
            std::cout<<"could not bind with agent socket"<<std::endl;
            ack = 0;
        }
    }
    if(ack){
        std::cout<<"successfully bind with agent socket"<<std::endl;
    }
}


void SSHAgent::killSocket(){
    close(socketFD);
    std::cout<<"killing the agent socket"<<std::endl;
}
