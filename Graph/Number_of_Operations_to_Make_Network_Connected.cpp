class Solution {
public:
    vector<int> parent;
    vector<int> rank;
    int find(int u){
        if(parent[u]==u){
            return u;
        }
        return parent[u]=find(parent[u]);
    }
    bool Union(int u,int v){
        int parent_u=find(u);
        int parent_v=find(v);
        if(parent_u==parent_v){
            return false;
        }
        if(rank[parent_u]==rank[parent_v]){
            parent[parent_v]=parent_u;
            rank[parent_u]++;
        }
        else if(rank[parent_u]>rank[parent_v]){
            parent[parent_v]=parent_u;
        }
        else{
            parent[parent_u]=parent_v;
        }
        return true;
    }
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1)
            return -1;

        parent.resize(n);
        rank.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        int components = n;

        for (auto &edge : connections) {
            int u = edge[0];
            int v = edge[1];

            if (Union(u, v)) {
                components--;
            }
        }

        return components - 1;
    }
};