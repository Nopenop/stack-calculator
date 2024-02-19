#ifndef STACK_H
#define STACK_H

class Stack {
    unsigned capacity;
    int* array;
    unsigned size;
    public:
    Stack(unsigned capacity);
    void push(int val);
    void pop();
    int peek() const;
    unsigned empty() const;
    unsigned full() const;
};

#endif