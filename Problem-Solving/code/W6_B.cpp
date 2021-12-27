#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

struct point {
	int x;
	int y;
};

int check[1001][1001];
bool visited[1001][1001];

int dx[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
int dy[8] = { 1, -1, 0, -1, 1, 0, -1, 1 };

point inha, safe, knight, gunner;

int N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	while (T--) {
		memset(check, 0, sizeof(check));
		memset(visited, false, sizeof(visited));

		cin >> N;

		cin >> inha.x >> inha.y >> safe.x >> safe.y;
		cin >> knight.x >> knight.y >> gunner.x >> gunner.y;

		inha.x--;
		inha.y--;
		safe.x--;
		safe.y--;
		knight.x--;
		knight.y--;
		gunner.x--;
		gunner.y--;

		// 소총수의 공격 범위
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < N; j++) {
				if (gunner.x + dx[i] * j == -1 || gunner.x + dx[i] * j == N || gunner.y + dy[i] * j == -1 || gunner.y + dy[i] * j == N) {
					break;
				}

				if (gunner.x + dx[i] * j == knight.x && gunner.y + dy[i] * j == knight.y) {
					break;
				}

				check[gunner.x + dx[i] * j][gunner.y + dy[i] * j] = 1;
			}
		}

		// 검사의 공격 범위
		for (int i = 0; i < 8; i++) {
			if (knight.x + dx[i] == -1 || knight.y + dx[i] == N || knight.y + dy[i] == -1 || knight.y + dy[i] == N) {
				continue;
			}

			check[knight.x + dx[i]][knight.y + dy[i]] = 1;
		}

		queue<point>q;

		q.push({ inha.x, inha.y });

		while (!q.empty()) {
			point now = q.front();
			q.pop();

			visited[now.x][now.y] = true;

			for (int i = 0; i < 8; i++) {
				if (now.x + dx[i] == -1 || now.x + dx[i] == N || now.y + dy[i] == -1 || now.y + dy[i] == N) {
					continue;
				}

				if ((check[now.x + dx[i]][now.y + dy[i]] != 0) || (visited[now.x + dx[i]][now.y + dy[i]] == true)) {
					continue;
				}

				check[now.x + dx[i]][now.y + dy[i]] = check[now.x][now.y] + 1;
				q.push({ now.x + dx[i], now.y + dy[i] });
			}
		}

		cout << check[safe.x][safe.y] << "\n";
	}
}