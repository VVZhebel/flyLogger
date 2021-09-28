#include "StatArray.hpp"

StatArray::StatArray():StatArray(std::time(0)/ SECONDS_PER_DAY, STATARRAY_ADD_SIZE){
}

StatArray::StatArray(
    int start,
    int size
){
    _size = size;
    _start = start ;
    _data = new int[_size];
    std::memset(_data,0,_size*sizeof(int));
}

StatArray::~StatArray(){
    if (_data)
        delete[] _data;
}

StatArray::StatArray(const StatArray& A){
    _size = A._size;
    _start = A._start;
    _data = new int[_size];
    std::memcpy(_data, A._data, _size*sizeof(int));
}

void StatArray::resize(int inc_size = STATARRAY_ADD_SIZE){
    int offset = 0;
    int inc = (inc_size>=0)?inc_size+1:-inc_size;
    if (inc_size<0) offset = inc;
    int _nsize = _size + inc;
    int* _ndata = new int[_nsize];
    std::memset(_ndata, 0, _nsize*sizeof(int));
    std::memcpy(_ndata + offset, _data, _size*sizeof(int));
    delete[] _data;

    _data = _ndata;
    _size = _nsize;
    _start = _start - offset;
}

int& StatArray::operator[](const std::time_t index){
    int I = getIndex(index);
    if (I>=_size)
        resize(I-_size);
    if (I<0){
        resize(I);
        I = 0;
    }
    return _data[I];
}

StatArray& StatArray::operator++(){
    std::time_t Now = std::time(0);
    operator[](Now) += 1;
    return *this;
}

StatArray StatArray::operator++(int i){
    StatArray old = *this;
    operator++();
    return old;
}

StatArray StatArray::operator+(StatArray& A){
    int index, i;
    int start = (this->_start < A._start)?this->_start:A._start;
    int size  = (((this->_start + this->_size) > (A._start + A._size))?(this->_start + this->_size) : (A._start + A._size)) - start;
    
    StatArray Result(start, size);
    for (i=0; i<size; ++i){
        index = (i+start) * SECONDS_PER_DAY;
        Result[index] = operator[](index) + A[index];
    }
    return Result;
}

inline int StatArray::getIndex(const std::time_t timestamp)const{
    return timestamp / SECONDS_PER_DAY - _start;
}

void StatArray::print(){
    int Max = getIndex(std::time(0));
     for (int i=0; (i<_size) && (i<=Max); ++i){
        std::time_t datetime = (i+_start) * SECONDS_PER_DAY;
        std::cout << std::ctime(&datetime) << " " << _data[i] << std::endl;
    }   
}