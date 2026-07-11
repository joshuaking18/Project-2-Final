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

class HashTable {
private:
    static const int tableSize = 5000011;
    Hash* table[tableSize];
    int calcHash(double price){
        long long pennies = static_cast<long long>(price* 100);
        return(pennies ^ (pennies >>16)) % tableSize;

    }
    public:
    HashTable() {
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }
    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            Hash* curr = table[i];
            while (curr != nullptr) {
                Hash* deleted = curr;
                curr = curr->next;
                delete deleted;
            }
        }
    }
    Hash* getNode(double price) {
        int index = calcHash(price);
        Hash* curr = table[index];
        while (curr != nullptr) {
            if (curr->pricekey == price) {
                return curr;
            }
            curr = curr->next;
        }
        Hash* newNode = new Hash(price);
        newNode->next = table[index];
        table[index] = newNode;
        return newNode;
    }
    void insert(const Order& order) {
        Hash* node = getNode(order.cost);
        if (order.type == 'B') {
            node->buyVolume += order.amount;
        }else {
            node->sellVolume += order.amount;
        }
    }
    void matchOrders(std::vector<Order>& input) {
    std::cout << "\n--- EXECUTING HASH TABLE MATCHING ENGINE ---\n";
    int tradesExecuted = 0;
    int totalVolumeTraded = 0;

    // 1. Populate Hash Table with current sell orders to create the order book depth
    for ( auto& order : input) {
        insert(order);


        // The strategy allows matching if Buy Price >= Sell Price.
        // We look for any matching sell liquidity in the hash table.
        for (int i = 0; i < tableSize; i++) {
            Hash* current = table[i];
            while (current != nullptr) {
                // COMPARISON RULE: Buy Price >= Sell Price, and there is sell volume available
                if (current->sellVolume > 0 && order.cost >= current->pricekey) {

                    // Determine how much volume can match
                    int matchedVolume = (order.amount < current->sellVolume) ?
                                         order.amount : current->sellVolume;

                    // Execute trade deductions
                    order.amount -= matchedVolume;
                    current->sellVolume -= matchedVolume;
                    totalVolumeTraded += matchedVolume;
                    tradesExecuted++;

                    std::cout << "[TRADE] Matched Buy at $" << order.cost
                              << " with Sell limit at $" << current->pricekey
                              << " | Vol: " << matchedVolume << "\n";
                }

                if (order.amount == 0) break; // Buy order completely filled
                current = current->next;
            }
            if (order.amount == 0) break;
        }
    }
    std::cout << "Execution Finished. Trades: " << tradesExecuted
              << " | Total Vol Filled: " << totalVolumeTraded << "\n";
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