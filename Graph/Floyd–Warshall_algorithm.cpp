class Solution {
public:
    void floydWarshall(vector<vector<int>>& dist) {
        int n = dist.size();

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    if (dist[i][k] != 1e8 &&
                        dist[k][j] != 1e8) {

                        dist[i][j] = min(
                            dist[i][j],
                            dist[i][k] + dist[k][j]
                        );
                    }
                }
            }
        }
    }
};

/*




How it works
The key idea is to check whether going from i to j through an intermediate vertex k gives a shorter path.
\[
dist[i][j] = \min(dist[i][j],\ dist[i][k]+dist[k][j])
\]

- k: intermediate vertex
- i: source vertex
- j: destination vertex
Remember: The k loop must be outermost.
Complexity
- Time: \(O(V^3)\)
- Space: \(O(1)\) auxiliary space if the distance matrix is updated in place.
Floyd–Warshall supports negative edge weights, but not negative-weight cycles. After the algorithm, if dist[i][i] < 0 for any vertex i, a negative cycle exists.

*/