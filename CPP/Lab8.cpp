#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct node {
    string value;
    node* next;

    node(string val) : value(val), next(nullptr) {}
};

class stackL {
    node* head;

public:
    stackL() : head(nullptr) {}

    void push(string value) {
        node* newHead = new node(value);
        newHead->next = head;
        head = newHead;
    }

    string pop() {
        if (!head) return "";

        string retVal = head->value;
        node* temp = head;
        head = head->next;
        delete temp;
        return retVal;
    }

    string peek() {
        return head ? head->value : "";
    }

    bool isEmpty() {
        return head == nullptr;
    }

    ~stackL() {
        while (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class stackA {
    vector<string> stack;

public:
    void push(string value) {
        stack.push_back(value);
    }

    string pop() {
        if (stack.empty()) return "";
        string value = stack.back();
        stack.pop_back();
        return value;
    }

    string peek() {
        return stack.empty() ? "" : stack.back();
    }

    bool isEmpty() {
        return stack.empty();
    }
};

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int precedence(string op) {
    return precedence(op[0]);  // safe reuse
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infixToPostfix(string infix) {
    stackL s;
    string postfix;

    for (char token : infix) {
        if (isalnum(token)) {
            postfix += token;
        } else if (token == '(') {
            s.push("(");
        } else if (token == ')') {
            while (s.peek() != "(" && !s.isEmpty()) {
                postfix += s.pop();
            }
            s.pop();  // remove '('
        } else if (isOperator(token)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(token)) {
                if (token == '^' && s.peek() == "^") break;  // right-associative
                postfix += s.pop();
            }
            s.push(string(1, token));
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

int main() {
    stackA stack1;
    stackL stack2;

    stack1.push("TP01");
    stack1.push("TP02");
    stack1.push("TP03");
    stack1.pop();
    cout << "Array Stack Peek: " << stack1.peek() << endl;
    stack1.pop();
    stack1.push("TP04");
    stack1.push("TP05");
    stack1.push("TP03");
    stack1.pop();
    stack1.push("TP02");

    stack2.push("TP01");
    stack2.push("TP02");
    stack2.push("TP03");
    stack2.pop();
    cout << "Linked Stack Peek: " << stack2.peek() << endl;
    stack2.pop();
    stack2.push("TP04");
    stack2.push("TP05");
    stack2.push("TP03");
    stack2.pop();
    stack2.push("TP02");

    stackL parenthesisStack;
    string eq;
    cout << "\nEnter your equation here: ";
    getline(cin >> ws, eq);  // ws to clear leftover newline

    bool valid = true;
    for (char current : eq) {
        if (current == '(') parenthesisStack.push("(");
        else if (current == ')' && parenthesisStack.pop() != "(") { valid = false; break; }
        else if (current == '{') parenthesisStack.push("{");
        else if (current == '}' && parenthesisStack.pop() != "{") { valid = false; break; }
        else if (current == '[') parenthesisStack.push("[");
        else if (current == ']' && parenthesisStack.pop() != "[") { valid = false; break; }
    }

    if (!parenthesisStack.isEmpty()) valid = false;

    cout << (valid ? "The parenthesis of the equation is balanced and valid.\n"
                   : "The parenthesis of the equation is NOT balanced.\n");

    string infix;
    cout << "\nEnter infix expression (e.g., A+B*C): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    stackA characterStack;
    string seq;
    cout << "\nEnter a sequence of characters: ";
    cin >> seq;

    for (char element : seq) {
        characterStack.push(string(1, element));
    }

    cout << "Reversed: ";
    while (!characterStack.isEmpty()) {
        cout << characterStack.pop();
    }
    cout << endl;

}
