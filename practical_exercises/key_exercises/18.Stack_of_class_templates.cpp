#include <iostream>

using namespace std;

template <typename T, int MAXSIZE>

class Stack {
public:
    Stack() {}

    void init() { top = -1; }

    bool isFull() {
        if (top >= MAXSIZE - 1)
            return true;
        else
            return false;
    }

    bool isEmpty() {
        if (top == -1)
            return true;
        else
            return false;
    }

    void push(T e);

    T pop();

private:
    T elems[MAXSIZE];
    int top;
};

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T e) {
    if (!isFull()) {
        elems[++top] = e;
    } else {
        cout << "The stack is full, please do not add any more elements!";
        return;
    }
}

template <typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::pop() {
    if (!isEmpty()) {
        return elems[top--];
    } else {
        cout << "The stack is empty, please don't pop any more elements!";
        return 0;
    }
}

int main(int argc, char const *argv[]) {
    Stack<int, 10> s1;
    s1.init();
    int i;
    for (i = 1; i < 11; i++) s1.push(i);
    for (i = 1; i < 11; i++) cout << s1.pop() << "\t";
    cout << endl;
    system("pause");
    return 0;
}
