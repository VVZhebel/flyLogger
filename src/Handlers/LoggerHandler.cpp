#include "LoggerHandler.hpp"

LoggerHandler::LoggerHandler(const char* filename){
    _logfile.open(filename, std::ios::out | std::ios::app);
}

LoggerHandler::LoggerHandler(std::string& filename):LoggerHandler(filename.c_str()){
}

LoggerHandler::~LoggerHandler(){
    _logfile.flush();
    _logfile.close();
}

void LoggerHandler::handle(char *BUF)
{
    std::stringstream MSG;

    MSG << std::time(0) << " " << BUF;

    TaskPool::Pool().pushTask(MSG.str());

    this->_logfile << MSG.str() << std::endl;
}