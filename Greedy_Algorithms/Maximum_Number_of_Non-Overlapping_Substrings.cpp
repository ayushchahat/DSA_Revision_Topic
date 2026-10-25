class Solution {
public:
    static bool myCmp(vector<int> &a,vector<int> &b){
        if (a[1] != b[1]) {
            return a[1] < b[1];
        }
        return a[0] < b[0];
    }
    vector<string> maxNumOfSubstrings(string s) {
        int n=s.size();
        vector<int> first(26,INT_MAX);
        vector<int> last(26,-1);
        //find first and last occurance
        for(int i=0;i<n;i++){
            int ch=s[i]-'a';
            first[ch]=min(first[ch],i);
            last[ch] = i;
        }

        //form the interval
        vector<vector<int>> interval;
        for(int i=0;i<26;i++){
            if(last[i]==-1){
                continue;
            }
            int l=first[i];
            int r=last[i];
            //check for vaild interval
            bool valid=true;
            for(int j=l;j<=r;j++){
                int ch=s[j]-'a';
                if(first[ch]<l){
                    valid=false;
                    break;
                }
                r = max(r, last[ch]);
            }
            if(valid){
                interval.push_back({l,r});
            }
        }

        //find smallest interval using merge
        sort(interval.begin(),interval.end(),myCmp);
        vector<vector<int>>  ans;
        int l=-1;
        for(int i=0;i<interval.size();i++){
            if(l==-1){
                l=interval[i][1];
                ans.push_back(interval[i]);
            }
            else if(l<interval[i][0]){
                ans.push_back(interval[i]);
                l=interval[i][1];
            }
        }
        vector<string> res;
        for(int i=0;i<ans.size();i++){
            int st=ans[i][0];
            int e=ans[i][1];
            res.push_back(s.substr(st,e-st+1));
        }
        return res;
    }
};