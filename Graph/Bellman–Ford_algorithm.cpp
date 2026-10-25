class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e8);
        dist[src] = 0;

        // Relax all edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            for (auto &e : edges) {
                int u = e[0];
                int v = e[1];
                int wt = e[2];

                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Check for negative-weight cycle
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];

            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1};
            }
        }

        return dist;
    }
};

/*
How to remember it
1. Initialize all distances to infinity and dist[src] = 0.
2. Relax every edge V - 1 times.
3. Relax once more to check for a reachable negative-weight cycle.
Relaxation means checking whether going through u gives a shorter path to v:
\[
dist[v] = \min(dist[v], dist[u] + wt)
\]

Bellman–Ford vs. Dijkstra
Feature	Bellman–Ford	Dijkstra
Negative edges	Yes	No
Negative cycle detection	Yes	No
Time complexity	\(O(VE)\)	\(O((V+E)\log V)\) with a heap

Note: The code uses the common GFG convention that 1e8 represents infinity and {-1} indicates a reachable negative-weight cycle.
*/