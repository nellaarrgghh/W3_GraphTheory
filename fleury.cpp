#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// DFS to count reachable vertices
int dfs(int u, vector<vector<int>> &adj, vector<bool> &visited) {
  visited[u] = true;
  int count = 1;
  for (int v : adj[u]) {
    if (v != -1 && !visited[v]) {
      count += dfs(v, adj, visited);
    }
  }
  return count;
}

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  if (!(cin >> n >> m))
    return 0;

  vector<vector<int>> adj(n + 1);
  vector<int> degree(n + 1, 0);

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    degree[u]++;
    degree[v]++;
  }

  // Check Eulerian
  for (int i = 1; i <= n; ++i) {
    if (degree[i] % 2 != 0) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  // Check graph connectivity
  vector<bool> visited(n + 1, false);
  int reachable = dfs(1, adj, visited);
  int vertices_with_edges = 0;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] > 0)
      vertices_with_edges++;
  }

  if (reachable < vertices_with_edges) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  vector<int> path;
  int curr = 1;
  path.push_back(curr);

  int edges_left = m;
  while (edges_left > 0) {
    for (int i = 0; i < adj[curr].size(); ++i) {
      int v = adj[curr][i];
      if (v != -1 && isValidNextEdge(curr, v, adj, n)) {
        path.push_back(v);

        // Remove edge
        adj[curr][i] = -1;
        auto itV = find(adj[v].begin(), adj[v].end(), curr);
        *itV = -1;

        curr = v;
        edges_left--;
        break;
      }
    }
  }

  for (int i = 0; i < path.size(); ++i) {
    cout << path[i] << (i + 1 == path.size() ? "" : " ");
  }
  cout << "\n";

  return 0;
}
