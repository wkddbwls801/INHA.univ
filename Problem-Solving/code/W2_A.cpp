#include<iostream>
#include<queue>
using namespace std;

string word[2001];
queue<string> note[21];
int main() {
	int T;	// 테스트 케이스
	int N;	// 친구의 수
	int M;	// 단어의 수
	int K;	// 각 친구들이 노트에 필기한 단어의 수
	string W;	// 단어

	cin >> T;

	while (T--) {
		cin >> N >> M;

		for (int i = 0; i < N; i++) {
			while (!note[i].empty()) {
				note[i].pop();
			}
		}

		for (int i = 0; i < M; i++) {
			cin >> word[i];
		}

		for (int i = 0; i < N; i++) {
			cin >> K;

			for (int j = 0; j < K; j++) {
				cin >> W;
				note[i].push(W);
			}
		}

		bool check = true;

		for (int i = 0; i < M; i++) {
			check = false;
			for (int j = 0; j < N; j++) {
				if (word[i] == note[j].front()) {
					note[j].pop();
					check = true;
					break;
				}
			}

			if (check == false) {
				break;
			}
		}

		cout << check << "\n";
	}
}