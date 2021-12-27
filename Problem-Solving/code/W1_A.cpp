#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

char zigzag[101][1001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	string S;
	int K;

	cin >> T;

	while (T--) {

		memset(zigzag, 0, sizeof(zigzag));
		queue<char> word;

		cin >> S;

		for (int i = 0; i < S.size(); i++) {
			word.push(S[i]);
		}

		cin >> K;

		bool check = true;
		int x = -1;

		while (!word.empty()) {
			x++;
			if (check) {
				for (int i = 0; i < K; i++) {
					if (word.empty()) {
						break;
					}
					zigzag[i][x] = word.front();
					word.pop();
				}
			}

			else {
				for (int i = K - 1; i >= 0; i--) {
					if (word.empty()) {
						break;
					}
					zigzag[i][x] = word.front();
					word.pop();
				}
			}

			check = !check;
		}

		for (int i = 0; i < K; i++) {
			for (int j = 0; j < S.size(); j++) {
				if (zigzag[i][j] == '\0') {
					break;
				}
				cout << zigzag[i][j];
			}
		}

		cout << "\n";
	}
}