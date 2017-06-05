#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <conio.h>

using namespace std;

queue<char> que;
mutex m;

void input() {
	while (1) {
		que.push(getche());
	}
	return;
}

void output() {
	m.lock();
	cout << endl;
	while (!que.empty()) {
		cout << que.front();
		que.pop();
	}
	cout << endl;
	m.unlock();
	return;
}

int main() {
	thread t(input);
	t.detach();
	for (int i = 1; i <= 10; ++i) {
		output();
		this_thread::sleep_for(chrono::seconds(1));
	}
	return 0;
}
