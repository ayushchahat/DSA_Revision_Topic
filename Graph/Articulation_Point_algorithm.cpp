class Solution {
public:
    int timer = 1;

    void dfs(int node, int parent,
             vector<int>& vis,
             vector<int>& tin,
             vector<int>& low,
             vector<int> adj[],
             vector<int>& mark) {

        // Mark the node visited and assign its discovery time
        vis[node] = 1;
        tin[node] = low[node] = timer++;

        int child = 0;  // Number of DFS tree children

        for (auto adjNode : adj[node]) {

            // Ignore the edge back to the parent
            if (adjNode == parent) continue;

            // If the neighbor has not been visited
            if (!vis[adjNode]) {
                child++;

                dfs(adjNode, node, vis, tin, low, adj, mark);

                // Update low time using the child's low time
                low[node] = min(low[node], low[adjNode]);

                // If the child cannot reach node or an ancestor
                // of node using a back edge, node is an articulation point.
                if (low[adjNode] >= tin[node] && parent != -1) {
                    mark[node] = 1;
                }
            }
            else {
                // Back edge to an already visited neighbor
                low[node] = min(low[node], tin[adjNode]);
            }
        }

        // Special case: DFS root is an articulation point
        // only if it has more than one DFS tree child.
        if (parent == -1 && child > 1) {
            mark[node] = 1;
        }
    }

    vector<int> articulationPoints(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        vector<int> tin(V, -1);
        vector<int> low(V, -1);
        vector<int> mark(V, 0);

        timer = 1;

        // Handle disconnected graphs too
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, adj, mark);
            }
        }

        vector<int> ans;

        // Return articulation points in increasing order
        for (int i = 0; i < V; i++) {
            if (mark[i]) {
                ans.push_back(i);
            }
        }

        // Common GFG convention: -1 if none exist
        if (ans.empty()) {
            return {-1};
        }

        return ans;
    }
};