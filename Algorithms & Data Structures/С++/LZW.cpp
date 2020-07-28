//
// Created by macbookbro on 08/06/2020.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

vector<int16_t> encoding(vector<char> file) {
    unordered_map<string, int16_t> table;

    for (unsigned int i = 0; i <= 255; i++) {
        string ch;
        ch += char(i);
        table[ch] = i;
    }

    string p, c;
    p += file[0];
    unsigned int code = 256;
    vector<int16_t> output_code;

    for (unsigned int i = 0; i < file.size(); i++) {
        if (i != file.size() - 1)
            c += file[i + 1];
        if (table.find(p + c) != table.end()) {
            p += c;
        } else {
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    output_code.push_back(table[p]);
    return output_code;
}

vector<string> decoding(vector<int16_t> old_file) {

    unordered_map<int16_t, string> table;

    for (int16_t i = 0; i < 256; i++) {
        string ch;
        ch += char(i);
        table[i] = ch;
    }

    vector<string> file;
    int16_t current_code = old_file[0], next_code;

    string current_symbol = table[current_code];
    string c;

    c += current_symbol[0];

    file.push_back(current_symbol);

    int16_t table_iter = 256;

    for (int16_t i = 0; i < old_file.size() - 1; i++) {
        next_code = old_file[i + 1];
        if (table.find(next_code) == table.end()) {
            current_symbol = table[current_code];
            current_symbol += c;
        } else {
            current_symbol = table[next_code];
        }
        file.push_back(current_symbol);
        c = "";
        c += current_symbol[0];
        table[table_iter] = table[current_code] + c;
        table_iter++;
        current_code = next_code;
    }
    return file;
}


int main() {
    vector<char> char_vector;
    vector<string> string_vector;
    ifstream fin;
    char ch;
    unsigned int index;
    vector<int16_t> bin_vector;
    fstream file;
    ofstream dec;
    ifstream read;
    int com;
    string file_name;
    ofstream ofs;

    cout << "Welcome! What are we going to do?" << endl;
    cout << "1. encode" << endl;
    cout << "2. decode" << endl;
    cout << "3. exit" << endl;
    cin >> com;

    switch (com) {
        case 1:
            cout << "Enter file name" << endl;
            cin >> file_name;
            fin.open(file_name, ios::binary);
            if (fin.is_open()) {
                while (fin.get(ch)) {
                    char_vector.push_back(ch);
                }
                fin.close();

                bin_vector = encoding(char_vector);
                cout << "Enter file name" << endl;
                cin >> file_name;
                ofs.open(file_name, ios::binary);

                for (short & i : bin_vector) {
                    ofs.write((char*)&i, sizeof(int16_t));
                }
                bin_vector.clear();
                char_vector.clear();
                ofs.close();
            } else cout << "Error with file opening";
            break;

        case 2:
            cout << "Enter file name" << endl;
            cin >> file_name;
            fin.open(file_name, ios::binary);
            if (fin) {
                index = 0;
                while (!fin.eof()) {
                    if (!fin.eof()) {
                        bin_vector.push_back(0);
                        fin.read((char *) &bin_vector[index], sizeof(int16_t));
                        index++;
                    }
                }
                fin.close();

                string_vector = decoding(bin_vector);
                cout << "Enter file name" << endl;
                cin >> file_name;
                ofs.open(file_name, ios::binary);
                for (unsigned int i = 0; i < string_vector.size()-1; i++) {
                    ofs.write(string_vector[i].c_str(), string_vector[i].length());
                }
                ofs.close();

                bin_vector.clear();
                string_vector.clear();
            } else
                cout << "\n Can't open file\n";
            break;

        default:
            exit(1);
    }
}
