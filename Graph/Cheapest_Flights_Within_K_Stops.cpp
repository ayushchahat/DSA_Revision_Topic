class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for(int i=0;i<flights.size();i++){
            int u=flights[i][0];
            int v=flights[i][1];
            int price=flights[i][2];
            adj[u].push_back({v,price});
        }
        vector<vector<int>> destPrice(n,vector<int> (k + 2,INT_MAX));
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
        pq.push({0,{0,src}});
        destPrice[src][0]=0;
        while(!pq.empty()){
            int currNode=pq.top().second.second;
            int currStops=pq.top().second.first;
            int currPrice=pq.top().first;
            pq.pop();
            if (currPrice > destPrice[currNode][currStops])
                continue;

            // Reached destination
            if (currNode == dst)
                return currPrice;

            // Cannot take more flights
            if (currStops == k + 1)
                continue;
            
            for(auto it:adj[currNode]){
                int neighbor=it.first;
                int stopPrice=it.second;
                if(currStops<=k &&destPrice[neighbor][currStops+1]>currPrice+stopPrice ){
                    destPrice[neighbor][currStops+1]=currPrice+stopPrice;
                    pq.push({currPrice+stopPrice,{currStops+1,neighbor}});
                }
            }
        }
        return -1;
    }
};