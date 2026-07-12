//
// Created by meepe on 7/9/2026.
//
#include "functions.h"

#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

void loadData(const string &fileName, vector<Order>& buffer) {

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> tokens;
        while (ss >> value) {
            tokens.push_back(value);
        }
        for (size_t i = 0; i < 40; i+=4) {
            if (i + 3 < tokens.size()) {
                double sPrice = stod(tokens[i]);
                int sVolume = stoi(tokens[i+1]);
                if (sVolume > 0 && sPrice > 0) {
                    buffer.push_back(Order{'S', sVolume, sPrice});
                }
                double bPrice = stod(tokens[i+2]);
                int bVolume = stoi(tokens[i+3]);
                if (bVolume > 0 && bPrice > 0) {
                    buffer.push_back(Order{'B', bVolume, bPrice});
                }
            }
        }
    }
    file.close();
    cout << "yall good: " << buffer.size() << endl;
}
void shiftDownMAX(vector<Order>& input, int n, int i) {
    int biggest = i;
    int left = (i * 2) + 1;
    int right = (i * 2) + 2;
    if (left < n && input[left].cost >input[biggest].cost) {
        biggest = left;
    }
    if (right < n && input[right].cost > input[biggest].cost) {
        biggest = right;
    }
    if (biggest != i) {
        swap(input[i], input[biggest]);
        shiftDownMAX(input, n, biggest);
    }
}
void shiftDownMIN(vector<Order>& input, int n, int i) {
    int smallest = i;
    int left = (i * 2) + 1;
    int right = (i * 2) + 2;
    if (left < n && input[left].cost < input[smallest].cost) {
        smallest = left;
    }
    if (right < n && input[right].cost < input[smallest].cost) {
        smallest = right;
    }
    if (smallest != i) {
        swap(input[i], input[smallest]);
        shiftDownMIN(input, n, smallest);
    }
}

bool isMax(const vector<Order>& input) {
   int n = input.size();
    for(int i = 0; i < n; i++) {
        int left = i * 2 + 1;
int right = (i * 2) + 2;
    if(left < n && input[left].cost > input[i].cost) {
return false;}
if(right < n && input[right].cost > input[i].cost) {
return false;}
}
return true;
}
bool isMin(const vector<Order>& input) {
    int n = input.size();
    for(int i = 0; i < n; i++) {
        int left = i * 2 + 1;
        int right = (i * 2) + 2;
        if(left < n && input[left].cost < input[i].cost) {
            return false;}
        if(right < n && input[right].cost < input[i].cost) {
            return false;}
    }
    return true;
}
void makeMaxHeap(vector<Order>& input) {
    int n = input.size();
    for (int i = (n / 2) -1; i >= 0; i--) {
        shiftDownMAX(input, n, i);
    }
    if(isMax(input)) {
//cout<<"yippie its maxed"<<endl;
}
}
void makeMinHeap(vector<Order>& input) {
    int n = input.size();
    for (int i = (n / 2) -1; i >= 0; i--) {
        shiftDownMIN(input, n, i);
    }
    if(isMin(input)) {
        //cout<<"yippie its min"<<endl;
        }
}
void popMax(vector<Order>& input) {
    input[0] = input.back();
    input.pop_back();
    shiftDownMAX(input, input.size(), 0);
}
void popMin(vector<Order>& input) {
    input[0] = input.back();
    input.pop_back();
    shiftDownMIN(input, input.size(), 0);
}
void compare(vector<Order>& Buy, vector<Order>& Sell) {

    while ( !Sell.empty() && !Buy.empty() && Buy[0].cost >= Sell[0].cost) {

        cout<< "Trade Completed | Price: "<< Sell[0].cost << " | Volume: " <<  Sell[0].amount<<endl;
        popMax(Buy);
        popMin(Sell);
    }
}
//push , pop are needed
Performance executeHash(const vector<Order>& input) {
    size_t initial = sizeof(HashTable);
    size_t dynamic = 0;
    auto start = chrono::high_resolution_clock::now();
    HashTable hashtable;
    for (auto& order : input) {
        hashtable.insert(order);
        dynamic += sizeof(Order) + 16;
    }
    hashtable.compareHash();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> length = end - start;
    size_t totalBytes = initial + dynamic;
    return Performance{length.count(), totalBytes};

}
Performance executeHeap (const vector<Order>& input) {
    size_t initial = sizeof(vector<Order>) * 2;
    size_t dynamic = 0;
    auto start = chrono::high_resolution_clock::now();
    vector<Order> buy;
    vector<Order> sell;
    for (auto& order : input) {
       if (order.type == 'B') {
           buy.push_back(order);
       }else if (order.type == 'S') {
           sell.push_back(order);
       }
    }
    makeMaxHeap(buy);
    makeMinHeap(sell);
    dynamic = (buy.capacity() + sell.capacity()) * sizeof(Order);
    compare(buy, sell);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> length = end - start;
    size_t totalBytes = initial + dynamic;
    return Performance{length.count(), totalBytes};
}
