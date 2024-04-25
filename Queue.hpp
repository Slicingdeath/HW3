#pragma once

template <typename T>
class Queue {
    protected:
        // the current number of elements in the queue
        int length;

    public:
        // default constructor
        Queue() : length(0) { }

        // destructor
        virtual ~Queue() { }

        // return the element at the back of the queue
        virtual T back() const = 0;

        // remove all elements in the queue, resetting to the initial state
        virtual void clear() = 0;

        // remove the front element from the queue
        virtual void dequeue() = 0;

        // add the argument to the back of the queue
        virtual void enqueue(const T&) = 0;

        // return the element at the front of the queue
        virtual T front() const = 0;

        // return the current length of the queue
        virtual int getLength() const = 0;

        // determine if the queue is currently empty
        virtual bool isEmpty() const = 0;
};
