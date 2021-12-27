#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct room {
	int value;
	int distance;
};

int T;	// �׽�Ʈ ���̽�
int N;	// ���� ��
int A;	// ����
int B;	// �Ÿ�
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

		sort(rooms.begin(), rooms.end());	// ����� ������ ����

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