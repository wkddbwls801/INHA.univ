#include<iostream>
#include<vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;	// 테스트 케이스
	int N;	// 수신된 신호의 시간
	int X;	// 주파수

	cin >> T;

	while (T--) {
		vector<int> signal;
		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> X;
			signal.push_back(X);
		}

		int answer = -1;

		for (int i = 1; i < N; i++) {
			bool check = true;
			for (int j = i; j < N; j++) {
				if (signal[j % i] != signal[j]) {
					check = false;
					break;
				}
			}
			
			if (check) {
				answer = i;
				break;
			}
		}

		if (answer == -1) {
			answer = N;
		}

		for (int i = 0; i < answer; i++) {
			cout << signal[i] << " ";
		}

		cout << "\n";
	}
}