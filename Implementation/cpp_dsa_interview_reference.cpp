// C++17 DSA Interview Reference
// A practical collection of common data structures and algorithms for coding rounds.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic cpp_dsa_interview_reference.cpp -o dsa
// Most functions are examples/templates; use only the sections needed for a question.

#include <bits/stdc++.h>
using namespace std;

namespace dsa {

// ============================================================================
// 1. SINGLY LINKED LIST
// ============================================================================
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

void pushFront(ListNode*& head, int value) {
    auto* node = new ListNode(value);
    node->next = head;
    head = node;
}

void pushBack(ListNode*& head, int value) {
    auto* node = new ListNode(value);
    if (!head) { head = node; return; }
    ListNode* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

bool insertAt(ListNode*& head, int index, int value) { // 0-based index
    if (index < 0) return false;
    if (index == 0) { pushFront(head, value); return true; }
    ListNode* cur = head;
    for (int i = 0; cur && i < index - 1; ++i) cur = cur->next;
    if (!cur) return false;
    auto* node = new ListNode(value);
    node->next = cur->next;
    cur->next = node;
    return true;
}

bool eraseAt(ListNode*& head, int index) { // 0-based index
    if (index < 0 || !head) return false;
    if (index == 0) {
        ListNode* old = head;
        head = head->next;
        delete old;
        return true;
    }
    ListNode* cur = head;
    for (int i = 0; cur && i < index - 1; ++i) cur = cur->next;
    if (!cur || !cur->next) return false;
    ListNode* old = cur->next;
    cur->next = old->next;
    delete old;
    return true;
}

ListNode* reverseListIterative(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nextNode = head->next;
        head->next = prev;
        prev = head;
        head = nextNode;
    }
    return prev;
}

ListNode* reverseListRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

ListNode* middleNode(ListNode* head) { // For even length, returns the second middle.
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool hasCycle(ListNode* head) { // Floyd's tortoise-and-hare algorithm.
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

void removeCycle(ListNode* head) {
    if (!head) return;
    ListNode* slow = head;
    ListNode* fast = head;
    do {
        if (!fast || !fast->next) return;
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);

    slow = head;
    if (slow == fast) { // Cycle begins at head.
        while (fast->next != slow) fast = fast->next;
    } else {
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    fast->next = nullptr;
}

ListNode* mergeSortedLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

void deleteList(ListNode*& head) {
    while (head) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

// Doubly linked list: each node stores both previous and next pointers.
struct DoublyNode {
    int val;
    DoublyNode* prev;
    DoublyNode* next;
    explicit DoublyNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
    DoublyNode* head = nullptr;
    DoublyNode* tail = nullptr;
public:
    void pushFront(int x) {
        auto* node = new DoublyNode(x);
        node->next = head;
        if (head) head->prev = node;
        else tail = node;
        head = node;
    }
    void pushBack(int x) {
        auto* node = new DoublyNode(x);
        node->prev = tail;
        if (tail) tail->next = node;
        else head = node;
        tail = node;
    }
    bool eraseFirst(int x) {
        DoublyNode* cur = head;
        while (cur && cur->val != x) cur = cur->next;
        if (!cur) return false;
        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev;
        delete cur;
        return true;
    }
    void printForward() const {
        for (DoublyNode* cur = head; cur; cur = cur->next) cout << cur->val << ' ';
        cout << '\n';
    }
    void printBackward() const {
        for (DoublyNode* cur = tail; cur; cur = cur->prev) cout << cur->val << ' ';
        cout << '\n';
    }
    ~DoublyLinkedList() {
        while (head) { DoublyNode* nextNode = head->next; delete head; head = nextNode; }
    }
};

// ============================================================================
// 2. STACKS AND QUEUES
// ============================================================================
class MinStack {
    stack<pair<int, int>> st; // {value, minimum so far}
public:
    void push(int x) {
        int currentMin = st.empty() ? x : min(x, st.top().second);
        st.push({x, currentMin});
    }
    void pop() { if (!st.empty()) st.pop(); }
    int top() const { if (st.empty()) throw runtime_error("Stack is empty"); return st.top().first; }
    int getMin() const { if (st.empty()) throw runtime_error("Stack is empty"); return st.top().second; }
    bool empty() const { return st.empty(); }
};

class ArrayStack {
    vector<int> data;
    size_t capacity;
public:
    explicit ArrayStack(size_t cap) : capacity(cap) { data.reserve(cap); }
    bool empty() const { return data.empty(); }
    bool full() const { return data.size() == capacity; }
    bool push(int x) { if (full()) return false; data.push_back(x); return true; }
    bool pop() { if (empty()) return false; data.pop_back(); return true; }
    int top() const { if (empty()) throw runtime_error("Stack is empty"); return data.back(); }
};

class LinkedListStack {
    ListNode* head = nullptr;
public:
    void push(int x) { auto* node = new ListNode(x); node->next = head; head = node; }
    bool pop() {
        if (!head) return false;
        ListNode* old = head; head = head->next; delete old; return true;
    }
    int top() const { if (!head) throw runtime_error("Stack is empty"); return head->val; }
    bool empty() const { return head == nullptr; }
    ~LinkedListStack() { deleteList(head); }
};

class LinkedListQueue {
    ListNode* frontNode = nullptr;
    ListNode* rearNode = nullptr;
public:
    void push(int x) {
        auto* node = new ListNode(x);
        if (rearNode) rearNode->next = node;
        else frontNode = node;
        rearNode = node;
    }
    bool pop() {
        if (!frontNode) return false;
        ListNode* old = frontNode;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete old;
        return true;
    }
    int front() const { if (!frontNode) throw runtime_error("Queue is empty"); return frontNode->val; }
    bool empty() const { return frontNode == nullptr; }
    ~LinkedListQueue() { while (pop()) {} }
};

class CircularQueue {
    vector<int> data;
    int frontIndex = 0;
    int rearIndex = -1;
    int currentSize = 0;
public:
    explicit CircularQueue(int capacity) : data(max(0, capacity)) {}
    bool empty() const { return currentSize == 0; }
    bool full() const { return currentSize == static_cast<int>(data.size()); }
    int size() const { return currentSize; }
    bool enqueue(int x) {
        if (full()) return false;
        rearIndex = (rearIndex + 1) % static_cast<int>(data.size());
        data[rearIndex] = x;
        ++currentSize;
        return true;
    }
    bool dequeue() {
        if (empty()) return false;
        frontIndex = (frontIndex + 1) % static_cast<int>(data.size());
        --currentSize;
        return true;
    }
    int front() const {
        if (empty()) throw runtime_error("Queue is empty");
        return data[frontIndex];
    }
};

class QueueUsingStacks {
    stack<int> input, output;
    void moveIfNeeded() {
        if (output.empty()) while (!input.empty()) { output.push(input.top()); input.pop(); }
    }
public:
    void push(int x) { input.push(x); }
    void pop() { moveIfNeeded(); if (!output.empty()) output.pop(); }
    int front() { moveIfNeeded(); if (output.empty()) throw runtime_error("Queue is empty"); return output.top(); }
    bool empty() const { return input.empty() && output.empty(); }
};

class StackUsingQueues {
    queue<int> q;
public:
    void push(int x) {
        q.push(x);
        for (int i = 0, n = static_cast<int>(q.size()) - 1; i < n; ++i) {
            q.push(q.front()); q.pop();
        }
    }
    void pop() { if (!q.empty()) q.pop(); }
    int top() const { if (q.empty()) throw runtime_error("Stack is empty"); return q.front(); }
    bool empty() const { return q.empty(); }
};

// Monotonic stack pattern: next greater element to the right; -1 if absent.
vector<int> nextGreaterElement(const vector<int>& a) {
    int n = static_cast<int>(a.size());
    vector<int> ans(n, -1);
    stack<int> st; // indices; values are decreasing from bottom to top
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.top()] < a[i]) {
            ans[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

// ============================================================================
// 3. BINARY TREE
// ============================================================================
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isLeaf(const TreeNode* root) {
    return root && !root->left && !root->right;
}

int heightNodes(const TreeNode* root) { // Number of nodes on the longest root-to-leaf path.
    if (!root) return 0;
    return 1 + max(heightNodes(root->left), heightNodes(root->right));
}

int heightEdges(const TreeNode* root) { // Number of edges; empty tree = -1, leaf = 0.
    if (!root) return -1;
    return 1 + max(heightEdges(root->left), heightEdges(root->right));
}

int countNodes(const TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(const TreeNode* root) {
    if (!root) return 0;
    if (isLeaf(root)) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

bool searchTree(const TreeNode* root, int target) { // Works for any binary tree.
    if (!root) return false;
    if (root->val == target) return true;
    return searchTree(root->left, target) || searchTree(root->right, target);
}

void preorderRecursive(const TreeNode* root, vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorderRecursive(root->left, out);
    preorderRecursive(root->right, out);
}
void inorderRecursive(const TreeNode* root, vector<int>& out) {
    if (!root) return;
    inorderRecursive(root->left, out);
    out.push_back(root->val);
    inorderRecursive(root->right, out);
}
void postorderRecursive(const TreeNode* root, vector<int>& out) {
    if (!root) return;
    postorderRecursive(root->left, out);
    postorderRecursive(root->right, out);
    out.push_back(root->val);
}

vector<int> preorderIterative(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;
    stack<TreeNode*> st; st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        ans.push_back(cur->val);
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
    return ans;
}

vector<int> inorderIterative(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();
        ans.push_back(cur->val);
        cur = cur->right;
    }
    return ans;
}

vector<int> postorderIterative(TreeNode* root) { // One-stack version.
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* lastVisited = nullptr;
    while (cur || !st.empty()) {
        if (cur) { st.push(cur); cur = cur->left; }
        else {
            TreeNode* peek = st.top();
            if (peek->right && lastVisited != peek->right) cur = peek->right;
            else { ans.push_back(peek->val); lastVisited = peek; st.pop(); }
        }
    }
    return ans;
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (!root) return ans;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        vector<int> level;
        while (levelSize--) {
            TreeNode* cur = q.front(); q.pop();
            level.push_back(cur->val);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        ans.push_back(move(level));
    }
    return ans;
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    auto ans = levelOrder(root);
    for (int i = 1; i < static_cast<int>(ans.size()); i += 2)
        reverse(ans[i].begin(), ans[i].end());
    return ans;
}

vector<int> leftView(TreeNode* root) {
    vector<int> ans;
    for (const auto& level : levelOrder(root)) if (!level.empty()) ans.push_back(level.front());
    return ans;
}
vector<int> rightView(TreeNode* root) {
    vector<int> ans;
    for (const auto& level : levelOrder(root)) if (!level.empty()) ans.push_back(level.back());
    return ans;
}

int diameterEdges(TreeNode* root) { // Longest path measured in edges; O(n).
    int diameter = 0;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int left = dfs(node->left), right = dfs(node->right);
        diameter = max(diameter, left + right);
        return 1 + max(left, right); // height measured in nodes here
    };
    dfs(root);
    return diameter;
}

int balancedHeightOrMinusOne(TreeNode* root) { // -1 means unbalanced; O(n).
    if (!root) return 0;
    int left = balancedHeightOrMinusOne(root->left);
    if (left == -1) return -1;
    int right = balancedHeightOrMinusOne(root->right);
    if (right == -1 || abs(left - right) > 1) return -1;
    return 1 + max(left, right);
}
bool isBalanced(TreeNode* root) { return balancedHeightOrMinusOne(root) != -1; }

TreeNode* lowestCommonAncestorBinaryTree(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestorBinaryTree(root->left, p, q);
    TreeNode* right = lowestCommonAncestorBinaryTree(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

bool hasRootToLeafSum(TreeNode* root, long long target) {
    if (!root) return false;
    if (isLeaf(root)) return target == root->val;
    target -= root->val;
    return hasRootToLeafSum(root->left, target) || hasRootToLeafSum(root->right, target);
}

void invertTree(TreeNode* root) {
    if (!root) return;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
}

void rootToNodePath(TreeNode* root, int target, vector<int>& path, bool& found) {
    if (!root || found) return;
    path.push_back(root->val);
    if (root->val == target) { found = true; return; }
    rootToNodePath(root->left, target, path, found);
    rootToNodePath(root->right, target, path, found);
    if (!found) path.pop_back();
}

TreeNode* buildTreeFromLevelOrder(const vector<optional<int>>& values) {
    if (values.empty() || !values[0].has_value()) return nullptr;
    TreeNode* root = new TreeNode(*values[0]);
    queue<TreeNode*> q; q.push(root);
    size_t i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* cur = q.front(); q.pop();
        if (i < values.size() && values[i].has_value()) {
            cur->left = new TreeNode(*values[i]); q.push(cur->left);
        }
        ++i;
        if (i < values.size() && values[i].has_value()) {
            cur->right = new TreeNode(*values[i]); q.push(cur->right);
        }
        ++i;
    }
    return root;
}

void printTreeByLevel(TreeNode* root) {
    if (!root) { cout << "Tree is empty\n"; return; }
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int n = static_cast<int>(q.size());
        while (n--) {
            TreeNode* cur = q.front(); q.pop();
            cout << cur->val << ' ';
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << '\n';
    }
}

// Builds a FULL binary tree with `levels` levels. levels=1 means just the root.
// This is a complete/full-by-construction tree, not a random-shaped tree.
// Recursive version matching the common interview prompt where height is
// measured in EDGES below the root: height=0 creates only the root.
void generateFullSubtreeByRemainingHeight(int remainingEdges, TreeNode* node, mt19937& rng) {
    if (!node || remainingEdges == 0) return;
    uniform_int_distribution<int> dist(1, 100);
    node->left = new TreeNode(dist(rng));
    generateFullSubtreeByRemainingHeight(remainingEdges - 1, node->left, rng);
    node->right = new TreeNode(dist(rng));
    generateFullSubtreeByRemainingHeight(remainingEdges - 1, node->right, rng);
}

TreeNode* buildFullRandomTreeByEdgeHeight(int height, mt19937& rng) {
    if (height < 0) return nullptr;
    uniform_int_distribution<int> dist(1, 100);
    TreeNode* root = new TreeNode(dist(rng));
    generateFullSubtreeByRemainingHeight(height, root, rng);
    return root;
}

TreeNode* generateFullRandomTree(int levels, mt19937& rng) {
    if (levels <= 0) return nullptr;
    uniform_int_distribution<int> dist(1, 100);
    TreeNode* root = new TreeNode(dist(rng));
    queue<pair<TreeNode*, int>> q; q.push({root, 1});
    while (!q.empty()) {
        auto [cur, level] = q.front(); q.pop();
        if (level == levels) continue;
        cur->left = new TreeNode(dist(rng));
        cur->right = new TreeNode(dist(rng));
        q.push({cur->left, level + 1});
        q.push({cur->right, level + 1});
    }
    return root;
}

// Generates a random-shaped tree up to maxDepth. Each possible child is created
// with probabilityPercent probability. Root depth is 1.
TreeNode* generateRandomShapeTree(int maxDepth, int probabilityPercent, mt19937& rng) {
    if (maxDepth <= 0) return nullptr;
    uniform_int_distribution<int> valueDist(1, 100);
    uniform_int_distribution<int> chance(1, 100);
    TreeNode* root = new TreeNode(valueDist(rng));
    function<void(TreeNode*, int)> build = [&](TreeNode* node, int depth) {
        if (depth == maxDepth) return;
        if (chance(rng) <= probabilityPercent) {
            node->left = new TreeNode(valueDist(rng));
            build(node->left, depth + 1);
        }
        if (chance(rng) <= probabilityPercent) {
            node->right = new TreeNode(valueDist(rng));
            build(node->right, depth + 1);
        }
    };
    build(root, 1);
    return root;
}

void deleteTree(TreeNode* root);

// Build a binary tree from preorder + inorder traversals (all values unique).
TreeNode* buildFromPreorderInorder(const vector<int>& preorder, const vector<int>& inorder) {
    if (preorder.size() != inorder.size()) throw invalid_argument("Traversal sizes differ");
    unordered_map<int, int> position;
    for (int i = 0; i < static_cast<int>(inorder.size()); ++i) position[inorder[i]] = i;
    int preIndex = 0;
    function<TreeNode*(int, int)> build = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        if (preIndex >= static_cast<int>(preorder.size())) throw invalid_argument("Invalid traversals");
        int value = preorder[preIndex++];
        auto it = position.find(value);
        if (it == position.end() || it->second < left || it->second > right)
            throw invalid_argument("Invalid traversals or duplicate values");
        TreeNode* root = new TreeNode(value);
        root->left = build(left, it->second - 1);
        root->right = build(it->second + 1, right);
        return root;
    };
    TreeNode* root = build(0, static_cast<int>(inorder.size()) - 1);
    if (preIndex != static_cast<int>(preorder.size())) {
        deleteTree(root);
        throw invalid_argument("Invalid traversals");
    }
    return root;
}

long long maximumPathSum(TreeNode* root) { // Any non-empty path; O(n).
    if (!root) return 0;
    long long best = LLONG_MIN;
    function<long long(TreeNode*)> dfs = [&](TreeNode* node) -> long long {
        if (!node) return 0;
        long long left = max(0LL, dfs(node->left));
        long long right = max(0LL, dfs(node->right));
        best = max(best, static_cast<long long>(node->val) + left + right);
        return static_cast<long long>(node->val) + max(left, right);
    };
    dfs(root);
    return best;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ============================================================================
// 4. BINARY SEARCH TREE (BST)
// ============================================================================
TreeNode* bstInsert(TreeNode* root, int value) { // Duplicate values are ignored.
    if (!root) return new TreeNode(value);
    if (value < root->val) root->left = bstInsert(root->left, value);
    else if (value > root->val) root->right = bstInsert(root->right, value);
    return root;
}

bool bstSearch(TreeNode* root, int target) {
    while (root) {
        if (root->val == target) return true;
        root = target < root->val ? root->left : root->right;
    }
    return false;
}

TreeNode* bstMinimum(TreeNode* root) {
    if (!root) return nullptr;
    while (root->left) root = root->left;
    return root;
}

TreeNode* bstDelete(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val) root->left = bstDelete(root->left, key);
    else if (key > root->val) root->right = bstDelete(root->right, key);
    else {
        if (!root->left) { TreeNode* r = root->right; delete root; return r; }
        if (!root->right) { TreeNode* l = root->left; delete root; return l; }
        TreeNode* successor = bstMinimum(root->right);
        root->val = successor->val;
        root->right = bstDelete(root->right, successor->val);
    }
    return root;
}

bool validateBSTRange(TreeNode* root, long long low, long long high) {
    if (!root) return true;
    if (root->val <= low || root->val >= high) return false;
    return validateBSTRange(root->left, low, root->val) &&
           validateBSTRange(root->right, root->val, high);
}
bool isValidBST(TreeNode* root) {
    return validateBSTRange(root, LLONG_MIN, LLONG_MAX);
}

TreeNode* kthSmallestBST(TreeNode* root, int k) { // k is 1-based.
    stack<TreeNode*> st;
    while (root || !st.empty()) {
        while (root) { st.push(root); root = root->left; }
        root = st.top(); st.pop();
        if (--k == 0) return root;
        root = root->right;
    }
    return nullptr;
}

TreeNode* sortedArrayToBST(const vector<int>& a, int left, int right) {
    if (left > right) return nullptr;
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(a[mid]);
    root->left = sortedArrayToBST(a, left, mid - 1);
    root->right = sortedArrayToBST(a, mid + 1, right);
    return root;
}

// ============================================================================
// 5. HEAP / PRIORITY QUEUE
// ============================================================================
class MinHeap {
    vector<int> a;
    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[p] <= a[i]) break;
            swap(a[p], a[i]); i = p;
        }
    }
    void siftDown(int i) {
        int n = static_cast<int>(a.size());
        while (true) {
            int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
            if (left < n && a[left] < a[smallest]) smallest = left;
            if (right < n && a[right] < a[smallest]) smallest = right;
            if (smallest == i) break;
            swap(a[i], a[smallest]); i = smallest;
        }
    }
public:
    bool empty() const { return a.empty(); }
    int size() const { return static_cast<int>(a.size()); }
    void push(int x) { a.push_back(x); siftUp(size() - 1); }
    int top() const { if (empty()) throw runtime_error("Heap is empty"); return a[0]; }
    int pop() {
        if (empty()) throw runtime_error("Heap is empty");
        int result = a[0];
        a[0] = a.back(); a.pop_back();
        if (!empty()) siftDown(0);
        return result;
    }
};

int kthLargest(const vector<int>& a, int k) { // O(n log k), k is 1-based.
    if (k < 1 || k > static_cast<int>(a.size())) throw invalid_argument("Invalid k");
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : a) {
        minHeap.push(x);
        if (static_cast<int>(minHeap.size()) > k) minHeap.pop();
    }
    return minHeap.top();
}

// ============================================================================
// 6. DISJOINT SET UNION (DSU / UNION-FIND)
// ============================================================================
class DSU {
    vector<int> parent, size;
public:
    explicit DSU(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]); // Path compression.
        return parent[x];
    }
    bool unite(int a, int b) { // Union by size. False means already connected.
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
    bool connected(int a, int b) { return find(a) == find(b); }
};

// ============================================================================
// 7. GRAPHS: BFS, DFS, CYCLES, TOPOLOGICAL SORT, SHORTEST PATHS, MST
// ============================================================================
using Graph = vector<vector<int>>;
vector<vector<int>> adjacencyMatrix(int n, const vector<pair<int, int>>& edges, bool directed) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (auto [u, v] : edges) {
        matrix[u][v] = 1;
        if (!directed) matrix[v][u] = 1;
    }
    return matrix;
}
void addUndirectedEdge(Graph& g, int u, int v) {
    g[u].push_back(v); g[v].push_back(u);
}
void addDirectedEdge(Graph& g, int u, int v) { g[u].push_back(v); }

vector<int> graphBFS(const Graph& g, int source) {
    int n = static_cast<int>(g.size());
    vector<int> order;
    if (source < 0 || source >= n) return order;
    vector<bool> seen(n, false);
    queue<int> q; q.push(source); seen[source] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop(); order.push_back(u);
        for (int v : g[u]) if (!seen[v]) { seen[v] = true; q.push(v); }
    }
    return order;
}

void graphDFSRecursive(const Graph& g, int u, vector<bool>& seen, vector<int>& order) {
    seen[u] = true; order.push_back(u);
    for (int v : g[u]) if (!seen[v]) graphDFSRecursive(g, v, seen, order);
}

vector<int> graphDFSIterative(const Graph& g, int source) {
    int n = static_cast<int>(g.size());
    vector<int> order;
    if (source < 0 || source >= n) return order;
    vector<bool> seen(n, false);
    stack<int> st; st.push(source);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (seen[u]) continue;
        seen[u] = true; order.push_back(u);
        // Reverse iteration often makes the visit order match recursive DFS.
        for (auto it = g[u].rbegin(); it != g[u].rend(); ++it)
            if (!seen[*it]) st.push(*it);
    }
    return order;
}

int connectedComponents(const Graph& g) {
    int n = static_cast<int>(g.size()), components = 0;
    vector<bool> seen(n, false);
    for (int i = 0; i < n; ++i) if (!seen[i]) {
        ++components;
        queue<int> q; q.push(i); seen[i] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (!seen[v]) { seen[v] = true; q.push(v); }
        }
    }
    return components;
}

bool hasCycleUndirectedBFS(const Graph& g) {
    int n = static_cast<int>(g.size());
    vector<bool> seen(n, false);
    for (int start = 0; start < n; ++start) if (!seen[start]) {
        queue<pair<int, int>> q; q.push({start, -1}); seen[start] = true;
        while (!q.empty()) {
            auto [u, parent] = q.front(); q.pop();
            for (int v : g[u]) {
                if (!seen[v]) { seen[v] = true; q.push({v, u}); }
                else if (v != parent) return true;
            }
        }
    }
    return false;
}

bool hasCycleDirectedDFS(const Graph& g) { // 0=unvisited, 1=visiting, 2=done.
    int n = static_cast<int>(g.size());
    vector<int> color(n, 0);
    function<bool(int)> dfs = [&](int u) {
        color[u] = 1;
        for (int v : g[u]) {
            if (color[v] == 1) return true;
            if (color[v] == 0 && dfs(v)) return true;
        }
        color[u] = 2;
        return false;
    };
    for (int i = 0; i < n; ++i) if (color[i] == 0 && dfs(i)) return true;
    return false;
}

bool isBipartite(const Graph& g) {
    int n = static_cast<int>(g.size());
    vector<int> color(n, -1);
    for (int s = 0; s < n; ++s) if (color[s] == -1) {
        queue<int> q; q.push(s); color[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) { color[v] = color[u] ^ 1; q.push(v); }
                else if (color[v] == color[u]) return false;
            }
        }
    }
    return true;
}

vector<int> topologicalSortDFS(const Graph& g) { // Returns empty if a directed cycle exists.
    int n = static_cast<int>(g.size());
    vector<int> color(n, 0), order;
    function<bool(int)> dfs = [&](int u) {
        color[u] = 1;
        for (int v : g[u]) {
            if (color[v] == 1) return false;
            if (color[v] == 0 && !dfs(v)) return false;
        }
        color[u] = 2;
        order.push_back(u);
        return true;
    };
    for (int i = 0; i < n; ++i)
        if (color[i] == 0 && !dfs(i)) return {};
    reverse(order.begin(), order.end());
    return order;
}

vector<int> topologicalSortKahn(const Graph& g) {
    int n = static_cast<int>(g.size());
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; ++u) for (int v : g[u]) ++indegree[v];
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indegree[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop(); order.push_back(u);
        for (int v : g[u]) if (--indegree[v] == 0) q.push(v);
    }
    if (static_cast<int>(order.size()) != n) return {}; // Directed cycle exists.
    return order;
}

// Weighted directed/undirected graph representation: adj[u] = { {v, weight}, ... }.
using WeightedGraph = vector<vector<pair<int, int>>>;
constexpr long long INF = LLONG_MAX / 4;

vector<long long> dijkstra(const WeightedGraph& g, int source) {
    int n = static_cast<int>(g.size());
    vector<long long> dist(n, INF);
    if (source < 0 || source >= n) return dist;
    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[source] = 0; pq.push({0, source});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue; // Ignore stale heap entries.
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist; // Requires all edge weights >= 0.
}

struct BellmanFordResult {
    vector<long long> dist;
    bool hasReachableNegativeCycle = false;
};
BellmanFordResult bellmanFord(int n, const vector<tuple<int, int, int>>& edges, int source) {
    vector<long long> dist(n, INF);
    if (source < 0 || source >= n) return {dist, false};
    dist[source] = 0;
    for (int i = 1; i < n; ++i) {
        bool changed = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; changed = true;
            }
        }
        if (!changed) break;
    }
    for (auto [u, v, w] : edges)
        if (dist[u] != INF && dist[u] + w < dist[v]) return {dist, true};
    return {dist, false};
}

vector<vector<long long>> floydWarshall(vector<vector<long long>> dist) {
    int n = static_cast<int>(dist.size());
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

struct Edge { int u, v, weight; };
pair<long long, vector<Edge>> kruskalMST(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
    DSU dsu(n);
    long long total = 0;
    vector<Edge> chosen;
    for (const Edge& e : edges) if (dsu.unite(e.u, e.v)) {
        total += e.weight; chosen.push_back(e);
        if (static_cast<int>(chosen.size()) == n - 1) break;
    }
    return {total, chosen}; // If chosen.size()!=n-1, graph was disconnected.
}

long long primMSTWeight(const WeightedGraph& g, int start = 0) {
    int n = static_cast<int>(g.size());
    if (n == 0) return 0;
    vector<bool> used(n, false);
    using State = pair<int, int>; // {edge weight, node}
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, start});
    long long total = 0;
    int visited = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (used[u]) continue;
        used[u] = true; total += w; ++visited;
        for (auto [v, cost] : g[u]) if (!used[v]) pq.push({cost, v});
    }
    return visited == n ? total : -1; // -1 indicates disconnected graph.
}

// ============================================================================
// 8. TRIE (LOWERCASE ENGLISH LETTERS)
// ============================================================================
class Trie {
    struct Node {
        array<Node*, 26> child{};
        bool isEnd = false;
        Node() { child.fill(nullptr); }
    };
    Node* root = new Node();
    static int indexOf(char c) {
        if (c < 'a' || c > 'z') throw invalid_argument("Trie accepts lowercase a-z only");
        return c - 'a';
    }
public:
    void insert(const string& word) {
        Node* cur = root;
        for (char c : word) {
            int i = indexOf(c);
            if (!cur->child[i]) cur->child[i] = new Node();
            cur = cur->child[i];
        }
        cur->isEnd = true;
    }
    bool search(const string& word) const {
        Node* cur = root;
        for (char c : word) {
            int i = indexOf(c);
            if (!cur->child[i]) return false;
            cur = cur->child[i];
        }
        return cur->isEnd;
    }
    bool startsWith(const string& prefix) const {
        Node* cur = root;
        for (char c : prefix) {
            int i = indexOf(c);
            if (!cur->child[i]) return false;
            cur = cur->child[i];
        }
        return true;
    }
    ~Trie() { destroy(root); }
private:
    static void destroy(Node* node) {
        if (!node) return;
        for (Node* next : node->child) destroy(next);
        delete node;
    }
};

// ============================================================================
// 9. FENWICK TREE / BINARY INDEXED TREE (POINT UPDATE, PREFIX/RANGE SUM)
// ============================================================================
class FenwickTree {
    int n;
    vector<long long> bit;
public:
    explicit FenwickTree(int n) : n(n), bit(n + 1, 0) {}
    explicit FenwickTree(const vector<int>& a) : FenwickTree(static_cast<int>(a.size())) {
        for (int i = 0; i < n; ++i) add(i, a[i]);
    }
    void add(int index0, long long delta) { // 0-based external index
        for (int i = index0 + 1; i <= n; i += i & -i) bit[i] += delta;
    }
    long long prefixSum(int index0) const { // Sum [0..index0]; prefixSum(-1)=0.
        long long result = 0;
        for (int i = index0 + 1; i > 0; i -= i & -i) result += bit[i];
        return result;
    }
    long long rangeSum(int left, int right) const { // Inclusive range.
        if (left > right) return 0;
        return prefixSum(right) - prefixSum(left - 1);
    }
};

// ============================================================================
// 10. SEGMENT TREE (RANGE SUM + POINT UPDATE)
// ============================================================================
class SegmentTree {
    int n;
    vector<long long> tree;
    void build(int node, int left, int right, const vector<int>& a) {
        if (left == right) { tree[node] = a[left]; return; }
        int mid = left + (right - left) / 2;
        build(node * 2, left, mid, a);
        build(node * 2 + 1, mid + 1, right, a);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
    void update(int node, int left, int right, int index, long long value) {
        if (left == right) { tree[node] = value; return; }
        int mid = left + (right - left) / 2;
        if (index <= mid) update(node * 2, left, mid, index, value);
        else update(node * 2 + 1, mid + 1, right, index, value);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
    long long query(int node, int left, int right, int ql, int qr) const {
        if (qr < left || right < ql) return 0; // No overlap.
        if (ql <= left && right <= qr) return tree[node]; // Full overlap.
        int mid = left + (right - left) / 2;
        return query(node * 2, left, mid, ql, qr) +
               query(node * 2 + 1, mid + 1, right, ql, qr);
    }
public:
    explicit SegmentTree(const vector<int>& a) : n(static_cast<int>(a.size())), tree(max(1, 4 * n), 0) {
        if (n) build(1, 0, n - 1, a);
    }
    void pointUpdate(int index, long long value) {
        if (index < 0 || index >= n) throw out_of_range("Segment tree index");
        update(1, 0, n - 1, index, value);
    }
    long long rangeSum(int left, int right) const {
        if (n == 0 || left > right) return 0;
        if (left < 0 || right >= n) throw out_of_range("Segment tree range");
        return query(1, 0, n - 1, left, right);
    }
};

// ============================================================================
// 11. SEARCHING
// ============================================================================
int linearSearch(const vector<int>& a, int target) {
    for (int i = 0; i < static_cast<int>(a.size()); ++i) if (a[i] == target) return i;
    return -1;
}

int binarySearchIterative(const vector<int>& a, int target) { // Array must be sorted.
    int left = 0, right = static_cast<int>(a.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int binarySearchRecursive(const vector<int>& a, int left, int right, int target) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (a[mid] == target) return mid;
    if (a[mid] < target) return binarySearchRecursive(a, mid + 1, right, target);
    return binarySearchRecursive(a, left, mid - 1, target);
}

int firstOccurrence(const vector<int>& a, int target) { // lower_bound style
    int left = 0, right = static_cast<int>(a.size());
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left < static_cast<int>(a.size()) && a[left] == target ? left : -1;
}

int lastOccurrence(const vector<int>& a, int target) { // upper_bound - 1
    int left = 0, right = static_cast<int>(a.size());
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] <= target) left = mid + 1;
        else right = mid;
    }
    int index = left - 1;
    return index >= 0 && a[index] == target ? index : -1;
}

int searchRotatedSortedArray(const vector<int>& a, int target) { // Distinct values.
    int left = 0, right = static_cast<int>(a.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == target) return mid;
        if (a[left] <= a[mid]) {
            if (a[left] <= target && target < a[mid]) right = mid - 1;
            else left = mid + 1;
        } else {
            if (a[mid] < target && target <= a[right]) left = mid + 1;
            else right = mid - 1;
        }
    }
    return -1;
}

// ============================================================================
// 12. SORTING
// ============================================================================
void bubbleSort(vector<int>& a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n; ++i) {
        bool swapped = false;
        for (int j = 0; j + 1 < n - i; ++j) if (a[j] > a[j + 1]) {
            swap(a[j], a[j + 1]); swapped = true;
        }
        if (!swapped) break;
    }
}

void selectionSort(vector<int>& a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n; ++i) {
        int smallest = i;
        for (int j = i + 1; j < n; ++j) if (a[j] < a[smallest]) smallest = j;
        swap(a[i], a[smallest]);
    }
}

void insertionSort(vector<int>& a) {
    for (int i = 1; i < static_cast<int>(a.size()); ++i) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; --j; }
        a[j + 1] = key;
    }
}

void mergeSort(vector<int>& a) {
    vector<int> temp(a.size());
    function<void(int, int)> sortRange = [&](int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        sortRange(left, mid); sortRange(mid + 1, right);
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        while (i <= mid) temp[k++] = a[i++];
        while (j <= right) temp[k++] = a[j++];
        for (int p = left; p <= right; ++p) a[p] = temp[p];
    };
    if (!a.empty()) sortRange(0, static_cast<int>(a.size()) - 1);
}

void quickSort(vector<int>& a) { // Average O(n log n), worst O(n^2).
    mt19937 rng(random_device{}());
    function<void(int, int)> sortRange = [&](int left, int right) {
        if (left >= right) return;
        uniform_int_distribution<int> pick(left, right);
        int pivotIndex = pick(rng);
        swap(a[pivotIndex], a[right]);
        int pivot = a[right], p = left;
        for (int i = left; i < right; ++i) if (a[i] < pivot) swap(a[i], a[p++]);
        swap(a[p], a[right]);
        sortRange(left, p - 1); sortRange(p + 1, right);
    };
    if (!a.empty()) sortRange(0, static_cast<int>(a.size()) - 1);
}

void heapSort(vector<int>& a) {
    priority_queue<int, vector<int>, greater<int>> minHeap(a.begin(), a.end());
    for (int& x : a) { x = minHeap.top(); minHeap.pop(); }
}

// ============================================================================
// 13. ARRAY / HASHING / TWO POINTER / SLIDING WINDOW
// ============================================================================
vector<int> twoSumIndices(const vector<int>& a, int target) {
    unordered_map<int, int> firstIndex;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        int need = target - a[i];
        if (firstIndex.count(need)) return {firstIndex[need], i};
        firstIndex.emplace(a[i], i);
    }
    return {};
}

long long maxSubarraySumKadane(const vector<int>& a) {
    if (a.empty()) return 0;
    long long current = a[0], best = a[0];
    for (int i = 1; i < static_cast<int>(a.size()); ++i) {
        current = max<long long>(a[i], current + a[i]);
        best = max(best, current);
    }
    return best;
}

vector<long long> prefixSums(const vector<int>& a) {
    vector<long long> pref(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); ++i) pref[i + 1] = pref[i] + a[i];
    return pref; // Sum [left..right] = pref[right+1] - pref[left].
}

int longestSubstringWithoutRepeating(const string& s) {
    vector<int> last(256, -1);
    int left = 0, best = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        unsigned char c = static_cast<unsigned char>(s[right]);
        left = max(left, last[c] + 1);
        last[c] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

long long countSubarraysWithSumK(const vector<int>& a, long long k) { // Handles negatives too.
    unordered_map<long long, long long> freq;
    freq[0] = 1;
    long long prefix = 0, answer = 0;
    for (int x : a) {
        prefix += x;
        if (freq.count(prefix - k)) answer += freq[prefix - k];
        ++freq[prefix];
    }
    return answer;
}

// ============================================================================
// 14. RECURSION / BACKTRACKING
// ============================================================================
void generateSubsets(int index, const vector<int>& a, vector<int>& current,
                     vector<vector<int>>& answer) {
    if (index == static_cast<int>(a.size())) { answer.push_back(current); return; }
    // Choice 1: exclude a[index].
    generateSubsets(index + 1, a, current, answer);
    // Choice 2: include a[index].
    current.push_back(a[index]);
    generateSubsets(index + 1, a, current, answer);
    current.pop_back(); // Undo choice (backtrack).
}

void generatePermutations(vector<int>& a, int index, vector<vector<int>>& answer) {
    if (index == static_cast<int>(a.size())) { answer.push_back(a); return; }
    for (int i = index; i < static_cast<int>(a.size()); ++i) {
        swap(a[index], a[i]);
        generatePermutations(a, index + 1, answer);
        swap(a[index], a[i]); // Restore before exploring next choice.
    }
}

// ============================================================================
// 15. DYNAMIC PROGRAMMING
// ============================================================================
long long fibonacciMemo(int n, vector<long long>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
}

long long fibonacciTabulation(int n) {
    if (n <= 1) return n;
    vector<long long> dp(n + 1, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

long long fibonacciSpaceOptimized(int n) {
    if (n <= 1) return n;
    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; ++i) {
        long long current = prev1 + prev2;
        prev2 = prev1; prev1 = current;
    }
    return prev1;
}

int climbStairs(int n) { // 1-step or 2-step; assumes answer fits int.
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; ++i) {
        int cur = prev1 + prev2;
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}

int knapsack01(const vector<int>& weight, const vector<int>& value, int capacity) {
    vector<int> dp(capacity + 1, 0);
    for (int i = 0; i < static_cast<int>(weight.size()); ++i) {
        for (int cap = capacity; cap >= weight[i]; --cap) // Descending prevents reusing item.
            dp[cap] = max(dp[cap], value[i] + dp[cap - weight[i]]);
    }
    return dp[capacity];
}

int coinChangeMinCoins(const vector<int>& coins, int amount) {
    const int BAD = amount + 1;
    vector<int> dp(amount + 1, BAD);
    dp[0] = 0;
    for (int coin : coins) {
        for (int x = coin; x <= amount; ++x) // Ascending allows unlimited use of this coin.
            dp[x] = min(dp[x], 1 + dp[x - coin]);
    }
    return dp[amount] == BAD ? -1 : dp[amount];
}

int longestCommonSubsequence(const string& a, const string& b) {
    int n = static_cast<int>(a.size()), m = static_cast<int>(b.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        if (a[i - 1] == b[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
        else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
    return dp[n][m];
}

int longestIncreasingSubsequence(const vector<int>& a) { // O(n log n), strictly increasing.
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return static_cast<int>(tails.size());
}

// ============================================================================
// 16. STRING ALGORITHM: KMP PATTERN SEARCH
// ============================================================================
vector<int> kmpPrefixFunction(const string& pattern) {
    int n = static_cast<int>(pattern.size());
    vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n;) {
        if (pattern[i] == pattern[len]) lps[i++] = ++len;
        else if (len > 0) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern) { // Match starting indices.
    vector<int> positions;
    if (pattern.empty()) return positions;
    vector<int> lps = kmpPrefixFunction(pattern);
    for (int i = 0, j = 0; i < static_cast<int>(text.size());) {
        if (text[i] == pattern[j]) { ++i; ++j; }
        if (j == static_cast<int>(pattern.size())) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < static_cast<int>(text.size()) && text[i] != pattern[j]) {
            if (j > 0) j = lps[j - 1];
            else ++i;
        }
    }
    return positions;
}

// ============================================================================
// 17. GREEDY / INTERVALS
// ============================================================================
vector<pair<int, int>> mergeIntervals(vector<pair<int, int>> intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<pair<int, int>> result;
    result.push_back(intervals[0]);
    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].first <= result.back().second)
            result.back().second = max(result.back().second, intervals[i].second);
        else result.push_back(intervals[i]);
    }
    return result;
}

} // namespace dsa

// Small smoke-test main. Remove or replace it when copying individual snippets.
int main() {
    using namespace dsa;

    // Tree example: levels=3 creates 1 + 2 + 4 = 7 nodes.
    mt19937 rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()));
    TreeNode* root = generateFullRandomTree(3, rng);
    cout << "Tree by level:\n";
    printTreeByLevel(root);
    cout << "Height in nodes: " << heightNodes(root) << '\n';
    cout << "Leaf count: " << countLeaves(root) << '\n';
    deleteTree(root);

    // A few standard library examples:
    vector<int> values = {7, 2, 9, 1, 5};
    mergeSort(values);
    cout << "Sorted: ";
    for (int x : values) cout << x << ' ';
    cout << '\n';

    return 0;
}
