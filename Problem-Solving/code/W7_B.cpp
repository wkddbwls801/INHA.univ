#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

struct point {
	int x;
	int y;
	double distance;	// �Ÿ�
};

// �켱������ ������� ��!
bool operator<(point a, point b) {
	if (a.distance == b.distance) {
		if (a.x == b.x) {
			return a.y < b.y;
		}

		return a.x < b.x;
	}

	return a.distance < b.distance;
}

int T;	// �׽�Ʈ ���̽�
int M;	// ó�� �����ϴ� �ܹ��� ������ ��
int N;	// ���Ӱ� �����Ǵ� �ܹ��� ������ ��
int K;	
int store_x;	// ��ǥ
int store_y;	// ��ǥ
priority_queue<point> stores;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {
		
		while (!stores.empty()) {	// �ʱ�ȭ
			stores.pop();
		}

		cin >> M >> N >> K;
		 
		// ó�� �����ϴ� �ܹ��� ���� ��ǥ �Է�
		for (int i = 0; i < M; i++) {
			cin >> store_x >> store_y;
			stores.push(point{store_x, store_y, sqrt(pow(store_x, 2) + pow(store_y, 2))});

			if (stores.size() > K) {
				stores.pop();	// K���� ����
			}
		}

		// ���Ӱ� �����Ǵ� �ܹ��� ���� ��ǥ �Է�
		for (int i = 0; i < N; i++) {
			cin >> store_x >> store_y;
			stores.push(point{ store_x, store_y, sqrt(pow(store_x, 2) + pow(store_y, 2)) });

			stores.pop();	// ������ K���� ����Ǿ� �ְ�, ���ο� ���� �߰� �Ǿ� K+!���� �Ǿ� �����Ƿ�, ���� �� ���� K+1��°�� ����

			cout << stores.top().x << " " << stores.top().y << "\n";
		}
	}
}