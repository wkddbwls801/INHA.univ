#include<iostream>
#include<vector>
#include<cstring>
#include<utility>
using namespace std;

const int MAX_V = 2010;
vector<pair<int, int>> adj[MAX_V];
bool visited[MAX_V];
int far = -1;
int diameter = -1;

void dfs(int cur, int cost) {
	if (visited[cur]) {
		return;
	}

	visited[cur] = true;

	if (diameter < cost) {
		diameter = cost;
		far = cur;
	}

	for (int i = 0; i < adj[cur].size(); i++) {
		int next = adj[cur][i].first;
		int d = adj[cur][i].second;

		dfs(next, cost + d);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	int n;
	int u;
	int v;
	int d;

	cin >> T;

	while (T--) {
		cin >> n;
		diameter = -1;
		far = -1;

		memset(adj, 0, sizeof(adj));

		for (int i = 0; i < n - 1; i++) {
			cin >> u >> v >> d;
			adj[u].push_back(make_pair(v, d));
			adj[v].push_back(make_pair(u, d));
		}

		memset(visited, false, sizeof(visited));

		dfs(1, 0);

		memset(visited, false, sizeof(visited));
		diameter = 0;

		dfs(far, 0);

		cout << diameter << "\n";
	}
}