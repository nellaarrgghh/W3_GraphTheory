#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  if (!(cin >> n >> m))
    return 0;

  // Adjacency list storing pairs
  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> degree(n + 1, 0);

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
    degree[u]++;
    degree[v]++;
  }

  // Even degrees = eulerian
  for (int i = 1; i <= n; ++i) {
    if (degree[i] % 2 != 0) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  vector<int> path;
  vector<int> stack;
  stack.push_back(1);

  // Keep track of used edges
  vector<bool> used(m, false);
  // Keep track of the current neighbor
  vector<int> head(n + 1, 0);

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

  // If the path doesn't contain all edges, the graph is disconnected
  if (path.size() != m + 1) {
    cout << "IMPOSSIBLE\n";
  } else {
    // output
    for (int i = 0; i < path.size(); ++i) {
      cout << path[i] << (i + 1 == path.size() ? "" : " ");
    }
    cout << "\n";
  }

  return 0;
}
