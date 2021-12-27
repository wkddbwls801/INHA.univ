#include<iostream>
#define ll long long
using namespace std;

int T;	// �׽�Ʈ ���̽�
ll X;	// �ڿ���
ll N;	// ���� ��
ll M;	// ������ ��


ll mypow(ll ratio, ll num) {
	// ration ^ 0�̸� -> 1

	if (num == 0) {
		return 1;
	}

	// �������� ¦���� ���
	if (num % 2 == 0) {
		return mypow((ratio * ratio) % M, num / 2) % M;
	}

	else {
		return (ratio * mypow((ratio * ratio) % M, num / 2)) % M;
	}
}

// func(ù ��° ��(0), ������ �� (n - 1), ������(n)) -> ������ ��ȭ�� ���ؼ�
ll func(ll x, ll y, ll size) {
	if (size == 1) {
		return (X * mypow(X, x)) % M;
	}

	// ���� ���� ¦�� �� ��
	if (size % 2 == 0) {
		return (func(x, x + (size / 2) - 1, size / 2) * (mypow(X, (size / 2)) + 1)) % M;
	}

	// ���� ���� Ȧ�� �� ��
	else {
		return (func(y, y, 1) + func(x, x + (size / 2) - 1, size / 2) * (mypow(X, (size / 2)) + 1)) % M;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {
		cin >> X >> N >> M;

		cout << func(0, N - 1, N) << "\n";
	}
}