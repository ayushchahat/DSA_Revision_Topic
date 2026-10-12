
class Solution {
public:
    void solve(int i, int n, long long sum,
               vector<int>& comb,
               vector<vector<int>>& ans,
               vector<int>& candidates, int target) {

        if (sum == target) {
            ans.push_back(comb);
            return;
        }

        if (i >= n || sum > target) {
            return;
        }

        // TAKE current element
        comb.push_back(candidates[i]);

        solve(i + 1, n, sum + candidates[i],
              comb, ans, candidates, target);

        // BACKTRACK
        comb.pop_back();

        // NOT TAKE: skip all duplicate values
        int j = i + 1;

        while (j < n && candidates[j] == candidates[i]) {
            j++;
        }

        solve(j, n, sum, comb, ans, candidates, target);
    }

    vector<vector<int>> combinationSum2(
        vector<int>& candidates, int target) {

        sort(candidates.begin(), candidates.end());

        int n = candidates.size();
        vector<vector<int>> ans;
        vector<int> comb;

        solve(0, n, 0, comb, ans, candidates, target);

        return ans;
    }
};


// Take → Move one step to allow duplicates; Not Take → Skip all duplicates to avoid repeating the same combination.