//
// Created by meepe on 7/9/2026.
//
#include <iostream>
#include <filesystem>
#include "functions.h"
#include <algorithm>

using namespace std;

int main() {
    int command = 0;
    vector<Order> orders;
    vector<Order> max;
    vector<Order> min;
    Performance heap = {0.0,0};
    Performance hash = {0.0,0};

    while (command != 5) {
        cout<<"======================================"<<endl;
        cout<<"High Frequency Stock Matching"<<endl;
        cout<<"1.Load"<<endl; // load all data
        cout<<"2.Execute Heap"<<endl;
        cout<<"3.Execute Hash"<<endl;
        cout<<"4.Print Report"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"Enter your command: ";
        cin >> command;
        cout<<"======================================"<<endl;
        //Initial Input

        if (command == 1) {
            cout<<"Loading something?"<<endl;

            loadData("C:\\Users\\meepe\\Downloads\\Project-2-Final-main\\Train_Dst_NoAuction_DecPre_CF_7.txt", orders);
            cout << orders.size();
            for (const auto& order : orders) {
                if (order.type == 'B') {
                    max.push_back(order);
                }
                if (order.type == 'S') {
                    min.push_back(order);
                }
                /* std::cout << "Type: " << order.type
                           << " | Vol: " << order.amount
                           << " | Price: " << order.cost << std::endl;*/
             }
        }else if(command == 2) {
            cout<<"Loading Heap Comparison..."<<endl;
            heap = executeHeap(orders);

        }else if(command == 3) {
            cout<<"Loading Hash Comparison..."<<endl;
          hash  = executeHash(orders);
        }else if(command == 4) {
            cout<<"Loading Report..."<<endl;
            cout<<"======================================"<<endl;
            cout<<"Metric            Heaps        Hash   "<<endl;
            cout<<"--------------------------------------"<<endl;
            cout<<"Time:             "            <<heap.time<<" ms"<<"        "<<hash.time<< "ms"<<endl;
            cout<<"Memory:           "            <<heap.memory<<" bytes"<<"     "<<hash.memory<< " bytes"<<endl;
            cout<<"======================================"<<endl;


        }else if(command == 5) {
            cout<<"Exiting..."<<endl;
            return 0;
        }
    }

}
