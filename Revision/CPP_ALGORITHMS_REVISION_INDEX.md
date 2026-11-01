# C++17 Algorithms Interview Revision Index

Companion to `cpp_algorithms_interview_reference.cpp`.

## Recommended revision order

### Priority 1 — must be fluent

1. **Sorting:** Bubble, Selection, Insertion, Merge (recursive + iterative), Quick, Heap; know stability, in-place behavior, and complexity.
2. **Binary search:** normal search, lower/upper bound, first/last occurrence, rotated sorted array, binary search on answer.
3. **Strings:** KMP prefix/LPS construction and matching, Z algorithm, Rabin–Karp rolling hash.
4. **Array patterns:** two pointers, fixed/variable sliding window, prefix sums, difference arrays, Kadane, hashmap prefix sum.
5. **Recursion/backtracking:** subsets, permutations (including duplicates), combination sum, balanced parentheses.
6. **Core DP:** climbing stairs, house robber, 0/1 vs unbounded knapsack, coin change, subset sum, LIS, LCS, edit distance.
7. **Graphs:** BFS, DFS, connected components, cycle detection, bipartite check, topological sorting, Dijkstra.

### Priority 2 — very useful

- Counting sort, radix sort, inversion count, Quickselect, Dutch National Flag.
- Monotonic stack: next greater element, largest histogram rectangle; monotonic deque: sliding-window maximum.
- Greedy intervals, activity/meeting scheduling, fractional knapsack.
- Bellman–Ford, Floyd–Warshall, 0-1 BFS, DSU, Kruskal, Prim.
- SCC (Kosaraju), bridges, articulation points.
- Manacher's longest palindromic substring.
- Matrix-chain multiplication and N-Queens.

### Priority 3 — revise if time remains

- Modular arithmetic, extended Euclid, modular inverse, sieve, bit tricks.
- Advanced DP state design and graph edge cases.

## File section map

| Section | Main implementations | Typical complexity |
|---|---|---|
| 1. Sorting | Bubble, Selection, Insertion, Merge (top-down + bottom-up), Quick (3-way), Heap, Counting, Radix, inversion count, Quickselect, sort 0/1/2 | Usually O(n log n); simple quadratic sorts O(n²) |
| 2. Searching | Linear, Binary, lower/upper bound, first/last, rotated array, answer-space search, integer square root | O(n) or O(log n) |
| 3. Strings | Prefix/LPS, KMP, Z, Rabin–Karp, Manacher, longest unique substring | Mostly O(n+m) or O(n) |
| 4. Arrays | Prefix/difference, Kadane, two pointers, sliding window, prefix hashmap, monotonic stack/deque | Mostly O(n) |
| 5. Greedy | Merge intervals, interval selection, meeting rooms, fractional knapsack | Usually O(n log n) |
| 6. Backtracking | Subsets, unique subsets, permutations, unique permutations, combination sum, parentheses, N-Queens | Exponential/output-sensitive |
| 7. DP | Fibonacci, stairs, robber, knapsack, coin change, subset sum, LIS, LCS, edit distance, grid DP, MCM | Varies; commonly O(n·target) or O(n·m) |
| 8. Graphs | BFS/DFS, cycles, bipartite, topo, shortest paths, DSU, MST, SCC, bridges, articulation points | Commonly O(V+E), Dijkstra O((V+E)logV), Floyd O(V³) |
| 9. Math/bits | GCD/LCM, sieve, modular power/inverse, bit operations, XOR | Often O(log n), sieve O(n log log n) |

## Important algorithm selection rules

- **Unweighted shortest path:** BFS.
- **Weights are only 0 or 1:** 0-1 BFS.
- **Non-negative weighted shortest path:** Dijkstra.
- **Negative edges:** Bellman–Ford; use it to detect reachable negative cycles.
- **All-pairs shortest paths on a small graph:** Floyd–Warshall.
- **Minimum spanning tree:** Kruskal + DSU or Prim.
- **Directed acyclic graph ordering:** Kahn's algorithm or DFS topological sort.
- **Pattern search in a string:** KMP or Z for deterministic linear time; Rabin–Karp for rolling-hash use cases.
- **Maximum subarray sum:** Kadane.
- **Range sum queries with static array:** prefix sums.
- **Many range increment updates:** difference array.
- **Subarray sum equals k (negative values allowed):** prefix sum + hashmap.
- **Fixed-size window:** sliding window; **max/min per window:** monotonic deque.
- **Next greater/smaller or histogram:** monotonic stack.
- **0/1 choice DP:** iterate capacity backwards in 1D compression.
- **Unbounded choice DP:** iterate capacity forwards.
- **Strict LIS length:** patience-sorting idea with `lower_bound` (O(n log n)).

## Complexity and correctness reminders

- Merge sort is stable and O(n log n), but uses O(n) extra memory.
- Quick sort is expected O(n log n); worst case is O(n²). Randomized pivot reduces the chance of adversarial input.
- Heap sort is O(n log n), in-place, and not stable.
- Counting sort depends on the value range, not just n. Avoid it for a huge sparse range.
- Radix sort here handles signed 32-bit integers.
- Binary search requires sorted data or a monotonic true/false predicate.
- Sliding-window shrink logic for a target sum generally relies on non-negative array elements. Use prefix sums + hashmap when negatives are allowed.
- Dijkstra must not be used with negative edge weights.
- Topological sorting applies to directed acyclic graphs.
- The provided 1D subset-sum implementation assumes non-negative values.
- `coinChangeMinimum` and the unbounded-knapsack implementation require positive item values/weights.

## How to practise each implementation

For each algorithm, be able to do these without looking at the code:

1. Explain the core idea in two or three sentences.
2. State the time and auxiliary-space complexity.
3. State the required assumptions (sorted input, non-negative weights, DAG, etc.).
4. Dry-run a normal case, an empty/single-element case, and a boundary case.
5. Write the implementation from memory and test it against a small brute-force example when possible.

## DP interview checklist

Before coding a DP problem, say:

- `dp[state]` represents what exact quantity?
- What choices or transitions lead to this state?
- What are the base cases?
- Is the answer at one state or an aggregate over states?
- What is the evaluation order?
- Can I compress dimensions? If yes, which loop direction preserves the previous layer?

A useful distinction:

- **0/1 knapsack:** each item is used at most once; compressed capacity loop goes downward.
- **Unbounded knapsack / coin change:** an item can be reused; capacity loop generally goes upward.

