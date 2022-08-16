#include<iostream>
#include"ssh-agent.h"
#include "openSSHKey.h"


int main(){

    SSHAgent * agent = new SSHAgent();
    agent->createSocket();

    return 0;
}