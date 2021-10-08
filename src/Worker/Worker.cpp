#include "Worker.hpp"

Worker::Worker(){
    T = std::thread([](){
        std::string MSG;
        std::cout << "Worker" << std::endl;
        while (true){
            try{
                MSG = TaskPool::Pool().popTask();
            }
            catch(...){
                return;
            }
            Task T(MSG);
            Statistics::getStat().process(T);
        }
    });
}

Worker::Worker(void (*f)()){
    T = std::thread(f);
}

Worker::~Worker(){
    T.join();
}