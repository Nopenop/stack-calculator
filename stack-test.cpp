#include "stack.h"
#include <iostream>

int main() {
    Stack s1(10);
    for(int i = 0; i < 10; i++){
        s1.push(i);
    }
    std::cout << s1.full() << std::endl;
    while(!s1.empty()){
        std::cout << s1.peek() << " -> ";
        s1.pop();
    }
    try{
        std::cout << s1.peek() << std::endl;
    } catch(int val){
        std::cout << val;
    }
}