#include<iostream>
#include<algorithm>
using namespace std;

int T;	// �׽�Ʈ ���̽�
int N;	// ��Ʈ���ī�� ����
int m[100001];	// ��Ʈ���ī�� ũ�⸦ ������ �迭
int dp[501];	// dp[i] : i��° ��Ʈ���ī�� '������' ��Ʈ���ī�� �����Ͽ��� ��, �ִ� ���� ����

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