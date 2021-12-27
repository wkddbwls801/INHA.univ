#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;

int T;	// �׽�Ʈ ���̽�
int A;	// ���� �� ��ȣ
int B;	// Ż�� �� ��ȣ
vector<int> room[10001];
int check[10001];
queue<int> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// �� ��ȣ ����
	for (int i = 0; i < 10000; i++) {

		// �� ��ȣ���� -1�� ��ȣ�� ������ �̵�
		if (i != 0) {
			room[i].push_back(i - 1);
		}

		// �� ��ȣ���� +1�� ��ȣ�� ������ �̵�
		if (i != 9999) {
			room[i].push_back(i + 1);
		}

		// �� ��ȣ�� ������ ��ȣ�� ������ �̵�
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

		fill(check, check + 10000, 10000);	// �ʱ�ȭ

		check[A] = 0;

		q.push(A);

		while (!q.empty()) {
			int now = q.front();

			q.pop();

			for (int i = 0; i < room[now].size(); i++) {
				if (check[room[now][i]] > check[now] + 1) {	// ���ư��� �ʰ� �ϱ� ���ؼ� �ϴ� ����
					q.push(room[now][i]);
					check[room[now][i]] = check[now] + 1;
				}
			}
		}

		cout << check[B] << "\n";
	}
}