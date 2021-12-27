#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

stack<int> min_stack;
stack<int> max_stack;

int main() {
	int T;	// �׽�Ʈ ���̽�
	int N;	// ������ ��
	int command;	// ����
	int x;	// ����

	cin >> T;

	while (T--) {
		
		// �ʱ�ȭ
		while (!min_stack.empty()) {
			min_stack.pop();
			max_stack.pop();
		}

		min_stack.push(1001);
		max_stack.push(0);

		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> command;

			if (command == 1) {
				cin >> x;

				min_stack.push(min(min_stack.top(), x));
				max_stack.push(max(max_stack.top(), x));

				cout << min_stack.top() << " " << max_stack.top() << "\n";
			}

			else {
				if (min_stack.empty()) {
					continue;
				}

				else {
					min_stack.pop();
					max_stack.pop();

					if (min_stack.empty()) {
						min_stack.push(1001);
						max_stack.push(0);
					}
				}
			}
		}
		
	}
}