#include "stack.h"

template <typename T>
Stack<T>::Stack(unsigned capacity) {
    this->capacity = capacity;
    array = new T[capacity];
    size = 0;
}

template <typename T>
Stack<T>::~Stack(){
    delete[] array;
}

template <typename T>
unsigned Stack<T>::empty() const{
    switch (size){
        case(0):
        return 1;
    }
    return 0;
}

template <typename T>
unsigned Stack<T>::full() const{
    if (size == capacity){
        return 1;
    }
    return 0;
}

template <typename T>
void Stack<T>::push(T val){
    if (full()){
        return;
    }
    array[size] = val;
    size++;
}

template <typename T>
int Stack<T>::pop(){
    if(empty()){
        return 0;
    }
    size--;
    return 1;
}

template <typename T>
T Stack<T>::peek() const {
    if (empty()){
        throw -1;
    }
    return array[size-1];
}