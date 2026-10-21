/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
private:
    TreeNode* first;
    TreeNode* last;
    TreeNode* middle;
    TreeNode* prev;

public:
    void solve(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        solve(root->left);
        if ( root->val < prev->val) {
            if (first == NULL) {
                first = prev;
                middle = root;
            }
            else {
                last = root;
            }
        }
        prev = root;
        solve(root->right);
    }
    void recoverTree(TreeNode* root) {
        first = NULL;
        last = NULL;
        middle = NULL;
        prev = new TreeNode(INT_MIN);
        solve(root);
        if (last == NULL) {
            swap(first->val, middle->val);
        } else {
            swap(first->val, last->val);
        }
    }
};