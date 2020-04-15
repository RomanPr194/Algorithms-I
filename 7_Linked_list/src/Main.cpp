#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

class LinkedStackOfString
{
private:
    class Node
    {
    public:
        std::string item;
        Node* next;
    };
    Node* first = nullptr;

public:
    bool isEmpty() const
    {
        return first == nullptr;
    }

    void push(std::string item)
    {
        Node* oldfirst = first;
        first = new Node();
        first->item = item;
        first->next = oldfirst;
    }

    std::string pop()
    {
        std::string item = first->item;
        first = first->next;
        return item;
    }

    int size()
    {
        int ref_count = 1;
        Node* cur_ref = first;
        while(cur_ref->next != nullptr)
        {
            cur_ref = cur_ref->next;
            ref_count++;
        }
        return ref_count;
    }

};

void stringToList(const std::string& str, LinkedStackOfString& cont)
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        cont.push(token);
    }
    std::cout << std::endl;
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::cout << "Got line: " << line << std::endl;

    LinkedStackOfString* stack = new LinkedStackOfString();
    stringToList(line, *stack);
    std::cout << "isEmpty: " << stack->isEmpty() << std::endl;
    std::cout << "size: " << stack->size() << std::endl;

    std::cin.get();  //Program waiting for the last symbol
} 