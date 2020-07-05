//
// Created by macbookbro on 08/04/2020.
//

#ifndef BINARY_MYTREE_H
#define BINARY_MYTREE_H

using namespace std;
#include <iostream>
#include <vector>


class MyTree {
public:
    class Node {
    public:
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr):
        value(value), parent(parent), left(left), right(right) {}
    };

    MyTree (const vector<int>& values);
    ~MyTree();
    void print();
    void insert(int value);
    static void fixUp(Node* current);
    static Node* find(int value, Node* current);
    bool contains(int value);
    void del(int value);
    void delNode(Node* need);
    static void fixDown(Node* current);

private:
    Node* head = nullptr;
    Node* last = nullptr;
};

#endif //BINARY_MYTREE_H
