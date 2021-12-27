#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int x_cost[10001];
int y_cost[10001];
vector<pair<int, int>> sum;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;	// �׽�Ʈ ���̽�
	int N;	// �ڿ��� ����
	int answer;

	cin >> T;

	while (T--) {
		
		answer = 0;
		sum.clear();

		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> x_cost[i] >> y_cost[i];
			sum.push_back(make_pair(x_cost[i] + y_cost[i], i));
		}

		sort(sum.begin(), sum.end(), greater<>());

		for (int i = 0; i < N; i++) {
			if (i % 2 == 0) {
				answer += x_cost[sum[i].second];
			}

			else {
				answer -= y_cost[sum[i].second];
			}
		}

		cout << answer << "\n";
	}
}