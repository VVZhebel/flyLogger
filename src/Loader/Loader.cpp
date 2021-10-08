#include "Loader.hpp"

Loader::Loader(const char* _filename){
    _file.open(_filename, std::ios::in);
}

Loader::~Loader(){
    _file.close();
}

void Loader::load(){
    if (_file.fail())
        return;
    std::string line;
    while (!_file.eof()){
        std::getline(_file, line);
        if (line.length()>0)
            TaskPool::Pool().pushTask(line);
    }
}