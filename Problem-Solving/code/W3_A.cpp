#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Node {
	int parent;
	vector<int> child;
	int length;
};

Node directory[50001];
int directory_name[50001];

void DFS(int num) {
	if (num == 1) {
		directory_name[num] = directory[num].length;
	}

	else {
		directory_name[num] = directory_name[directory[num].parent] + 1 + directory[num].length;
	}

	for (int i = 0; i < directory[num].child.size(); i++) {
		DFS(directory[num].child[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;	// 테스트 케이스
	int N;
	int A;
	int B;
	string S;

	cin >> T;

	while (T--) {
		for (int i = 0; i < 50001; i++) {
			directory[i].child.clear();
		}
		cin >> N;

		for (int i = 0; i < N - 1; i++) {
			cin >> A >> B;
			directory[A].child.push_back(B);
			directory[B].parent = A;
		}

		for (int i = 1; i <= N; i++) {
			cin >> S;
			directory[i].length = S.length();
		}

		DFS(1);

		for (int i = 1; i <= N; i++) {
			cout << directory_name[i] << "\n";
		}
	}
}