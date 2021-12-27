#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int num[101][101];
int dp[101][101];

int T;	// 테스트 케이스
int N;	// 삼각형의 행의 수

int main() {
	ios::sync_with_stdio(false);

	cin >> T;

	while (T--) {
		memset(dp, 0, sizeof(dp));

		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				cin >> num[i][j];
			}
		}

		dp[0][0] = num[0][0];

		for (int i = 1; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				if (j == 0) {
					dp[i][j] = dp[i - 1][j] + num[i][j];
				}

				else if (j == i) {
					dp[i][j] = dp[i - 1][j - 1] + num[i][j];
				}

				else {
					dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + num[i][j];
				}
			}
		}

		int result = dp[N - 1][0];
		for (int i = 1; i < N; i++) {
			result = min(result, dp[N - 1][i]);
		}

		cout << result << "\n";
	}
}