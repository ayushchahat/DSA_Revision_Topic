class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int, int>>> adj(V);

        // Build adjacency list: {neighbor, weight}
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // Undirected graph
        }

        vector<int> dist(V, INT_MAX);

        // Min-heap: {distance, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            // Ignore outdated distances
            if (d > dist[node]) continue;

            for (auto &[neighbor, weight] : adj[node]) {
                if (d + weight < dist[neighbor]) {
                    dist[neighbor] = d + weight;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }

        return dist;
    }
};