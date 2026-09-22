# Informatics-ITS-Graph-Theory-class-Group-6

# Group Members

| Name                     | NRP        |
| ------------------------ | ---------- |
| Lina Fatima Azzahra Badr | 5025251168 |
| Naila Sa'ada Cahyani     | 5025251258 |

---
## A. Tarjan's Algorithm

Tarjan's algorithm is an efficient method for finding an Eulerian path in an undirected graph. It works by iteratively finding cycles in the graph and splicing them together into a single continuous path. A linked list is typically used to ensure that the splicing operation occurs in $O(1)$ constant time, allowing the algorithm to run efficiently in $O(E)$ time.

  
### Code Explanation

```cpp

// Splice cycles
while (it != path.end()) {
int u = *it;
// If the current vertex has unexplored incident edges
if (head[u] < adj[u].size()) {
// Find a cycle starting from u
list<int> cycle;
int curr = u;
// Traverse the graph to find a cycle
do {
bool advanced = false;
// Check remaining edges for the current vertex
while (head[curr] < adj[curr].size()) {
auto edge = adj[curr][head[curr]++];
int v = edge.first;
int id = edge.second;
// If the edge hasn't been used yet, include it in the cycle
if (!used[id]) {
used[id] = true;
cycle.push_back(v);
curr = v;
edges_used++;
advanced = true;
break;
}
} 
// If we couldn't advance but haven't reached the start, smthn is wrong
if (!advanced)
break;
} while (curr != u);
// Splice the newly found cycle
if (!cycle.empty()) {
auto next_it = next(it);
path.splice(next_it, cycle);
}
}
// Move to the next vertex
++it;

}
```

1. It initializes a `path` linked list with a starting vertex (node 1) and creates tracking arrays `head` and `used` to ensure each edge is only visited once.

2. The algorithm iterates through the vertices currently in the `path`. If it finds a vertex with unexplored incident edges, it begins to trace a new cycle starting from that vertex.

3. It continually adds unused edges to a temporary `cycle` list until it loops back to the starting vertex of the cycle.

4. Once a complete cycle is found, it uses the `splice` function to insert the newly found cycle into the main `path` at the current iterator position. This process repeats until all edges have been explored.

  

### Input Format

- **Line 1:** `n m` (number of vertices `n` and number of edges `m`)

- **Line 2 to m+1:** `u v` (Repeated for every edge, representing an undirected connection between node `u` and node `v`)

Example:

```
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5
```

  

### Output Format

Prints the space-separated sequence of vertices representing the Eulerian path. If no valid Eulerian path can be formed (e.g., if a vertex has an odd degree or the graph is disconnected), it outputs `IMPOSSIBLE`.

### Result of Sample Run

![Tarjan's algorithm sample run](Assets/Pasted%20image%2020260922142211.png)

---

## B. Fleury's Algorithm

Fleury's algorithm is a classical approach to finding an Eulerian path or path. The core rule of Fleury's algorithm is to traverse edges one by one, always avoiding "bridges" (edges whose removal would disconnect the unvisited parts of the graph) unless there is no other choice. Because it must repeatedly check for bridges using Graph Traversal (like DFS), it typically runs in $O(E^2)$ time.

  

### Code Explanation

```cpp

// Check if edge (u, v) is a valid next edge
bool isValidNextEdge(int u, int v, vector<vector<int>> &adj, int n) {

int degree = 0;

for (int neighbor : adj[u]) {

if (neighbor != -1)
degree++;
}
// It's valid valid if it's the only adjacent vertex

if (degree == 1)

return true;

// Count reachable vertices

vector<bool> visited1(n + 1, false);

int count1 = dfs(u, adj, visited1);

// Remove edge (u, v)
auto itU = find(adj[u].begin(), adj[u].end(), v);

int idxU = distance(adj[u].begin(), itU);

adj[u][idxU] = -1;

  
auto itV = find(adj[v].begin(), adj[v].end(), u);

int idxV = distance(adj[v].begin(), itV);

adj[v][idxV] = -1;

// Count reachable vertices
vector<bool> visited2(n + 1, false);
int count2 = dfs(u, adj, visited2);


// Add the edge back
adj[u][idxU] = v;
adj[v][idxV] = u;

  
// If count1 > count2, then edge (u, v) is a bridge

return (count1 <= count2);

}

```

1. The algorithm starts at a valid vertex and loops until all edges are consumed (`edges_left > 0`).

2. For the current vertex, it evaluates adjacent edges to see if they are a valid move using `isValidNextEdge`.

3. Inside `isValidNextEdge`, it counts reachable vertices using a Depth-First Search (`dfs`) before and after temporarily removing the candidate edge. If the reachable count drops after removal, the edge is a bridge.

4. It only chooses a bridge if it's the absolute last remaining edge for that vertex (i.e., `degree == 1`). Once a valid edge is selected, it is permanently removed from the graph, and the traversal continues from the next vertex.

  

### Input Format

Same as Tarjan's Algorithm.

  

### Output Format

Same as Tarjan's Algorithm.

  
### Result of Sample Run

![Fleury's algorithm sample run](Assets/Pasted%20image%2020260922142251.png)
---

## C. Hierholzer's Algorithm

Hierholzer's algorithm is another highly efficient algorithm for finding Eulerian paths, operating in $O(E)$ time. Unlike Tarjan's algorithm, which uses linked lists for splicing, Hierholzer's algorithm elegantly uses a stack to trace paths and backtrack when it reaches a dead end. When backtracking, it adds vertices to the final Eulerian path.

  

### Code Explanation

```cpp

// Hierholzer's algorithm

while (!stack.empty()) {
int u = stack.back();
bool found = false;


// Find the next unused edge

while (head[u] < adj[u].size()) {
auto edge = adj[u][head[u]++];
int v = edge.first;
int id = edge.second;

if (!used[id]) {
used[id] = true;
stack.push_back(v); // Move to the neighbor
found = true;

break;

}

}

  
// If no more unused edges from u, add it to the path and backtrack

if (!found) {
path.push_back(u);
stack.pop_back();
}
}

```

1. The algorithm begins by pushing a starting vertex onto a `stack`.

2. It continually peeks at the top vertex `u` of the stack. It then looks for any unused incident edges connected to `u` using the `head` array.

3. If an unused edge is found, it marks the edge as used and pushes the neighboring vertex `v` onto the stack, essentially walking forward through the graph.

4. If the vertex `u` has no more unused edges left (a dead end), the algorithm pops `u` from the stack and appends it to the final `path`. Because it builds the path during the backtracking phase, the resulting path is constructed in reverse order, which is still mathematically valid for a cycle.

  

### Input Format

Same as Tarjan's Algorithm.

  

### Output Format

Same as Tarjan's Algorithm.

### Result of Sample Run

![Hierholzer's algorithm sample run](Assets/Pasted%20image%2020260922142340.png)

---

## D. Comparison of the Algorithms

| Feature | Tarjan's (Cycle-Splicing) | Fleury's Algorithm | Hierholzer's Algorithm |
| :--- | :--- | :--- | :--- |
| **Time Complexity** | $O(E)$ | $O(E^2)$ | $O(E)$ |
| **Space Complexity**| $O(V + E)$ | $O(V + E)$ | $O(V + E)$ |
| **Data Structure** | Linked List (`std::list`) | None specific (DFS used) | Stack (`std::vector`) |
| **Approach** | Splices independent cycles | Avoids cutting bridges | Backtracks at dead-ends |
| **Practical Speed** | Fast, but has linked-list overhead | Very Slow on large graphs | **Fastest Among the Three** |

### Which one is the best?
**Hierholzer's Algorithm is the best** among the three.

**Why?**
1. Funfact: Hierholzer's algorithm was explicitly invented for Eulerian circuits and paths. Tarjan's was invented for general graph connectivity (bridges and articulation points) and only happens to work as a fix forFleury's efficiency.
2. It achieves the theoretically best $O(E)$ time. Fleury's algorithm wastes time by continuously scanning for bridges, it will be inefficient if there are many bridges.
3. Hierholzer's relies on a Stack. This fits well with modern CPU cache architectures, taking advantage of spatial locality to make memory reads/writes faster. Tarjan's/Cycle-Splicing requires Linked Lists, which scatter memory nodes and cause expensive CPU cache misses.
4. Hierholzer's logic maps directly to a simple loop mimicking a natural graph walk with backtracking. There's no need to stitch sub-cycles together or write a separate heavy subroutine just to track graph components.

---

## Prerequisites to Run the Code

1. **C++ Compiler**: You must have a C++ compiler installed (like `g++` or `clang++` on macOS/Linux, or MinGW on Windows). The code uses features up to C++17.

2. **An Interactive Terminal/IDE**: You must run it in a terminal, command prompt, or a compatible IDE.

  

**To compile and run a script from the terminal, use the following commands:**

  

```bash

# Compile the code

g++ -std=c++17 <filename>.cpp -o <filename>


# Run the executable

./<filename>

```

---

## Resources

- **Eulerian Path: https://en.wikipedia.org/wiki/Eulerian_path
- https://cp-algorithms.com/graph/euler_path.html
- **Tarjan's Algorithm**: https://www.geeksforgeeks.org/dsa/tarjan-algorithm-find-strongly-connected-components/
- **Hierholzer's Algorithm**: https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/
- **Fleury's Algorithm**: https://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/
- **CSES Problem Set**: https://cses.fi/problemset/
- **The prompt**: https://share.gemini.google/7JsvM7kPuYnI