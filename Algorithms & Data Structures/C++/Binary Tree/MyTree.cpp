//
// Created by macbookbro on 08/04/2020.
//

#include "MyTree.h"

using namespace std;
#define COUNT 10

#include <iostream>
#include <vector>


MyTree::MyTree(const vector<int>& values) {
    for (int value : values) {
        insert(value);
    }
    print();
}


MyTree::~MyTree() {
    head = nullptr;
    last = nullptr;
}


void MyTree::insert(int value) {
    if (head == nullptr) {
        head = new Node(value);
        return;
    }
    if (head->left == nullptr) {
        Node *newNode = new Node(value, head);
        last = newNode;
        head->left = last;
        fixUp(last);
        return;
    }
    if (last->parent->right == nullptr) {
        Node *newNode = new Node(value, last->parent);
        last->parent->right = newNode;
        last = newNode;
        fixUp(last);
        return;
    }
    Node *current = last->parent;
    while (current->parent != nullptr) {
        if (current == current->parent->left) {
            current = current->parent->right;
            while (current->left != nullptr) {
                current = current->left;
            }
            Node *newNode = new Node(value, current);
            current->left = newNode;
            last = newNode;
            fixUp(last);
            return;
        }
        current = current->parent;
    }
    while (current->left != nullptr) {
        current = current->left;
    }
    Node *newNode = new Node(value, current);
    current->left = newNode;
    last = newNode;
    fixUp(last);
}


void MyTree::fixUp(Node *current) {
    while (current->parent != nullptr && current->value > current->parent->value) {
        Node *tmp = current->parent;

        int temp = current->value;
        current->value = current->parent->value;
        current->parent->value = temp;

        current = tmp;
    }
}


MyTree::Node *MyTree::find(int value, Node *current) {
    if (current != nullptr && current->value == value) {
        return current;
    }
    if (current == nullptr) {
        return nullptr;
    }
    Node *tmp = find(value, current->right);
    if (tmp != nullptr) {
        return tmp;
    }
    return find(value, current->left);
}


bool MyTree::contains(int value) {
    Node *tmp = find(value, head);
    return tmp != nullptr;
}


void MyTree::del(int value) {
    if (head == nullptr) {
        cout << "is empty" << endl;
    }
    Node *need = find(value, head);
    while (need != nullptr) {
        delNode(need);
        if (last == nullptr) {
            break;
        }
        if (last->parent != nullptr) {
            fixUp(need);
            fixDown(need);
        }
        need = find(value, head);
    }
}


void MyTree::delNode(Node *need) {
    if (need == nullptr) {
        return;
    }
    need->value = last->value;
    if (last == head) {
        head = nullptr;
        last = nullptr;
        return;
    }
    if (last->parent->right != nullptr) {
        last = last->parent->left;
        last->parent->right = nullptr;
        return;
    }
    last->parent->left = nullptr;
    while (last->parent != nullptr) {
        if (last == last->parent->right) {
            last = last->parent->left;
            while (last->left != nullptr) {
                last = last->right;
            }
            return;
        }
        last = last->parent;
    }
    last = head;
    while (last->right != nullptr) {
        last = last->right;
    }
}


void MyTree::fixDown(Node *current) {
    while (current && current->left) {
        Node *max = current->left;
        if (current->right != nullptr) {
            if (current->right->value > max->value) {
                max = current->right;
            }
        }
        Node *tmp = max;
        if (current->value > max->value) {
            break;
        }
        int temp = current->value;
        current->value = max->value;
        max->value = temp;

        current = tmp;
    }
}


// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(MyTree::Node *root, int space) {
    // Base case
    if (root == NULL)
        return;
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print2DUtil(root->right, space);
    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->value << "\n";
    // Process left child
    print2DUtil(root->left, space);
}


// Wrapper over print2DUtil()
void MyTree::print() {
    Node *root = head;
    print2DUtil(root, 0);
}


void interface(MyTree* tree) {
    cout << "What are you going to do next?" << endl;
    cout << "1. insert an element" << endl;
    cout << "2. delete the element" << endl;
    cout << "3. find the element" << endl;
    cout << "4. print the tree" << endl;
    cout << "5. delete the tree" << endl;
    int com;
    int val;
    cin >> com;
    if (com == 1) {
        cout << "Value?" << endl;
        cin >> val;
        tree->insert(val);
        interface(tree);
    }
    if (com == 2) {
        cout << "Value?" << endl;
        cin >> val;
        tree->del(val);
        interface(tree);
    }
    if (com == 3) {
        cout << "Value?" << endl;
        cin >> val;
        if (tree->contains(val)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
        interface(tree);
    }
    if (com == 4) {
        tree->print();
        interface(tree);
    }
    if (com == 5) {
        tree->~MyTree();
    }
}


int main() {
    cout << "Welcome to Tree class!" << endl;
    cout << "Enter some values" << endl;
    vector<int> values;
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        values.push_back(n);
    }
    auto *tree = new MyTree(values);
    interface(tree);
}
