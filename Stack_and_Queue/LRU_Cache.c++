
#include <map>
using namespace std;

class Node {
public:
    Node* prev;
    Node* next;
    int key;
    int val;

    Node(int key, int val) {
        this->key = key;
        this->val = val;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache {
    map<int, Node*> mp;
    int cap;
    Node* first = nullptr;
    Node* last = nullptr;

    void removeNode(Node* node) {
        if (node->prev)
            node->prev->next = node->next;
        else
            first = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            last = node->prev;
    }

    void addToEnd(Node* node) {
        node->prev = last;
        node->next = nullptr;

        if (last)
            last->next = node;
        else
            first = node;

        last = node;
    }

    void moveToEnd(Node* node) {
        if (node == last) return;

        removeNode(node);
        addToEnd(node);
    }

public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        auto it = mp.find(key);

        if (it == mp.end())
            return -1;

        Node* curr = it->second;
        moveToEnd(curr);

        return curr->val;
    }

    void put(int key, int value) {
        if (cap == 0) return;

        // Key already exists: update and mark recently used.
        if (mp.find(key) != mp.end()) {
            Node* curr = mp[key];
            curr->val = value;
            moveToEnd(curr);
            return;
        }

        // Evict the least recently used node.
        if (mp.size() == cap) {
            Node* temp = first;
            removeNode(temp);
            mp.erase(temp->key);
            delete temp;
        }

        Node* curr = new Node(key, value);
        addToEnd(curr);
        mp[key] = curr;
    }

    ~LRUCache() {
        Node* curr = first;

        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};
