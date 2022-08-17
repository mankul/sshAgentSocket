#include"ssh-agent.h"
#include<iostream>
#include<unistd.h>


#define MAX_BUFFER_SIZE  16 << 20
#define INT_LENGTH_SIZE 4


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
    unlink(ENPASS_SSH_AGENT);
    if(ack){
        bzero( (char *)&socketAddr, sizeof(socketAddr) );
        socketAddr.sun_family = AF_UNIX;
        strcpy( socketAddr.sun_path , ENPASS_SSH_AGENT);
        if( bind(socketFD, (struct sockaddr *)&socketAddr, sizeof(socketAddr) ) < 0 )
        {
            std::cout<<"could not bind with agent socket"<<std::endl;
            ack = 0;
        }
    }
    if(ack){
        std::cout<<"successfully bind with agent socket"<<std::endl;

        if( listen(socketFD, 10) < 0){
            std::cout<<"not listening agent socket"<<std::endl;
            ack = 0;

        }
    }
    if(ack){
        int i = 0;
        while(i < 10){
            std::cout<<"listening"<<std::endl;
            i+=1;
            int newSocket = accept(socketFD, (struct sockaddr *) &socketAddr, (socklen_t *) &socketAddr );

            if(newSocket < 0){
                std::cout<<"could not communicate with the client"<<std::endl;
            }            
            char * buffer;
            buffer = (char *)malloc(INT_LENGTH_SIZE);
            bzero(buffer, sizeof(buffer));
            int readAck = read(newSocket, buffer, sizeof(buffer));
            std::cout<<"reading packet size, ack is "<<readAck<<std::endl;
            int32 sizeOfData = convertStreamToInt(buffer);
            if(readAck){
                if(sizeOfData > MAX_BUFFER_SIZE){
                    readAck = 0;
                    std::cout<<"data crosses maximum buffer size"<<std::endl;
                }
            }
            if(readAck){
                std::cout<<"size is "<<sizeOfData<<std::endl;
                free(buffer);
                buffer = (char *)malloc(sizeOfData);
                bzero(buffer, sizeOfData);
                int readAck = read(newSocket, buffer, sizeof(buffer) );
            }
            if(readAck){
                std::cout<<"data recieved is "<<std::endl;
                std::cout<<buffer<<std::endl;   
            }
        }
    }
}


int32 SSHAgent::convertStreamToInt(char * stream){
    std::cout<<"convert stream to int "<<stream[0]<<stream[1]<<stream[2]<<stream[3]<<std::endl;
	int32 sizeOfPacket= (int32)(stream[0] << 24) | (int32)(stream[1] << 16) | (int32)(stream[2] << 8) | (int32)stream[3] ;
    std::cout<<"stream to Int is "<<sizeOfPacket<<std::endl;
	return sizeOfPacket;
}

void SSHAgent::killSocket(){
    close(socketFD);
    std::cout<<"killing the agent socket"<<std::endl;
}
