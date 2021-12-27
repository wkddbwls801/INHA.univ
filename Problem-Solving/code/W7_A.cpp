#include<iostream>
#include<vector>
using namespace std;

int T;	// 테스트 케이스
int N;	// 공의 개수
int M;	// 저울로 측정한 횟수
int A;	// 공의 번호
int B;	// 공의 번호
int answer;
vector<int> Graph[101];
int visit[101];

void DFS(int u) {
	visit[u] = 1;

	for (int i = 0; i < Graph[u].size(); i++) {
		int v = Graph[u][i];

		if (visit[v] == 0) {
			DFS(v);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {

		for (int i = 0; i < 101; i++) {
			Graph[i].clear();
		}
		
		cin >> N >> M;

		for (int i = 1; i <= M; i++) {
			cin >> A >> B;
			Graph[A].push_back(B);
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				visit[j] = 0;	// visit 배열 초기화
			}

			DFS(i);

			answer = 0;

			for (int j = 1; j <= N; j++) {
				answer = answer + visit[j];
			}

			cout << answer - 1 << " ";
		}

		cout << "\n";
	}
}