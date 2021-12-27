#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int M;	// �ܾ��� ����
int needalpha[23][26];	// �ܾ�
int restalpha[10000000][26];	// ���¿� ���� �ܾ�
int score[23];	// �ܾ� �� ����
int score_dp[10000000];	// ���� ����
string word;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// �ʱ� ���ĺ� ����
	for (int i = 0; i < 26; i++) {
		cin >> restalpha[0][i];
	}

	cin >> M;

	for (int i = 0; i < M; i++) {
		cin >> word >> score[i];

		for (int j = 0; j < word.size(); j++) {
			needalpha[i][word[j] - 'a'] += 1;
		}
	}

	int status = 0;
	int result = 0;

	for (int i = 0; i < M; i++) {
		status = pow(2, i);

		for (int j = 0; j < status; j++) {

			bool check = false;

			for (int alpha = 0; alpha < 26; alpha++) {
				// ���� �Ұ����� Ȯ��
				if (restalpha[j][alpha] < needalpha[i][alpha]) {
					check = true;
					break;
				}
			}

			// ���� �Ұ��� �ƴϸ� ��� ���
			if (check == true) {
				continue;
			}

			for (int alpha = 0; alpha < 26; alpha++) {
				restalpha[status + j][alpha] = restalpha[j][alpha] - needalpha[i][alpha];
			}

			score_dp[status + j] = score[i] + score_dp[j];
			result = max(result, score_dp[status + j]);
		}
	}


	cout << result << "\n";
}