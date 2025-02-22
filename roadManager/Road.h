#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;


struct BridgeNode {
    float height;
    BridgeNode* next;

    BridgeNode(float h) : height(h), next(nullptr) {}
};


class Road {
public:
    float minBridgeHeight;
    int bridgeCount;
    BridgeNode* bridgesHead; // Linked list of bridge heights
    Road* roadP; // Dual pointer to connect the heap and the array in RoadSystem

    Road() : minBridgeHeight(numeric_limits<float>::max()), bridgeCount(0), bridgesHead(nullptr), roadP(nullptr) {}
    ~Road() {
        while (bridgesHead) {
            BridgeNode* temp = bridgesHead;
            bridgesHead = bridgesHead->next;
            delete temp;
        }
    }

    void AddBridge(float height);
    void printBridges() const;
    void insertAtHead(float height);
    void deleteNode(BridgeNode*& node);
    void insertAtPosition(float height, int pos);
    
};