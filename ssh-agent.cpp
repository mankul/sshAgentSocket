#include"ssh-agent.h"
#include<iostream>
#include<unistd.h>


#define MAX_BUFFER_SIZE  16 << 20
#define MAX_BYTES_READ 4096 // maximum bytes read from client socket
#define INT_LENGTH_SIZE 4


/* Messages for the authentication agent connection. */
#define SSH_AGENTC_REQUEST_RSA_IDENTITIES	1
#define SSH_AGENT_RSA_IDENTITIES_ANSWER		2
#define SSH_AGENTC_RSA_CHALLENGE		3
#define SSH_AGENT_RSA_RESPONSE			4
#define SSH_AGENT_FAILURE			5
#define SSH_AGENT_SUCCESS			6
#define SSH_AGENTC_ADD_RSA_IDENTITY		7
#define SSH_AGENTC_REMOVE_RSA_IDENTITY		8
#define SSH_AGENTC_REMOVE_ALL_RSA_IDENTITIES	9

/* private OpenSSH extensions for SSH2 */
#define SSH2_AGENTC_REQUEST_IDENTITIES		11
#define SSH2_AGENT_IDENTITIES_ANSWER		12
#define SSH2_AGENTC_SIGN_REQUEST		13
#define SSH2_AGENT_SIGN_RESPONSE		14
#define SSH2_AGENTC_ADD_IDENTITY		17
#define SSH2_AGENTC_REMOVE_IDENTITY		18
#define SSH2_AGENTC_REMOVE_ALL_IDENTITIES	19

/* smartcard */
#define SSH_AGENTC_ADD_SMARTCARD_KEY		20
#define SSH_AGENTC_REMOVE_SMARTCARD_KEY		21

/* lock/unlock the agent */
#define SSH_AGENTC_LOCK				22
#define SSH_AGENTC_UNLOCK			23

/* add key with constraints */
#define SSH_AGENTC_ADD_RSA_ID_CONSTRAINED	24
#define SSH2_AGENTC_ADD_ID_CONSTRAINED		25
#define SSH_AGENTC_ADD_SMARTCARD_KEY_CONSTRAINED 26

/* generic extension mechanism */
#define SSH_AGENTC_EXTENSION			27

#define	SSH_AGENT_CONSTRAIN_LIFETIME		1
#define	SSH_AGENT_CONSTRAIN_CONFIRM		2
#define	SSH_AGENT_CONSTRAIN_MAXSIGN		3
#define	SSH_AGENT_CONSTRAIN_EXTENSION		255

/* extended failure messages */
#define SSH2_AGENT_FAILURE			30

/* additional error code for ssh.com's ssh-agent2 */
#define SSH_COM_AGENT2_FAILURE			102

#define	SSH_AGENT_OLD_SIGNATURE			0x01
#define	SSH_AGENT_RSA_SHA2_256			0x02
#define	SSH_AGENT_RSA_SHA2_512			0x04

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
            char buffer[MAX_BYTES_READ];
            bzero(buffer, sizeof(buffer));
            int readAck = read(newSocket, buffer, sizeof(buffer));
            std::cout<<"reading packet size, ack is "<<readAck<<std::endl;
            // for(int i = 0; i < readAck; i++){
                // std::cout<<i<<"\t"<<buffer[i]<<std::endl;
            // }
            // std::cout<<std::endl;

            std::cout<<"size of packet "<<convertStreamToInt(buffer)<<std::endl;

            switch (buffer[4])
            {
            case SSH2_AGENTC_ADD_IDENTITY:
            case SSH2_AGENTC_ADD_ID_CONSTRAINED:
                std::cout<<"add identity"<<std::endl;
                break;
            
            default:
                std::cout<<"not identified"<<std::endl;
                break;
            }
            std::cout<<&buffer[4+1]<<std::endl;
            // int32 sizeOfData = convertStreamToInt(buffer);
            // if(readAck){
                // if(sizeOfData > MAX_BUFFER_SIZE){
                    // readAck = 0;
                    // std::cout<<"data crosses maximum buffer size"<<std::endl;
                // }
            // }
            // if(readAck){
                // std::cout<<"size is "<<sizeOfData<<std::endl;
                // free(buffer);
                // buffer = (char *)malloc(sizeOfData);
                // bzero(buffer, sizeOfData);
                // int readAck = read(newSocket, buffer, sizeof(buffer) );
            // }
            // if(readAck){
                // std::cout<<"data recieved is "<<std::endl;
                // std::cout<<buffer<<std::endl;   
            // }
        }
    }
}


int32 SSHAgent::convertStreamToInt(char * stream){
    std::cout<<"convert stream to int "<<stream[0]<<stream[1]<<stream[2]<<stream[3]<<std::endl;
	int32 sizeOfPacket= ( (int32) ( ( (const int8 *) (stream) )[0] ) << 24 ) |\
                        ( (int32) ( ( (const int8 *) (stream) )[1] ) << 16 ) |\
                        ( (int32) ( ( (const int8 *) (stream) )[2] ) << 8  ) |\ 
                         (int32) ( ( (const int8 *) (stream) )[3] );
    std::cout<<"stream to Int is "<<sizeOfPacket<<std::endl;
	return sizeOfPacket;
}




void SSHAgent::killSocket(){
    close(socketFD);
    std::cout<<"killing the agent socket"<<std::endl;
}
