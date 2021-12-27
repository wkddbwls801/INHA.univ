#include<iostream>
#include<algorithm>
using namespace std;

int T;	// 테스트 케이스
int N;	// 마트료시카의 개수
int m[100001];	// 마트료시카의 크기를 저장할 배열
int dp[501];	// dp[i] : i번째 마트료시카를 '마지막' 마트료시카로 선택하였을 때, 최대 조립 개수

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	 
	cin >> T;

	while (T--) {
		cin >> N;

		for (int i = 1; i <= N; i++) {
			cin >> m[i];
		}

		for (int i = 1; i <= N; i++) {
			dp[i] = 1; 

			for (int j = 1; j <= i - 1; j++) {
				if (m[j] < m[i]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}

		int result = dp[1];

		for (int i = 2; i <= N; i++) {
			result = max(result, dp[i]);
		}

		cout << result << "\n";
	}
}