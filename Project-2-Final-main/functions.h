//
// Created by meepe on 7/9/2026.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct Order {
    char type;
    int amount;
    double cost;
};
struct Hash {

    double pricekey;
    int buyVolume;
    int sellVolume;
    Hash* next;
    Hash(double p) : pricekey(p), buyVolume(0), sellVolume(0), next(nullptr) {}
};

void loadData(const string &fileName, vector<Order>& buffer);
void makeMaxHeap(vector<Order>& input);
void makeMinHeap(vector<Order>& input);
void compare(vector<Order>& Buy, vector<Order>& Sell);
int findHash(double cost);
void insertHash(Hash* table[], const Order& order);
vector<Order>* getOrders(Hash* table[], double cost);
void deleteHash(Hash* table[], double cost);
void compareHash(const vector<Order>& input);