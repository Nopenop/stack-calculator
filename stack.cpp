#include "stack.h"

Stack::Stack(unsigned capacity) {
    this->capacity = capacity;
    array = new int[capacity];
    size = 0;
}

unsigned Stack::empty() const{
    switch (size){
        case(0):
        return 1;
    }
    return 0;
}

unsigned Stack::full() const{
    if (size == capacity){
        return 1;
    }
    return 0;
}

void Stack::push(int val){
    if (full()){
        return;
    }
    array[size] = val;
    size++;
}

void Stack::pop(){
    if(empty()){
        return;
    }
    size--;
}

int Stack::peek() const {
    if (empty()){
        throw -1;
    }
    return array[size-1];
}