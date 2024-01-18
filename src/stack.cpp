#include <iostream>
#include <string>
#include "stack.hpp"  

int main()
{
    Stack stk;         // Declare a Stack object
    string line;       // Declare a string to hold the input

    // Read lines from standard input
    while (getline(cin, line))
	
	{
        push_all(stk, line);  // Push each character of the line onto the stack
        pop_all(stk);         // Pop and print each character, reversing the line
    }

    return 0;  // Program will return 0 when EOF is reached (Control+D)
}
