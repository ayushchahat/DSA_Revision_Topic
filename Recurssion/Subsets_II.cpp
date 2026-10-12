class Solution {
public:
    void solve(int i,int n,vector<int>& nums,vector<vector<int>> &ans,vector<int> &curr){
        if(i>=n){
            ans.push_back(curr);
            return;
        }
        curr.push_back(nums[i]);
        solve(i+1,n,nums,ans,curr);
        curr.pop_back();
        int j=i+1;
        while(j<n && nums[i]==nums[j]){
            j++;
        }
        solve(j,n,nums,ans,curr);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int> curr;
        int n=nums.size();
        vector<vector<int>> ans;
        solve(0,n,nums,ans,curr);
        return ans; 
    }
};