#include<iostream>
#include<vector>
#include<queue>


#define x first
#define y second
using namespace std;

typedef pair<int, int> p;

vector<p> g[1010];
priority_queue<int> heap[1010];
int n, m, k;

void kth_dijkstra() {
	priority_queue< p, vector<p>, greater<p> > pq; pq.push({ 0, 1 }); heap[1].push(0);
	while (pq.size()) {
		int now = pq.top().y;
		int cost = pq.top().x;
		pq.pop();

		for (auto i : g[now]) {
			int nxt = i.x;
			int nxtCost = i.second + cost;
			if (heap[nxt].size() < k) {
				heap[nxt].push(nxtCost);
				pq.push({ nxtCost, nxt });
			}
			else if (heap[nxt].top() > nxtCost) {
				heap[nxt].pop();
				heap[nxt].push(nxtCost);
				pq.push({ nxtCost, nxt });
			}
		}
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		g[a].push_back({ b, c });
	}
	kth_dijkstra();

	for (int i = 1; i <= n; i++) {
		if (heap[i].size() != k) cout << "-1\n";
		else cout << heap[i].top() << "\n";
	}
}