#include <cstdio>
#include <iostream>
#include <ctime>
using namespace std;

int n, k;

void make_0() {
	for (int i = 1; i <= n; i ++) cout << "0 ";
	cout << endl;
}

void make_1() {
	for (int i = 1; i <= n; i ++) cout << rand() % n << ' ';
}

int main() {
	freopen("1.in", "w", stdout);
  srand(time(NULL));
  n = 1000;
  k = 1000;
  cout << n << ' ' << k << endl;
  int w = rand() % 2;
  if (!w) {
  	make_0();
  } else {
    make_1();
  }
  for (int i = 2; i <= n; i ++) {
    cout << rand() % (i - 1) + 1 << ' ';
  }
  return 0;
}
  