#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

class StackOfString
{
private:
   std::stack<std::string> stack;

public:
    StackOfString()
    {
    }

    void push(std::string item)
    {
        stack.push(item);
    }

    std::string pop()
    {
        std::string top = stack.top();
        stack.pop();
        return top;
    }

    bool isEmpty() const
    {
        return stack.empty();
    }

    int size() const
    {
        return stack.size();
    }
};

void stringToList(const std::string& str, StackOfString& cont)
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        if(token == "-")
            std::cout << cont.pop() << " ";
        else
            cont.push(token);
    }
    std::cout << std::endl;
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::cout << "Got line: " << line << std::endl;

    StackOfString* stack = new StackOfString();
    stringToList(line, *stack);
    std::cout << "size: " << stack->size() << std::endl;

    std::cin.get();  //Program waiting for the last symbol
} 