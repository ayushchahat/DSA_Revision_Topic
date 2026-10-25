class Solution {
public:
    int timer = 1;

    void dfs(int node, int parent, vector<int>& vis,
             vector<int>& tin, vector<int>& low,
             vector<int> adj[], vector<vector<int>>& bridges) {

        vis[node] = 1;
        tin[node] = low[node] = timer++;

        for (auto adjNode : adj[node]) {

            // Ignore the edge back to parent
            if (adjNode == parent) continue;

            if (!vis[adjNode]) {
                dfs(adjNode, node, vis, tin, low, adj, bridges);

                // Update low time after returning from DFS
                low[node] = min(low[node], low[adjNode]);

                // Bridge condition
                if (low[adjNode] > tin[node]) {
                    bridges.push_back({node, adjNode});
                }
            }
            else {
                // Back edge to an already visited node
                low[node] = min(low[node], tin[adjNode]);
            }
        }
    }

    vector<vector<int>> criticalConnections(
        int V, vector<int> adj[]) {

        vector<int> vis(V, 0);
        vector<int> tin(V, -1);
        vector<int> low(V, -1);
        vector<vector<int>> bridges;

        timer = 1;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, adj, bridges);
            }
        }

        return bridges;
    }
};

/*
What are tin[] and low[]?
- tin[node]: The time when the node is first visited by DFS.
- low[node]: The earliest discovery time reachable from that node's DFS subtree using tree edges and at most one back edge.
The most important condition
\[
\boxed{low[v] > tin[u]}
\]

Here, u is the parent and v is its DFS child.

If low[v] > tin[u], there is no back edge from v's subtree to u or any ancestor of u. Therefore, removing edge (u, v) disconnects the graph, making it a bridge.

Remember these two updates:
low[node] = min(low[node], low[adjNode]);  // After DFS returns


low[node] = min(low[node], tin[adjNode]); // Already visited neighbor


Complexity: Time \(O(V+E)\), space \(O(V)\) auxiliary space, excluding the graph and returned bridges.

Note: This implementation assumes a simple undirected graph without parallel edges. If parallel edges are possible, track the parent edge ID rather than skipping every edge to the parent vertex.

*/