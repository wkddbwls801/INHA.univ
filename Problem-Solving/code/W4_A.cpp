#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int gcd(int a, int b) {
	int c = a % b;

	while (c != 0) {
		a = b;
		b = c;
		c = a % b;
	}

	return b;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;	// 테스트 케이스
	int A;
	int B;
	int x;
	int y;

	cin >> T;

	while (T--) {
		cin >> A >> B >> x >> y;

		if (A < B) {
			swap(A, B);
		}

		vector<int> gcd_factor;

		for (int i = 1; i <= (A - B); i++) {
			if ((A - B) % i == 0) {
				gcd_factor.push_back(i);
			}
		}

		int max = gcd_factor.back();
		int A_plus = A;
		int B_plus = B;
		int A_minus = A;
		int B_minus = B;
		int x_cost = 0;
		int y_cost = 0;
		int answer = 0;

		while (1) {
			if (gcd(A_plus, B_plus) == max) {
				break;
			}

			else {
				A_plus++;
				B_plus++;
				x_cost += x;
			}
		}

		while (A_minus > 0 && B_minus > 0) {
			if (gcd(A_minus, B_minus) == max) {
				break;
			}

			else {
				A_minus--;
				B_minus--;
				y_cost += y;
			}
		}

		if (A_minus == 0 || B_minus == 0) {
			answer = x_cost;
		}

		else {
			answer = min(x_cost, y_cost);
		}
		cout << max << " " << answer << "\n";
	}
}