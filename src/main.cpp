#include "Server/Server.hpp"
#include "Worker/Worker.hpp"
#include "Storage/StatArray.hpp"
#include <iostream>
#include <signal.h>

Server* S;

void signal_callback(int signum){
    std::cout << "SIGINT recieved" << std::endl;
    S->Stop();
}

int main(){
    Worker W;
    S = new Server(22222, "log.txt");
    signal(SIGINT, signal_callback);
    S->Start();


    delete S;
}

