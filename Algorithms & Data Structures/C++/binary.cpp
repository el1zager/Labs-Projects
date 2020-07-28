//
// Created by macbookbro on 21/03/2020.
//

#include "binary.h"
using namespace std;
#include <iostream>
#include <vector>
#include <cmath>


Binary::Binary(int decimal) {
    if (decimal > 0) {
        if (decimal >= pow(2, this->size - 1)){
            throw invalid_argument("Invalid input: the number is too big");
        }
    } else {
        if (decimal < -pow(2, this->size - 1)){
            throw invalid_argument("Invalid input: the number is too small");
        }
    }

    int dividend; //делимое
    if (decimal < 0) {
        dividend = -decimal;
    } else {
        dividend = decimal;
    }

    if (dividend == 0){
        binary.push_back(0);
    } else {
        if (dividend == 1){
            binary.push_back(1);
        } else {
            int quotient = 0; //частное
            int remainder = 0; //остаток от деления
            while (quotient != 1) {
                quotient = dividend / 2;
                remainder = dividend - quotient * 2;
                binary.push_back(remainder);
                dividend = quotient;
            }
            binary.push_back(1);
        }
        if (decimal > 0) {
            binary.push_back(0);
        } else {
            binary.push_back(1);
        }
        reverse(begin(binary), end(binary));
        this->to_complement();
        this->decimal_ = this->to_decimal();
    }
    for (int i = 0; i < this->binary.size(); i++){
        bin += to_string(this->binary[i]);
    }
}


Binary::~Binary() {
    binary.clear();
}


void Binary::to_complement() {
    if (binary[0] == 0){
        for (int i = 0; i < (this->size + 1) - binary.size(); i++){
            complement.push_back(0);
        }
        for (int i = 1; i < binary.size(); i++) {
            complement.push_back(binary[i]);
        }
    } else {
        for (int i = 0; i < (this->size + 1) - binary.size(); i++){
            complement.push_back(1);
        }
        for (int i = 1; i < binary.size(); i++) {
            if (binary[i] == 0) {
                complement.push_back(1);
            } else {
                complement.push_back(0);
            }
        }
        this->complement = this->sum_comp(1);
    }
}


vector<int> Binary::sum_comp(int number) {
    if (number == 0) {
        return this->complement;
    } else {
        int summary;
        int add = 0;
        vector<int> result;
        Binary *addend = new Binary(number);
        for (int i = this->size - 1; i >= 0; i--) {
            summary = this->complement[i] + addend->complement[i] + add;
            switch (summary) {
                case 0:
                    result.push_back(0);
                    add = 0;
                    break;
                case 1:
                    result.push_back(1);
                    add = 0;
                    break;
                case 2:
                    result.push_back(0);
                    add = 1;
                    break;
                case 3:
                    result.push_back(1);
                    add = 1;
                    break;
            }
        }
        reverse(begin(result), end(result));
        if (this->complement[0] == 1 && addend->complement[0] == 1){
            if (result[0] == 0) {
                throw invalid_argument("Invalid input: OVERFLOW");
            }
        }
        if (this->complement[0] == 0 && addend->complement[0] == 0){
            if (result[0] == 1) {
                throw invalid_argument("Invalid input: OVERFLOW");
            }
        }
        return result;
    }
}


void Binary::print_sum(int arg) {
    vector<int> sum = this->sum_comp(arg);
    for (int i : sum) cout << i;
}


int Binary::sum_dec(int number) {
    this->complement = this->sum_comp(number);
    if (number == 0){
        return this->decimal_;
    }
    int a = this->binary[0];
    int b = this->to_decimal();
    if ((a==1 && number < 0)||(a==1 && number > 0 && fabs(b) > fabs(number))||(a==0 && number < 0 && fabs(b) < fabs(number))){
        vector<int> tmp;
        tmp.push_back(1);
        for (int i = 1; i < this->size; i++){
            tmp.push_back(1-this->complement[i]);
        }
        this->complement = tmp;
        this->complement = this->sum_comp(1);
        if (this->complement[0] == 0) {
            return -128;
        }
    }

    int dec = 0;
    for (int i = this->size - 1; i > 0; i--) {
        if (this->complement[i] == 1){
            dec += pow(2, this->complement.size() - i - 1);
        }
    }
    if (this->complement[0] == 1) {
        dec = -dec;
    }
    return dec;
}


void Binary::print_sub(int arg) {
    if (arg == 0){
        this->print_comp();
    } else {
        this->print_sum(-arg);
    }
}


int Binary::sub_dec(int number) {
    if (number == 0){
        return this->to_decimal();
    } else {
        return this->sum_dec(-number);
    }
}


void Binary::print_bin() {
    if (binary.size() == 1){
        cout << "0" << endl;
    } else {
        cout << binary[0] << ".";
        for (int i = 1; i < binary.size(); i++) {
            cout << binary[i];
        }
    }
}


void Binary::print_comp() {
    if (binary.size() == 1){
        cout << "0" << endl;
    } else {
        cout << endl;
        for (int i : complement) cout << i;
    }
}


int Binary::multiply(int number) {
    if (number == 0 || this->decimal_ == 0) {
        return 0;
    } else {
        int result = this->decimal_;
        for (int i = 1; i <= fabs(number)-1; i++) {
            Binary* tmp = new Binary(result);
            result = tmp->sum_dec(this->decimal_);
        }
        if (number < 0){
            Binary* bin = new Binary(-result);
            bin->print_comp();
            cout << "\n";
            return -result;
        }
        Binary* bin = new Binary(result);
        bin->print_comp();
        cout << "\n";
        return result;
    }
}


int Binary::div(int number) {
    if (number == 0){
        throw invalid_argument("Invalid input: division by zero");
    }
    int result = 0;
    int tmp = fabs(this->to_decimal());
    while (tmp >= fabs(number)){
        result++;
        Binary* bin = new Binary(tmp);
        tmp = bin->sub_dec(fabs(number));
    }
    if ((this->to_decimal() < 0 && number > 0)||(this->to_decimal() > 0 && number < 0)){
        Binary* bin2 = new Binary(-result);
        bin2->print_comp();
        cout << "\n";
        return -result;
    } else {
        Binary* bin2 = new Binary(result);
        bin2->print_comp();
        cout << "\n";
        return result;
    }
}


int Binary::to_decimal() {
    int dec = 0;
    for (int i = this->binary.size(); i > 0; i--){
        if (this->binary[i] == 1){
            dec += pow(2, this->binary.size()-i-1);
        }
    }
    if (this->binary[0] == 1) {
        dec = -dec;
    }
    return dec;
}


bool operator == (const Binary& left, const Binary& right)
{
    return left.binary == right.binary;
}


bool operator != (const Binary& left, const Binary& right) {
    return !(left == right);
}


ostream& operator << (ostream& os, const Binary& at) {
    os << at.bin;
    return os;
}


int get_value()
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


void interface() {
    cout << "Welcome to Liza's binary class!" << endl;
    cout << "What number do you want to convert?" << endl;
    int number = get_value();
    cout << "What number do you want to perform AO with?" << endl;
    int argument = get_value();

    try{
        auto* bin = new Binary(number);
    }
    catch(invalid_argument& a){
        cout << a.what() << endl;
    }
    auto* bin = new Binary(number);

    cout << "\nWell, the number is:\n";
    bin->print_bin();
    bin->print_comp();

    cout << "\n\nsummation\n";
    bin->print_sum(argument);
    cout << "\n";
    auto* binaryy = new Binary(number);
    cout << binaryy->sum_dec(argument);
    cout << "\n";

    cout << "\nsub\n";
    auto* bin4 = new Binary(number);
    bin4->print_sub(argument);
    cout << "\n";
    auto* bin3 = new Binary(number);
    cout << bin3->sub_dec(argument);
    cout << "\n";

    cout << "\nmultiply";
    auto* bin5 = new Binary(number);
    cout << bin5->multiply(argument);
    cout << "\n";

    cout << "\ndivision";
    try{
        cout << bin5->div(argument);
    }
    catch(invalid_argument& a){
        cout << a.what() << endl;
    }
    //cout << bin5->div(argument);
}


int main() {
    try{
        interface();
    }
    catch(invalid_argument& a){
        cout << a.what() << endl;
    }
    return 0;
}
