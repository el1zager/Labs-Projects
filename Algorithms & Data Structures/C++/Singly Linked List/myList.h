//
// Created by macbookbro on 23/03/2020.
//

#ifndef BINARY_MYLIST_H
#define BINARY_MYLIST_H

#include "binary.h"

using namespace std;

template <typename T>
class List
{
public:

    List(int);
    ~List();

    int getQuantity();
    void push_back(T data);
    int getSize();
    void print();
    void raiseSize(int num);
    void deleteElem(T value);
    bool findElem(T value);
    void myInterface();

private:
    template <typename U>
    class Node
    {
    public:
        Node* pointerNext;
        U data;

        Node(U data, Node* next = 0): data(data), pointerNext(next) {}
    };

    int size;
    Node<T>* head;
};

#endif //BINARY_MYLIST_H


