#include<iostream>
#include<fstream>

using namespace std;

int main() {
	ifstream in("a.txt");
	int a;
	in >> a;
	cout << a;
	in.close();
	in.open("a.txt", ifstream::in);
	in >> a;
	cout << a;
	in.close();
	return 0;
}
