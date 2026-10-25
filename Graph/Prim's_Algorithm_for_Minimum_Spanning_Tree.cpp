class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        vector<int> vis(V, 0);
        int sum = 0;

        // {weight, node}
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [wt, node] = pq.top();
            pq.pop();

            if (vis[node]) continue;

            vis[node] = 1;
            sum += wt;

            for (auto &edge : adj[node]) {
                int neighbor = edge[0];
                int weight = edge[1];

                if (!vis[neighbor]) {
                    pq.push({weight, neighbor});
                }
            }
        }

        return sum;
    }
};

/*
Complexity
- Time: \(O(E\log E)\) using a priority queue.
- Space: \(O(V+E)\), including the graph representation.
*/