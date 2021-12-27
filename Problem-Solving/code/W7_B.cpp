#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

struct point {
	int x;
	int y;
	double distance;	// 거리
};

// 우선순위를 정해줘야 함!
bool operator<(point a, point b) {
	if (a.distance == b.distance) {
		if (a.x == b.x) {
			return a.y < b.y;
		}

		return a.x < b.x;
	}

	return a.distance < b.distance;
}

int T;	// 테스트 케이스
int M;	// 처음 존재하는 햄버거 가게의 수
int N;	// 새롭게 생성되는 햄버거 가게의 수
int K;	
int store_x;	// 좌표
int store_y;	// 좌표
priority_queue<point> stores;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {
		
		while (!stores.empty()) {	// 초기화
			stores.pop();
		}

		cin >> M >> N >> K;
		 
		// 처음 존재하는 햄버거 가게 좌표 입력
		for (int i = 0; i < M; i++) {
			cin >> store_x >> store_y;
			stores.push(point{store_x, store_y, sqrt(pow(store_x, 2) + pow(store_y, 2))});

			if (stores.size() > K) {
				stores.pop();	// K개만 저장
			}
		}

		// 새롭게 생성되는 햄버거 가게 좌표 입력
		for (int i = 0; i < N; i++) {
			cin >> store_x >> store_y;
			stores.push(point{ store_x, store_y, sqrt(pow(store_x, 2) + pow(store_y, 2)) });

			stores.pop();	// 기존에 K개가 저장되어 있고, 새로운 것이 추가 되어 K+!개가 되어 있으므로, 가장 먼 것인 K+1번째를 삭제

			cout << stores.top().x << " " << stores.top().y << "\n";
		}
	}
}