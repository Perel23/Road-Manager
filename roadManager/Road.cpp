#include "Road.h"

void Road::AddBridge(float height) {
    minBridgeHeight = min(minBridgeHeight, height);
    bridgeCount++;

    BridgeNode* newNode = new BridgeNode(height);
    if (!bridgesHead) {
        bridgesHead = newNode;
    }
    else {
        BridgeNode* temp = bridgesHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void Road::printBridges() const {
    BridgeNode* current = bridgesHead;
    while (current) {
        cout << fixed << setprecision(4) << current->height;
        if (current->next) {
            cout << ", ";
        }
        current = current->next;
    }
    cout << endl;
}

// Insert a bridge at the head of the linked list
void Road::insertAtHead(float height) {
    BridgeNode* newNode = new BridgeNode(height);
    newNode->next = bridgesHead;
    bridgesHead = newNode;
    bridgeCount++;
    minBridgeHeight = min(minBridgeHeight, height);
}

// Delete a bridge given by reference
void Road::deleteNode(BridgeNode*& node) {
    if (!bridgesHead || !node) return;

    if (bridgesHead == node) {
        bridgesHead = bridgesHead->next;
        delete node;
    }
    else {
        BridgeNode* temp = bridgesHead;
        while (temp->next && temp->next != node) {
            temp = temp->next;
        }
        if (temp->next) {
            temp->next = node->next;
            delete node;
        }
    }
    bridgeCount--;

    // Update minBridgeHeight after deletion
    minBridgeHeight = numeric_limits<float>::max();
    for (BridgeNode* temp = bridgesHead; temp; temp = temp->next) {
        minBridgeHeight = min(minBridgeHeight, temp->height);
    }
}

// Insert a bridge at a specific position in the linked list
void Road::insertAtPosition(float height, int pos) {
    if (pos < 0) return;

    BridgeNode* newNode = new BridgeNode(height);
    if (pos == 0 || !bridgesHead) {
        insertAtHead(height);
        return;
    }

    BridgeNode* temp = bridgesHead;
    for (int i = 0; temp->next && i < pos - 1; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    bridgeCount++;
    minBridgeHeight = min(minBridgeHeight, height);
}
