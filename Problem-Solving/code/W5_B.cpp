#include<iostream>
using namespace std;

int home[1000001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;	// 집의 수
	int M;	// 주민의 수

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> home[i];
	}

	int min = 1;
	int max = home[N - 1];
	int mid = 0;	// 주민들 간의 거리
	int count = 0;	// 주민의 수 확인
	int pos;	// 주민의 위치 index 값으로 표현
	int answer = 0;

	while (min <= max) {
		mid = (min + max) / 2;

		pos = 0;	// home[0]에 위치
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