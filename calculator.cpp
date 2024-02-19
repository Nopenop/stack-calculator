#include "stack.h"
#include "stack.cpp"
#include <iostream>
#include <iomanip>
#include <string>

// check if parenthesis, brackets, and curly are closed and matching
short int checkClosed(std::string s);
// check pair if true
short int endParCheck(char start, char end);
// check if characters in string are in expected set
short int checkChar(char c);
// convert infix to postfix
std::string inToPost(std::string s);
// solve postfix equation
double solvePost(std::string s);
// operator to priority
unsigned operatorToPriority(char c);

int main() {
    std::string testS = "(2 + 3 - 5 + 2 ^ 2)";
    switch(checkClosed(testS)){
        case(0):
        std::cout << "Closed bracket before start"<< std::endl;
        return 0;
        break;
        case(-1):
        std::cout << "non-matching pair"<< std::endl;
        return 0;
        break;
        case(-2):
        std::cout << "unexpected characters"<< std::endl;
        return 0;
        break;
    }
    try {
        std::string post = inToPost(testS);
        std::cout << post << std::endl;
        std::cout << std::setprecision(3)<<solvePost(post) << std::endl;
    }
    catch(int val){
        std::cout<<"Did not work" << std::endl;
    }
    return 0;
}

// error codes:
// 0 empty array
// -1 non-matching pair
// -2 unexpected characters
// 1 good string
short int checkClosed(std::string s){
    Stack<char> matchingP(s.length());
    for(int i = 0; i < s.length(); i++){
        switch (s[i]) {
        case('('):
        case('['):
        case('{'):
        matchingP.push(s[i]);
        break;
        case(')'):
        case(']'):
        case('}'):
        try{
        if (endParCheck(matchingP.peek(), s[i])) matchingP.pop();
        else return -1;
        }
        catch(int val){
            return 0;
        }
        break;
        default:
        if (!checkChar(s[i])) return -2;
        }
    }
    return matchingP.empty();
}

short int endParCheck(char start, char end){
    if( start=='(' && end==')' || start=='[' && end==']' || start=='{' && end=='}') return 1;
    return 0;
}

// codes
// 2 operands
// 1 operators
// 0 neither -> false
short int checkChar(char c){
    switch (c){
        case('('):
        case('{'):
        case('['):
        return 4;
        case(']'):
        case('}'):
        case(')'):
        return 3;
        case('0'):
        case('1'):
        case('2'):
        case('3'):
        case('4'):
        case('5'):
        case('6'):
        case('7'):
        case('8'):
        case('9'):
        return 2;
        case('+'):
        case('-'):
        case('*'):
        case('/'):
        case('^'):
        case('%'):
        return 1;
        case(' '):
        return 8;
        default:
        return 0;
    }
}


double solvePost(std::string s){
    Stack<double> operands(s.length());
    for(int i = 0; i < s.length(); i++){
        switch(checkChar(s[i])){
            case(1):
            // operator
            double o2, o1;
            try{
            o2 = operands.peek();
            operands.pop();
            o1 = operands.peek();
            operands.pop();
            }
            catch(int val){
                throw "Missing operands";
            }
            switch(s[i]){
                case('+'):
                operands.push(o1 + o2);
                break;
                case('-'):
                operands.push(o1 - o2);
                break;
                case('*'):
                operands.push(o1 * o2);
                break;
                case('/'):
                operands.push(o1 / o2);
                break;
                case('^'):
                operands.push(pow(o1, o2));
                break;
                case('%'):
                operands.push(double(int(o1) % int(o2)));
                break;
            }

            break;
            case(2):
            // operand
            operands.push(double (s[i]-48));
            break;
        }
    }
    return operands.peek();
}


unsigned operatorToPriority(char c){
    // priorities of operators from
    // lowest to higher
    switch(c){
        case('-'):
        return 0;
        case('+'):
        return 1;
        case('%'):
        return 2;
        case('/'):
        return 3;
        case('*'):
        return 4;
        case('^'):
        return 5;
        default:
        return 100;
    }
}

std::string inToPost(std::string s){
    // read from left to right
    // encounter operand, append to postfix
    // encounter operator, store as current operator
    // compare current to previous operator
    // if current is higher that top of stack, current is pushed 
    // to the top
    // if same or lower, keep poping operators from stack until 
    // priority is higher than operator at top. 
    // popped are appended
    // if open parenthesis, push in stack
    // if closing parenthesis, pop until open parenthesis in stack
    // append poped items to postfix except parenthesis
    // priority of operators high to low: ^, *, /, %, +, -
    std::string post = "";
    char current = 0;
    Stack<char> operators(s.length());
    for(int i = 0; i < s.length(); i++){
        switch(checkChar(s[i])){
            case(4):
            operators.push(s[i]);
            break;
            case(3):
            while (checkChar(operators.peek()) != 4){
                post += operators.peek();
                operators.pop();
            }
            operators.pop();
            break;
            case(2):
            //operands
            post += s[i];
            break;
            case(1):
            // operators
            current = s[i];
            try{
                if (operatorToPriority(current) > operatorToPriority(operators.peek())){
                    operators.push(current);
                }
                else{
                    while(operatorToPriority(current) >= operatorToPriority(operators.peek())){
                        post += operators.peek();
                        operators.pop();
                        if (operators.empty()) break;
                    }
                    operators.push(current);
                }
            }
            catch(int val){
                operators.push(current);
            }
            break;
        }
    }
    try{
        post += operators.peek();
    }
    catch(int val){
        
    }
    return post;
}