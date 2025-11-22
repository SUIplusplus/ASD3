#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* top;
    int size;
public:
    Stack();
    ~Stack();
    void clear();
    bool isEmpty();
    int getSize();
    void push(T value);
    void changeValue(int index, T value);
    T pop(int index = 0);
    T peek(int index = 0);
};

template<typename T>
Stack<T>::Stack() : top(nullptr), size(0) {}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
void Stack<T>::clear() {
    while (top) {
        typename Stack<T>::Node* temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}

template<typename T>
bool Stack<T>::isEmpty() {
    return size == 0;
}

template<typename T>
int Stack<T>::getSize() {
    return size;
}

template<typename T>
void Stack<T>::push(T value) {
    typename Stack<T>::Node* newNode = new typename Stack<T>::Node(value);
    newNode->next = top;
    top = newNode;
    ++size;
}

template<typename T>
T Stack<T>::pop(int index) {
    if (size == 0) {
        throw runtime_error("Stack is empty.");
    } 
    if (index < 0 || index >= size) {
        throw runtime_error("Index out of range.");
    }
    T value;
    if (index == 0) {
       typename Stack<T>::Node* temp = top;
        value = temp->data;
        top = top->next;
        delete temp;
        size--;
        return value;
    }
    typename Stack<T>::Node* curr = top;
    typename Stack<T>::Node* prev = nullptr;
    for (int i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    value = curr->data;
    prev->next = curr->next;
    delete curr;
    size--;
    return value;
}

template<typename T>
T Stack<T>::peek(int index) {
    if (size == 0) {
        throw runtime_error("Stack is empty.");
    }if (index < 0 || index >= size) {
        throw runtime_error("Index out of range.");
    }
    typename Stack<T>::Node* curr = top;
    for (int i = 0; i < index; ++i) curr = curr->next;
    return curr->data;
}

template<typename T>
void Stack<T>::changeValue(int index, T value) {
    if (index < 0 || index >= size) {
        throw runtime_error("Index out of range.");
    }
    typename Stack<T>::Node* curr = top;
    for (int i = 0; i < index; ++i) curr = curr->next;
    curr->data = value;
}