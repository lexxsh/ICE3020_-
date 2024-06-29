#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void DFS(int index, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& result) {
    visited[index] = true;
    result.push_back(index);
    for (int next : graph[index]) {
        if (!visited[next])
            DFS(next, graph, visited, result);
    }
}

void BFS(int index, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& result) {
    queue<int> q;
    q.push(index);
    visited[index] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current);
        for (int next : graph[current]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

int main() {
    int N, M, V;
    cin >> N >> M >> V;
    vector<vector<int>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= N; ++i) {
        sort(graph[i].begin(), graph[i].end());
    }
    vector<int> dfs_result;
    vector<int> bfs_result;
    vector<bool> visited(N + 1, false);
    DFS(V, graph, visited, dfs_result);
    fill(visited.begin(), visited.end(), false);
    BFS(V, graph, visited, bfs_result);


    for (int node : dfs_result) cout << node << " ";
    cout << "\n";
    
    
    for (int node : bfs_result) cout << node << " ";
    cout << "\n";
    return 0;
}
