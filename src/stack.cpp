#include<iostream>
using namespace std;
#include "stack.hpp"

void push_all(Stack& stk, const string& line) {
    for (char ch : line) {
        stk.push(ch);
    }
}

// Pops all characters from the stack and prints them
void pop_all(Stack& stk) {
    while (!stk.isEmpty()) {  // Note the parentheses after isEmpty
        cout << stk.pop();
    }
    cout << endl;  // Print a newline after the reversed string
}



int main()
{
	Stack stk;
	string line;
	while (getline(cin, line))
	{
		push_all(stk, line);
		pop_all(stk);

	}
	return 0;
}
