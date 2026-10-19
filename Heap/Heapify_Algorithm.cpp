
#include <iostream>
#include <vector>
using namespace std;

// Fix the heap property at index i by moving the element downward
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;             // Assume current node is largest
    int left = 2 * i + 1;        // Left child index
    int right = 2 * i + 2;       // Right child index

    // Find the largest among parent and left child
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Check whether right child is larger than current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If a child is larger than the parent, swap them
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Continue heapifying the subtree where the element moved
        heapify(arr, n, largest);
    }
}

// Convert an arbitrary array into a Max Heap
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();

    // Start at the last non-leaf node
    // All nodes from n/2 onward are leaves, so they need no heapify
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Fix each subtree, moving bottom-up toward the root
        heapify(arr, n, i);
    }
}

int main() {
    vector<int> arr = {4, 10, 3, 5, 1};

    buildMaxHeap(arr);

    // Print the resulting Max Heap
    for (int x : arr) {
        cout << x << " ";
    }

    return 0;
}

// Output: 10 5 3 4 1


// Time complexity: \(O(n)\) for building the heap. Each individual heapify() takes at most \(O(\log n)\), but the total build operation is \(O(n)\).