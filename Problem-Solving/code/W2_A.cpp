#include<iostream>
#include<queue>
using namespace std;

string word[2001];
queue<string> note[21];
int main() {
	int T;	// �׽�Ʈ ���̽�
	int N;	// ģ���� ��
	int M;	// �ܾ��� ��
	int K;	// �� ģ������ ��Ʈ�� �ʱ��� �ܾ��� ��
	string W;	// �ܾ�

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