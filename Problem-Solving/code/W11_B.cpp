#include<iostream>
#include<string.h>
using namespace std;

struct paperinfo {
	int red_count = 0;
	int red_size = 0;
	int blue_count = 0;
	int blue_size = 0;
};

int T;	// 테스트 케이스
int N;	// 종이의 크기
char arr[1025][1025];

paperinfo solution(int x, int y, int size) {
	paperinfo ret;

	if (size == 1) {
		if (arr[x][y] == 'R') {
			ret.red_count = ret.red_size = 1;
		}

		else {
			ret.blue_count = ret.blue_size = 1;
		}

		return ret;
	}

	paperinfo status[4];

	status[0] = solution(x, y, size / 2);
	status[1] = solution(x, y + size / 2, size / 2);
	status[2] = solution(x + size / 2, y, size / 2);
	status[3] = solution(x + size / 2, y + size / 2, size / 2);

	for (int i = 0; i < 4; i++) {
		ret.red_count += status[i].red_count;
		ret.red_size += status[i].red_size;
		ret.blue_count += status[i].blue_count;
		ret.blue_size += status[i].blue_size;
	}

	if (ret.red_count == 0) {
		ret.blue_count = 1;
	}

	if (ret.blue_count == 0) {
		ret.red_count = 1;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {

		memset(arr, 0, sizeof(arr));

		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
			}
		}

		paperinfo answer = solution(0, 0, N);

		cout << answer.red_count << " " << answer.red_size << " " << answer.blue_count << " " << answer.blue_size << "\n";

	}
}