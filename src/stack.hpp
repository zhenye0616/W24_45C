constexpr int STK_MAX = 1000;

class Stack {
    int _top;
    char buf[STK_MAX];

public:
    Stack() : _top(-1) {}

    void push(char c) {
        if (!isFull()) {
            buf[++_top] = c;
        }
    }

    char pop() {
        if (!isEmpty()) {
            return buf[_top--];
        }
        return '\0';
    }

    char top() {
        if (!isEmpty()) {
            return buf[_top];
        }
        return '\0';
    }

    bool isEmpty() const {
        return _top == -1;
    }

    bool isFull() const {
        return _top == STK_MAX - 1;
    }
};

void push_all(Stack& stk, const string& line) {
    for (char ch : line) {
        stk.push(ch);
    }
}

void pop_all(Stack& stk) {
    while (!stk.isEmpty()) {
        cout << stk.pop();
    }
    cout << endl;
}


