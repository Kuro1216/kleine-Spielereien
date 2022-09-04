#include <string>
#include "digraph.h"

#ifndef QUEUE_HEADER
#define QUEUE_HEADER


template <typename T>
class pQueueEntry {
private:
    T value; //Muss zu Node* werden.
    float priority;
    pQueueEntry *next;
    pQueueEntry *previous;
public:
    pQueueEntry(T value, float);
    pQueueEntry *getNext();
    pQueueEntry *getPrevious();
    void setNext(pQueueEntry*);
    void setPrevious(pQueueEntry*);
    T getValue();
    float getPriority();
};



template <typename T>
class pQueue {
private:
    int size;
    pQueueEntry<T> *begin;
    pQueueEntry<T>  *end;
public:
    pQueue();
    ~pQueue();
    void insert(T value, float);
    T  extractMin();
    void decreaseKey(T value, float);
    bool remove(T value);
    bool isEmpty();
};

#include <stdlib.h>
#include <string>
#include <iostream>
#include "priorityQueue.h"


template <typename T>
pQueue<T>::pQueue() {
    size = 0;
    begin = NULL;
    end = NULL;
}

template <typename T>
pQueue<T>::~pQueue(){
    while (begin != NULL) {
        extractMin();
    }
}
template <typename T>
void pQueue<T>::insert(T value, float pPrio) {
    pQueueEntry<T> *tempNode = new pQueueEntry<T>(value, pPrio);
    tempNode->setNext(NULL);
    tempNode->setPrevious(NULL);

    if(end == NULL) {
        begin = tempNode;
        end = tempNode;
        size = 1;

        return;
    }

    pQueueEntry<T> *currentNode = begin;
    for(int i = 0; i < size; i++) {
        if(tempNode->getPriority() < currentNode->getPriority()) {
            if(currentNode->getPrevious() == NULL) {
                currentNode->setPrevious(tempNode);
                tempNode->setNext(currentNode);
                begin = tempNode;
                size++;
                //printf("Inserted at position 1 \n");
                return;
            }
            tempNode->setPrevious(currentNode->getPrevious());
            currentNode->setPrevious(tempNode);
            tempNode->getPrevious()->setNext(tempNode);
            tempNode->setNext(currentNode);
            size++;

            return;
        }
        if(currentNode->getNext() == NULL) {
            currentNode->setNext(tempNode);
            tempNode->setPrevious(currentNode);
            size++;
            end = tempNode;
            //printf("Inserted at end\n");
            return;
        }
        currentNode = currentNode->getNext();
    }
}

template <typename T>
T pQueue<T>::extractMin() {
    if(begin == NULL) {
        std::cout << "pQueue empty" << std::endl;
        return NULL;
    }
    Node* value = begin->getValue();
    pQueueEntry<T> *newBegin = begin->getNext();
    delete begin;
    if(newBegin == NULL) {
        size = 0;
        begin = NULL;
        end = NULL;
        return value;
    }
    size--;
    newBegin->setPrevious(NULL);
    begin = newBegin;
    return value;
}

template <typename T>
void pQueue<T>::decreaseKey(T value, float pPrio) {
    if(remove(value)){
        insert(value, pPrio);
    }
}

template <typename T>
bool pQueue<T>::remove(T value) {
    pQueueEntry<T> *currentEntry = begin;

    for(int i = 0; i < size; i++) {
        if(value == currentEntry->getValue()) {
            if(currentEntry->getPrevious() == NULL && currentEntry->getNext ()== NULL) {
                begin = NULL;
                end = NULL;
            } else if(currentEntry->getPrevious() == NULL) {
                begin = currentEntry->getNext();
                currentEntry->getNext()->setPrevious(NULL);
            } else if(currentEntry->getNext() == NULL) {
                end = currentEntry->getPrevious();
                currentEntry->getPrevious()->setNext(NULL);
            } else {
                currentEntry->getPrevious()->setNext(currentEntry->getNext());
                currentEntry->getNext()->setPrevious(currentEntry->getPrevious());
            }
            delete(currentEntry);
            size--;
            return true;
        }
        currentEntry = currentEntry->getNext();
    }
    std::cout << "Wert " << value << " konnte nicht gefunden werden" << std::endl;
    return false;
}

template <typename T>
bool pQueue<T>::isEmpty() {
    if(size == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
pQueueEntry<T>::pQueueEntry(T values, float pPrio) {
    value = values;
    priority = pPrio;
    next = NULL;
    previous = NULL;
}

template <typename T>
pQueueEntry<T> *pQueueEntry<T>::getNext() {
    return next;
}

template <typename T>
pQueueEntry<T> *pQueueEntry<T>::getPrevious() {
    return previous;
}

template <typename T>
void pQueueEntry<T>::setNext(pQueueEntry *nextNode) {
    next = nextNode;
}

template <typename T>
void pQueueEntry<T>::setPrevious(pQueueEntry *previousNode) {
    previous = previousNode;
}

template <typename T>
T pQueueEntry<T>::getValue() {
    return value;
}

template <typename T>
float pQueueEntry<T>::getPriority() {
    return priority;
}



#endif
