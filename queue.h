#pragma once

#include <stdexcept>

template<typename T>
class Queue {
private:
    struct Node {
        T val;
        Node* next;
        Node(T data) : val(data), next(nullptr) {}
    };
    Node *first, *last;
    int size;
public:
    Queue();
    Queue(T data);
    ~Queue();
    bool isEmpty();
    void enqueue(T data);
    void dequeue();
    T front();
    T back();
};
#include "queue.h"
#include <stdexcept>

template<typename T>
Queue<T>::Queue() : first(nullptr), last(nullptr), size(0) {}

template<typename T>
Queue<T>::Queue(T data) : first(new Node(data)), last(first), size(1) {}

template<typename T>
Queue<T>::~Queue() {
    while (first) {
        Node* tmp = first;
        first = first->next;
        delete tmp;
    }
    last = nullptr;
    size = 0;
}

template<typename T>
bool Queue<T>::isEmpty() {
    return size == 0;
}

template<typename T>
void Queue<T>::enqueue(T data) {
    Node* temp = new Node(data);
    if (last) last->next = temp;
    else first = temp;
    last = temp;
    ++size;
}

template<typename T>
void Queue<T>::dequeue() {
    if (!first) return;
    Node* tmp = first;
    first = first->next;
    delete tmp;
    --size;
    if (!first) last = nullptr;
}

template<typename T>
T Queue<T>::front() {
    if (!first) throw std::runtime_error("Queue is empty");
    return first->val;
}

template<typename T>
T Queue<T>::back() {
    if (!last) throw std::runtime_error("Queue is empty");
    return last->val;
}
