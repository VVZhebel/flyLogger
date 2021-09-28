#pragma once

#define STATARRAY_ADD_SIZE 30
#define SECONDS_PER_DAY 86400  //60*60*24

#include <ctime>
#include <cstring>

#include <iostream>

class StatArray{
private:
    int  _start=0;
    int  _size=0;
    int* _data=0;

    void resize(int);
    inline int getIndex(const std::time_t) const;
public:
    StatArray();
    StatArray(int start, int size=STATARRAY_ADD_SIZE);
    StatArray(const StatArray&);
    ~StatArray();
    
    StatArray operator+(StatArray&);
    StatArray& operator++();
    StatArray operator++(int);
    int& operator[](const std::time_t);

    void print();
};