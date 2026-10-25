
class Solution {
public:
    // Step 1: DFS and store finishing order
    void dfs(int node, stack<int>& st,
             vector<bool>& vis, vector<int> adj[]) {
        vis[node] = true;

        for (auto adjNode : adj[node]) {
            if (!vis[adjNode]) {
                dfs(adjNode, st, vis, adj);
            }
        }

        st.push(node);
    }

    // Step 3: DFS on reversed graph
    void dfs_traversal(int node, vector<bool>& vis,
                       vector<int> reverseAdj[]) {
        vis[node] = true;

        for (auto adjNode : reverseAdj[node]) {
            if (!vis[adjNode]) {
                dfs_traversal(adjNode, vis, reverseAdj);
            }
        }
    }

    int kosaraju(int V, vector<int> adj[]) {
        // Step 1: Find finishing order
        stack<int> st;
        vector<bool> vis(V, false);

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, st, vis, adj);
            }
        }

        // Step 2: Reverse all edges
        vector<int> reverseAdj[V];

        for (int i = 0; i < V; i++) {
            for (auto v : adj[i]) {
                reverseAdj[v].push_back(i);
            }
        }

        // Step 3: Count SCCs in stack order
        fill(vis.begin(), vis.end(), false);

        int cnt = 0;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!vis[node]) {
                dfs_traversal(node, vis, reverseAdj);
                cnt++;
            }
        }

        return cnt;
    }
};
