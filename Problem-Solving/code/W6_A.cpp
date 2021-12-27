#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

struct consumerInfo {
	int time;
	int cost;
};

struct counterInfo {
	int use_time;
	int index;
};

consumerInfo guest[100000];
priority_queue<counterInfo> counterPQ;

int costAnswer[20000];

int N;	// 계산대의 수
int M;	// 손님의 수
int timeAnswer;

bool operator<(counterInfo a, counterInfo b) {
	if (a.use_time == b.use_time) {
		return a.index > b.index;
	}

	return a.use_time > b.use_time;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> guest[i].time >> guest[i].cost;
	}

	for (int i = 0; i < N; i++) {
		counterPQ.push({ guest[i].time, i });
		costAnswer[i] += guest[i].cost;
		timeAnswer = max(timeAnswer, guest[i].time);
	}

	for (int i = N; i < M; i++) {
		counterInfo counterTemp = counterPQ.top();

		counterPQ.pop();

		counterTemp.use_time += guest[i].time;
		costAnswer[counterTemp.index] += guest[i].cost;
		timeAnswer = max(timeAnswer, counterTemp.use_time);

		counterPQ.push(counterTemp);
	}

	cout << timeAnswer << "\n";

	for (int i = 0; i < N; i++) {
		cout << costAnswer[i] << "\n";
	}
}