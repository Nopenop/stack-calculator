#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
    unsigned capacity;
    T* array;
    unsigned size;
    public:
    Stack(unsigned capacity);
    ~Stack();
    void push(T val);
    int pop();
    T peek() const;
    unsigned empty() const;
    unsigned full() const;
};

#endif