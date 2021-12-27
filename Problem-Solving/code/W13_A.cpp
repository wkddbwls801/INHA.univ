#include<iostream>
#include<string>
#include<vector>
using namespace std;

int N;	// �������� ũ��
int M;	// �ܾ��� ����
string puzzle[3001];	// �������� ���� ����

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

	string T;	// �������� ��ģ ���ڿ�(�ؽ�Ʈ)
	string P;	// �˻��� �ܾ�(����)

	// ���� ����
	for (int i = 0; i < N; i++) {
		T += puzzle[i];
		T += "$";	// ������ ����
	}

	// ���� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			T += puzzle[j][i];
		}
		T += "$";
	}

	// �밢�� ����
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