#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;

int T;	// 테스트 케이스
int A;	// 시작 방 번호
int B;	// 탈출 방 번호
vector<int> room[10001];
int check[10001];
queue<int> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// 방 번호 설정
	for (int i = 0; i < 10000; i++) {

		// 방 번호에서 -1인 번호의 방으로 이동
		if (i != 0) {
			room[i].push_back(i - 1);
		}

		// 방 번호에서 +1인 번호의 방으로 이동
		if (i != 9999) {
			room[i].push_back(i + 1);
		}

		// 방 번호의 역순인 번호의 방으로 이동
		int num = 0;
		int temp = i;

		for (int j = 0; j < 4; j++) {
			num = num * 10 + temp % 10;
			temp = temp / 10;
		}

		room[i].push_back(num);
	}

	cin >> T;

	while (T--) {
		cin >> A >> B;

		fill(check, check + 10000, 10000);	// 초기화

		check[A] = 0;

		q.push(A);

		while (!q.empty()) {
			int now = q.front();

			q.pop();

			for (int i = 0; i < room[now].size(); i++) {
				if (check[room[now][i]] > check[now] + 1) {	// 돌아가지 않게 하기 위해서 하는 조건
					q.push(room[now][i]);
					check[room[now][i]] = check[now] + 1;
				}
			}
		}

		cout << check[B] << "\n";
	}
}