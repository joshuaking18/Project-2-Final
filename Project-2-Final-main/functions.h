//
// Created by meepe on 7/9/2026.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
using namespace std;
struct Performance {
    double time;
    size_t memory;
};
struct Order {
    char type;
    int amount;
    double cost;
};
struct Hash {
    long long pricekey;
    list<Order> bought;
    list<Order> sold;
};
class HashTable {
private:
    int tableSize = 1000003 ;
    vector<list<Hash>> table;
    double mult = 10000000.0;
    int makeIntoHash(long long pricekey) {
        return abs(pricekey) % tableSize;
    }
    long long getKey(double cost) {
        return cost * mult;
    }
    public:
    HashTable() : table(tableSize) {}
        void insert(const Order& order) {
            long long key = getKey(order.cost);
            int index = makeIntoHash(key);
            for (auto& bucket : table[index]) {
                if (bucket.pricekey == key) {
                    if (order.type == 'B') {
                        bucket.bought.push_back(order);
                    }else {
                        bucket.sold.push_back(order);
                    }
                    return;
                }
            }
        Hash newBucket;
        newBucket.pricekey = key;
        if (order.type == 'B') {
            newBucket.bought.push_back(order);
        }else {
            newBucket.sold.push_back(order);
        }
        table[index].push_back(newBucket);
        }
    void compareHash() {
        int totalTrades = 0;
        int totalVolumes = 0;
        for (int i = 0; i < tableSize; i++) {
            for (auto& bucket : table[i]) {
                while (!bucket.bought.empty() && !bucket.sold.empty()) {
                    auto& buy = bucket.bought.front();
                    auto& sold = bucket.sold.front();
                    int tradeAmount = min(buy.amount, sold.amount);
                    buy.amount -= tradeAmount;
                    sold.amount -= tradeAmount;
                    cout<< "Trade Completed | Price: " << (bucket.pricekey/mult) <<" | volume: "<< tradeAmount << endl;
                    totalTrades ++;
                    totalVolumes += tradeAmount;
                    if (buy.amount == 0) {
                        bucket.bought.pop_front();
                    }
                    if (sold.amount == 0) {
                        bucket.sold.pop_front();
                    }

                }
            }
        }
    }

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
Performance executeHash(const vector<Order>& input);
Performance executeHeap(const vector<Order>& input);