#include "GetStatHandler.hpp"

GetStatHandler::GetStatHandler(){

}

GetStatHandler::~GetStatHandler(){

}

void GetStatHandler::handle(int socket){
    SocketPool::Pool().pushTask(socket);
}