#include<iostream>
#include<vector>
using namespace std;

int ccw(pair<long long, long long> p1, pair<long long, long long> p2, pair<long long, long long> p3) {
	int temp = (p2.first - p1.first) * (p3.second - p1.second) - (p2.second - p1.second) * (p3.first - p1.first);

	if (temp > 0) {
		return 1;
	}

	else if (temp == 0) {
		return 0;
	}

	else {
		return -1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int T;

	cin >> T;

	while (T--) {
		pair<long long, long long> A;
		pair<long long, long long> B;
		pair<long long, long long> C;
		pair<long long, long long> D;

		cin >> A.first >> A.second >> B.first >> B.second;
		cin >> C.first >> C.second >> D.first >> D.second;

		if (A > B) {
			swap(A, B);
		}

		if (C > D) {
			swap(C, D);
		}

		if (A > C) {
			swap(A, C);
			swap(B, D);
		}

		int abc = ccw(A, B, C);
		int abd = ccw(A, B, D);
		int cda = ccw(C, D, A);
		int cdb = ccw(C, D, B);

		// 교차, 삼각형, 일직선
		if (abc * abd <= 0 && cda * cdb <= 0) {

			// 삼각형, 일직선
			if (abc * abd == 0 && cda * cdb == 0) {

				// 일직선
				if (abc == 0 && abd == 0 && cda == 0 && cdb == 0) {

					// 만나지 않음
					if (B < C) {
						cout << 1 << "\n";
					}

					// 한 점에서 만남
					else if (B == C) {
						cout << 2 << "\n";
					}

					// 교차
					else if (A < C && B < D) {
						cout << 3 << "\n";
					}

					// 포함
					else if (A <= C && (B <= D || D <= B)) {
						cout << 4 << "\n";
					}
				}

				// 삼각형
				else {
					cout << 2 << "\n";
				}
			}

			// 교차
			else {
				cout << 2 << "\n";
			}
		}

		// 만나지 않음
		else {
			cout << 1 << "\n";
		}
	}
}