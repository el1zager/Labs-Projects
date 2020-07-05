#include <iostream>
#include "myList.h"
#include "binary.h"

using namespace std;

template<typename T>
List<T>::List(int size) {
    if (size > 0) {
        this->size = size;
        this->head = nullptr;
    }
    else
    {
        size = 0;
    }
}

template<typename T>
List<T>::~List()
{
    if (this->head == nullptr) {
        cout << "The list is already empty" << endl;
    }
    else
    {
        while (this->head != nullptr)
        {
            Node<T>* temp = this->head;
            head = head->pointerNext;
            delete temp;
        }
    }
}

template<typename T>
int List<T>::getSize()
{
    return size;
}

template<typename T>
int List<T>::getQuantity()
{
    int counter = 0;
    Node<T>* count = this->head;

    if (count != nullptr)
    {
        while (count->pointerNext != nullptr)
        {
            counter++;
            count = count->pointerNext;
        }
        counter++;
    }
    return counter;
}

template<typename T>
void List<T>::push_back(T data)
{
    int counter = getQuantity();

    if (counter >= getSize())
    {
        throw out_of_range("Error, the list is filled or the size is 0");
    }
    else
    {
        if (head == nullptr)
        {
            head = new Node<T>(data);
        }
        else
        {
            Node<T>* temp = this->head;
            while (temp->pointerNext != nullptr)
            {
                temp = temp->pointerNext;
            }
            temp->pointerNext = new Node<T>(data);
        }
    }
}

template<typename T>
void List<T>::print()
{
    if (this->head == nullptr) {
        cout << "The list is empty" << endl;
    }
    else
    {
        Node<T>* temp = this->head;
        while (temp->pointerNext != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->pointerNext;
        }
        cout << temp->data << endl;
    }
}

template<typename T>
void List<T>::raiseSize(int num)
{
    size = size + num;
}

template<typename T>
void List<T>::deleteElem(T value)
{
    if (this->head == nullptr) {
        cout << "The list is empty" << endl;
    }
    else
    {
        while (head->data == value)
        {
            Node<T>* temp = this->head;
            head = head->pointerNext;
            delete temp;
        }
        Node<T>* temp = this->head;
        while (temp->pointerNext != nullptr)
        {
            if (temp->pointerNext->data == value)
            {
                Node<T>* tempNew = temp->pointerNext;
                temp->pointerNext = temp->pointerNext->pointerNext;
                delete tempNew;
            }
            else
            {
                temp = temp->pointerNext;
            }
        }
    }
}

template<typename T>
bool List<T>::findElem(T value)
{
    if (this->head == nullptr) {
        cout << "The list is empty" << endl;
        return false;
    }
    else
    {
        Node<T>* temp = this->head;
        while (temp->pointerNext != nullptr)
        {
            if (temp->data == value)
            {
                return true;
            }
            temp = temp->pointerNext;
        }
        if (temp->data == value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

char getCommand()
{
    while (true)
    {
        cout << "Enter one of the following: 1 or 2\n";
        char sm;
        cin >> sm;
        if (sm == '1' || sm == '2')
            return sm;
        else
            cout << "Oops, that input is invalid. Please try again.\n";
    }
}

int getValue()
{
    while (true)
    {
        std::cout << "Enter an int value: ";
        int a;
        std::cin >> a;
        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
        else
            return a;
    }
}

template<typename T>
void List<T>::myInterface()
{
    cout << "Super! What are you going to do next?\n" << endl;
    cout << "1. Add an element to a list\n" << endl;
    cout << "2. Delete an element\n" << endl;
    cout << "3. Raise a size of a list\n" << endl;
    cout << "4. Find an element\n" << endl;
    cout << "5. Print a list\n" << endl;
    cout << "6. Delete a list\n\n" << endl;

    int command;
    cin >> command;

    if (command == 1)
    {
        cout << "What data are you going to push?\n" << endl;
        int value = getValue();
        try {
            this->push_back(value);
        }
        catch (out_of_range a) {
            cout << a.what() << endl;
        }
        this->myInterface();
    }
    if (command == 2)
    {
        cout << "What data are you going to delete?\n" << endl;
        int value = getValue();
        this->deleteElem(value);
        this->myInterface();
    }
    if (command == 3)
    {
        cout << "How many positions do you want to increase the list by?\n" << endl;
        int numb = getValue();
        this->raiseSize(numb);
        this->myInterface();
    }
    if (command == 4)
    {
        cout << "What data are you going to find?\n" << endl;
        int value = getValue();
        if (this->findElem(value))
        {
            cout << "Yes, there is such an element\n" << endl;
        }
        else
        {
            cout << "No, there is no such an element\n" << endl;
        }
        this->myInterface();
    }
    if (command == 5)
    {
        this->print();
        this->myInterface();
    }
    if (command == 6)
    {
        this->~List();
    }
}


int main()
{
    cout << "Welcome to my List world!\n" << endl;
    cout << "Let's create a list!\n" << endl;
    cout << "Do you want to specify the size?\n" << endl;
    cout << "1. Yes\n" << endl;
    cout << "2. No\n" << endl;

    if (getCommand() == '1')
    {
        cout << "What size?\n" << endl;
        List<Binary>* list = new List<Binary>(getValue());
        list->myInterface();
    }
    else
    {
        List<Binary>* list = new List<Binary>(0);
        list->myInterface();
    }
}
