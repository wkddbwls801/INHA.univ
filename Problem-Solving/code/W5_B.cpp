#include<iostream>
using namespace std;

int home[1000001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;	// ���� ��
	int M;	// �ֹ��� ��

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> home[i];
	}

	int min = 1;
	int max = home[N - 1];
	int mid = 0;	// �ֹε� ���� �Ÿ�
	int count = 0;	// �ֹ��� �� Ȯ��
	int pos;	// �ֹ��� ��ġ index ������ ǥ��
	int answer = 0;

	while (min <= max) {
		mid = (min + max) / 2;

		pos = 0;	// home[0]�� ��ġ
		count = 1;

		for (int i = 1; i < N; i++) {
			if (home[i] - home[pos] >= mid) {
				pos = i;
				count++;
			}
		}

		if (count >= M) {
			answer = mid;
			min = mid + 1;
		}

		else {
			max = mid - 1;
		}
	}

	cout << answer << "\n";
}