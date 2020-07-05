//
// Created by macbookbro on 21/03/2020.
//

#ifndef BINARY_BINARY_H
#define BINARY_BINARY_H
using namespace std;
#include <vector>
#include <string>

class Binary {
public:
    Binary(int);
    ~Binary();

    void to_complement();
    void print_bin();
    void print_comp();
    vector <int> sum_comp(int number);
    void print_sum(int arg);
    int sum_dec(int number);
    int sub_dec(int number);
    void print_sub(int arg);
    int multiply(int number);
    int div(int number);
    int to_decimal();
    friend bool operator == (const Binary& left, const Binary& right);
    friend bool operator != (const Binary& left, const Binary& right);
    friend ostream& operator << (ostream& os, const Binary& at);

private:
    string bin;
    int size = 8;
    int decimal_;
    vector<int> binary;
    vector<int> complement;
};

#endif //BINARY_BINARY_H