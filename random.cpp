#include <iostream>
#include <random>

using namespace std;

void OutputARandomNum() {
	static default_random_engine e;
	static uniform_int_distribution<unsigned> u(0,9);
	cout << u(e) << endl;
	return;
}

int main() {
	for (int i = 1; i <= 100; ++i) {
		OutputARandomNum();
	}
	return 0;
}
