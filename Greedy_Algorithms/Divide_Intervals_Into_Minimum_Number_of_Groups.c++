class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        int n=intervals.size();
        sort(intervals.begin(),intervals.end());
        map<int, vector<vector<int>>> mp;
        for(int i=0;i<n;i++){
            int cnt=0;
            if(mp.empty()){
                mp[cnt].push_back(intervals[i]);
            }
            else{
                while(mp.find(cnt)!=mp.end() && intervals[i][0]<=mp[cnt].back()[1]){
                    cnt++;
                }
                mp[cnt].push_back(intervals[i]);
            }
        }
        return mp.size()
    }
};

// TLE

class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        sort(begin(intervals), end(intervals));

        priority_queue<int, vector<int>, greater<int>> pq; //stores end point of groups

        for(vector<int>& interval : intervals) {
            int start = interval[0];
            int end   = interval[1];

            if(!pq.empty() && pq.top() < start) {
                pq.pop();
            }
            pq.push(end);
        }

        return pq.size();
    }
};