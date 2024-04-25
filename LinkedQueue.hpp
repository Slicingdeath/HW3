#pragma once

#include "Queue.hpp"
#include <iostream>

template <typename T>
class LinkedQueue : public Queue<T> {
    protected:
        // represents an element in the queue
        struct Node {
            T value;
            Node* next;

            Node(T v = T(), Node* n = nullptr)
            : value(v), next(n) { }
        };

        // a pointer to the front (head) and back (last) of the queue
        Node *head, *last;

    private:
        // copy the state of the argument queue to `this`
        void copy(const LinkedQueue<T>&);

    public:
        // default constructor
        LinkedQueue();

        // copy constructor
        LinkedQueue(const LinkedQueue<T>&);

        // overloaded assignment operator
        LinkedQueue<T>& operator=(const LinkedQueue<T>&);

        // destructor
        virtual ~LinkedQueue();

        // return the element at the back of the queue
        virtual T back() const override;

        // remove all elements in the queue, resetting to the initial state
        virtual void clear() override;

        // remove the front element from the queue
        virtual void dequeue() override;

        // add the argument to the back of the queue
        virtual void enqueue(const T&) override;

        // return the element at the front of the queue
        virtual T front() const override;

        // return the current length of the queue
        virtual int getLength() const override;

        // determine if the queue currently empty
        virtual bool isEmpty() const override;
};

template <typename T>
LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    last = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
T LinkedQueue<T>::back() const {
    if (last == nullptr) {
        throw std::string("LinkedQueue::back error: queue is empty");
    }
    return last->value;
}

template <typename T>
void LinkedQueue<T>::clear() {
    while (!this->isEmpty()) {
        dequeue();
    }
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& copyObj) {
    for (Node *copy = copyObj.head; copy != nullptr; copy = copy->next) {
        enqueue(copy->value);
    }
}

template <typename T>
void LinkedQueue<T>::dequeue() {
    if (head == nullptr) {
        throw std::string("LinkedQueue::dequeue error: queue is empty");
    }
    Node *temp = head;
    head = head->next;
    delete temp;
    this->length--;
    if (this->length == 0) {
        last = nullptr;
    }
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem) {
    Node *n = new Node(elem);
    if (head == nullptr) {
        head = n;
        last = n;
    } else {
        last->next = n;
        last = last->next;
    }
    this->length++;
}

template <typename T>
T LinkedQueue<T>::front() const {
    if (head == nullptr) {
        throw std::string("LinkedQueue::front error: queue is empty");
    }
    return head->value;
}

template <typename T>
int LinkedQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return this->length == 0;
}

