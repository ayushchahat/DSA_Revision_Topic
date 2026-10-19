
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> arr;

    // Fix the min-heap property by moving the element DOWN.
    void heapify(vector<int>& arr, int n, int i) {
        int smallest = i;

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // MISTAKE FIX: Check left < n before accessing arr[left].
        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }

        // MISTAKE FIX: Check right independently, not with else-if.
        // Both children must be considered to find the smallest.
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }

        // If a child is smaller, swap and continue downward.
        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            heapify(arr, n, smallest);
        }
    }

    // Move an inserted or updated element UP when necessary.
    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (arr[parent] <= arr[i]) {
                break;  // Min-heap property is already satisfied.
            }

            swap(arr[parent], arr[i]);
            i = parent;
        }
    }

public:
    void initializeHeap() {
        arr.clear();
    }

    void insert(int key) {
        arr.push_back(key);

        // MISTAKE FIX: Don't rebuild the entire heap after insertion.
        // Only the newly inserted element needs to move upward.
        siftUp((int)arr.size() - 1);
    }

    void changeKey(int index, int new_val) {
        // Guard against an invalid index.
        if (index < 0 || index >= (int)arr.size()) {
            return;
        }

        int old_val = arr[index];

        // MISTAKE FIX: Use new_val, not the undefined variable key.
        arr[index] = new_val;

        if (new_val < old_val) {
            // The value decreased, so it might need to move UP.
            siftUp(index);
        } else if (new_val > old_val) {
            // The value increased, so it might need to move DOWN.
            heapify(arr, (int)arr.size(), index);
        }
    }

    void extractMin() {
        // MISTAKE FIX: Handle an empty heap.
        if (arr.empty()) {
            return;
        }

        // Move the last element to the root.
        arr[0] = arr.back();

        // Actually remove the last element.
        arr.pop_back();

        // Restore the min-heap property if elements remain.
        if (!arr.empty()) {
            heapify(arr, (int)arr.size(), 0);
        }
    }

    bool isEmpty() {
        return arr.empty();
    }

    int getMin() {
        // Precondition: the heap must not be empty.
        return arr[0];
    }

    int heapSize() {
        return (int)arr.size();
    }
};
