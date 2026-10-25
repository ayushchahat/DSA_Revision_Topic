class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj,
             vector<int>& vis, stack<int>& st) {
        vis[node] = 1;

        for (int neighbor : adj[node]) {
            if (!vis[neighbor]) {
                dfs(neighbor, adj, vis, st);
            }
        }

        st.push(node);
    }

    vector<int> topoSort(int V, vector<vector<int>>& adj) {
        vector<int> vis(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, adj, vis, st);
            }
        }

        vector<int> topo;

        while (!st.empty()) {
            topo.push_back(st.top());
            st.pop();
        }

        return topo;
    }
};