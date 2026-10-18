
#include <bits/stdc++.h>
using namespace std;

class LFUCache {
private:
    // Node represents one key-value pair in the cache.
    struct Node {
        int key, value, freq;
        Node* prev;
        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            freq = 1;          // Every new key starts with frequency 1
            prev = next = nullptr;
        }
    };

    // Doubly linked list stores nodes having the same frequency.
    // Most recently used node is near the head.
    // Least recently used node is near the tail.
    struct DoublyLinkedList {
        Node* head;
        Node* tail;
        int size;

        DoublyLinkedList() {
            // Dummy nodes simplify insertion and deletion.
            head = new Node(-1, -1);
            tail = new Node(-1, -1);

            head->next = tail;
            tail->prev = head;
            size = 0;
        }

        // Insert node at the front (most recently used).
        void addNode(Node* node) {
            node->next = head->next;
            node->prev = head;

            head->next->prev = node;
            head->next = node;

            size++;
        }

        // Remove a node from this list.
        void removeNode(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;

            size--;
        }

        // Remove the least recently used node.
        Node* removeLRU() {
            if (size == 0)
                return nullptr;

            Node* node = tail->prev;
            removeNode(node);
            return node;
        }

        bool empty() {
            return size == 0;
        }

        ~DoublyLinkedList() {
            delete head;
            delete tail;
        }
    };

    int capacity;
    int minFreq;

    // key -> corresponding node
    unordered_map<int, Node*> keyMap;

    // frequency -> list of nodes having that frequency
    unordered_map<int, DoublyLinkedList*> freqMap;

    // Increase a node's frequency after get() or updating an existing key.
    void updateFrequency(Node* node) {
        int oldFreq = node->freq;

        // Remove node from its current frequency list.
        freqMap[oldFreq]->removeNode(node);

        // If this was the last node with minimum frequency,
        // the minimum frequency increases by one.
        if (oldFreq == minFreq &&
            freqMap[oldFreq]->empty()) {
            minFreq++;
        }

        // Increase the frequency.
        node->freq++;

        // Add the node to the front of its new frequency list.
        if (freqMap.find(node->freq) == freqMap.end()) {
            freqMap[node->freq] = new DoublyLinkedList();
        }

        freqMap[node->freq]->addNode(node);
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        // Key does not exist.
        if (keyMap.find(key) == keyMap.end())
            return -1;

        Node* node = keyMap[key];

        // Accessing a key increases its frequency.
        updateFrequency(node);

        return node->value;
    }

    void put(int key, int value) {
        // Cannot store anything if capacity is zero.
        if (capacity == 0)
            return;

        // If key exists, update its value and frequency.
        if (keyMap.find(key) != keyMap.end()) {
            Node* node = keyMap[key];
            node->value = value;

            updateFrequency(node);
            return;
        }

        // If cache is full, evict the LFU key.
        if (keyMap.size() == capacity) {
            // Among keys with minimum frequency,
            // remove the least recently used one.
            Node* victim = freqMap[minFreq]->removeLRU();

            keyMap.erase(victim->key);
            delete victim;
        }

        // Insert the new key with frequency 1.
        Node* node = new Node(key, value);
        keyMap[key] = node;

        if (freqMap.find(1) == freqMap.end()) {
            freqMap[1] = new DoublyLinkedList();
        }

        freqMap[1]->addNode(node);

        // Every newly inserted key has frequency 1.
        minFreq = 1;
    }

    // Free allocated nodes and frequency lists.
    ~LFUCache() {
        for (auto& entry : keyMap) {
            delete entry.second;
        }

        for (auto& entry : freqMap) {
            delete entry.second;
        }
    }
};
