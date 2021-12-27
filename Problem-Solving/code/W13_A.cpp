#include<iostream>
#include<string>
#include<vector>
using namespace std;

int N;	// 격자판의 크기
int M;	// 단어의 개수
string puzzle[3001];	// 격자판의 문자 저장

vector<int> getPi(string pattern) {
	int m = pattern.size();
	int j = 0;

	vector<int> pi(m, 0);

	for (int i = 1; i < m; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {
			j = pi[j - 1];
		}

		if (pattern[i] == pattern[j]) {
			pi[i] = ++j;
		}
	}

	return pi;
}

int kmp(string s, string p) {
	
	int answer = 0;
	vector<int> pi = getPi(p);

	int n = s.size();
	int m = p.size();
	int j = 0;

	for (int i = 0; i < n; i++) {
		while (j > 0 && s[i] != p[j]) {
			j = pi[j - 1];
		}

		if (s[i] == p[j]) {
			if (j == (m - 1)) {
				answer = 1;
				//j = pi[j];
			}

			else {
				j++;
			}
		}
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> puzzle[i];
	}

	string T;	// 격자판을 합친 문자열(텍스트)
	string P;	// 검색할 단어(패턴)

	// 가로 방향
	for (int i = 0; i < N; i++) {
		T += puzzle[i];
		T += "$";	// 구분자 삽입
	}

	// 세로 방향
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			T += puzzle[j][i];
		}
		T += "$";
	}

	// 대각선 방향
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i; j++) {
			T += puzzle[j][i + j];
		}

		T += "$";
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N - i; j++) {
			T += puzzle[i + j][j];
		}

		T += "$";
	}

	while (M--) {
		cin >> P;

		cout << kmp(T, P) << "\n";
	}
	
}