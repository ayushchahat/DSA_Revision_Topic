class Solution {
private:
    vector<vector<long long>> PT;

public:
    int solve(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2)
            return 1;

        vector<int> left, right;
        int root = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] > root)
                right.push_back(nums[i]);
            else
                left.push_back(nums[i]);
        }

        int x = solve(left);
        int y = solve(right);

        long long z = PT[n - 1][left.size()];

        return (long long)x * y % 1000000007 * z % 1000000007;
    }
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        int mod = 1000000007;
        PT.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            PT[i] = vector<long long>(i + 1, 1);
            for (int j = 1; j < i; j++) {
                PT[i][j] = (PT[i - 1][j - 1] + PT[i - 1][j]) % mod;
            }
        }
        return solve(nums) - 1;
    }
};