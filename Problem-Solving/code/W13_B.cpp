#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int T;	// 테스트 케이스
int N;	// 채팅방의 인원수
int M;	// 메시지의 수
int msg[500001];
int result[500001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {
		cin >> N >> M;

		for (int i = 0; i < M; i++) {
			cin >> msg[i];
		}

		stack<int> reader;
		vector<bool> check(1000000001, false);

		for (int i = M - 1; i >= 0; i--) {
			if (check[msg[i]] == false) {
				reader.push(msg[i]);
				check[msg[i]] = true;
			}

			result[i] = N - reader.size();
		}

		for (int i = 0; i < M; i++) {
			cout << result[i] << "\n";
		}
	}
}