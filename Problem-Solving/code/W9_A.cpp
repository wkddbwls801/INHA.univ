#include<iostream>
#define ll long long
using namespace std;

int T;	// 테스트 케이스
ll X;	// 자연수
ll N;	// 항의 수
ll M;	// 나누는 수


ll mypow(ll ratio, ll num) {
	// ration ^ 0이면 -> 1

	if (num == 0) {
		return 1;
	}

	// 제곱수가 짝수인 경우
	if (num % 2 == 0) {
		return mypow((ratio * ratio) % M, num / 2) % M;
	}

	else {
		return (ratio * mypow((ratio * ratio) % M, num / 2)) % M;
	}
}

// func(첫 번째 수(0), 마지막 수 (n - 1), 사이즈(n)) -> 제곱수 변화에 대해서
ll func(ll x, ll y, ll size) {
	if (size == 1) {
		return (X * mypow(X, x)) % M;
	}

	// 항의 수가 짝수 일 때
	if (size % 2 == 0) {
		return (func(x, x + (size / 2) - 1, size / 2) * (mypow(X, (size / 2)) + 1)) % M;
	}

	// 항의 수가 홀수 일 때
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