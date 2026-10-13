
// url=https://leetcode.com/problems/apply-operations-on-array-to-maximize-sum-of-squares/description/?envType=daily-question&envId=2026-10-12

class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1000000007;
        int cnt[32] = {0};

        // Count frequency of each set bit
        for (int num : nums) {
            for (int bit = 0; bit < 32; bit++) {
                if (num & (1LL << bit)) {
                    cnt[bit]++;
                }
            }
        }

        long long ans = 0;

        // Construct k maximum possible numbers
        for (int i = 0; i < k; i++) {
            long long num = 0;

            for (int bit = 0; bit < 32; bit++) {
                if (cnt[bit] > 0) {
                    num |= (1LL << bit);
                    cnt[bit]--;
                }
            }

            ans = (ans + (num * num) % MOD) % MOD;
        }

        return ans;
    }
};
