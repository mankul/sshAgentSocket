#include"ssh-agent.h"
#include<iostream>


SSHAgent::SSHAgent(){
    std::cout<<"initializing SSH Agent and generating client socket"<<std::endl;
}

SSHAgent::~SSHAgent(){
    std::cout<<"cleaning socket and cleaning SSH Agent"<<std::endl;
}
