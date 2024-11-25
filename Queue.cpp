#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue() {
    front = -1;
    rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front){
        return;
    }

    rear = (rear + 1) % MAX_QUEUE_SIZE;

    if (front == -1){
        front = 0;
    }

    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    if (isEmpty()){
        return -1;
    }

    int temp = data[front];

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX_QUEUE_SIZE;
    }

    return temp;
}

// Returns the front province without removing it
int Queue::peek() const {
    if (isEmpty()) {
        return -1;
    }
    return data[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    return (front == -1 && rear == -1);
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    // put it in the front by pushing other elements to the back or decreamenting the front index
    // if we stay true to FIFO, we cannot do this by decreamenting the front index because then the priority part of the queue will become a stack
    // but the priority list doesn't have a priority order, so it should be fine to do it by decreamenting the front index

    // Check if the queue is full
    if ((front == 0 && rear == MAX_QUEUE_SIZE - 1) || (front - 1 == rear)) {
        return; // Queue is full
    }

    // Move the front pointer backward in a circular manner
    if (front == 0) {
        front = MAX_QUEUE_SIZE - 1; // Wrap around to the end of the queue
    } else {
        front--; // Decrement front normally
    }

    // Insert the priority province at the new front position
    data[front] = province;
}

