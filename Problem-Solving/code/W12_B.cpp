#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct room {
	int value;
	int distance;
};

int T;	// 테스트 케이스
int N;	// 방의 수
int A;	// 평점
int B;	// 거리
vector<room> rooms;

bool operator< (room a, room b) {
	if (a.distance == b.distance) {
		return a.value > b.value;
	}

	return a.distance < b.distance;
}

int main() {
	ios::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> T;

	while (T--) {
		rooms.clear();
		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> A >> B;

			rooms.push_back({ A, B });
		}

		sort(rooms.begin(), rooms.end());	// 가까운 순으로 정렬

		int max_value = 0;
		int result = N;

		for (int i = 0; i < N; i++) {
			if (max_value < rooms[i].value){
				max_value = rooms[i].value;
			}

			else {
				result--;
			}
			
		}

		cout << result << "\n";
	}

}