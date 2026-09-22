#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // n = number of vertices, m = number of edges
  int n, m;
  if (!(cin >> n >> m))
    return 0;

  // Adjacency list storing pairs
  // degree stores the number of incident edges
  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> degree(n + 1, 0);

  // Read edges and fill adjacency list and degrees
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
    degree[u]++;
    degree[v]++;
  }

  // Eulerian check
  for (int i = 1; i <= n; ++i) {
    if (degree[i] % 2 != 0) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  // Tracking arrays
  vector<bool> used(m, false);
  vector<int> head(n + 1, 0);

  // linked list to splice cycles
  list<int> path;
  path.push_back(1);

  // Iterator pointing to the current vertex in the main path
  auto it = path.begin();
  int edges_used = 0;

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
  // If there are no solutions
  if (edges_used != m) {
    cout << "IMPOSSIBLE\n";
  } else {
    // Print the final Eulerian path
    for (auto node : path) {
      cout << node << " ";
    }
    cout << "\n";
  }

  return 0;
}
