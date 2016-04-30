#include <iostream>

using namespace std;
// 7850 becomes 587
int reversed(int u) {
	int r = 0;
	bool non_zero = false;
	while(u) {
		if(u % 10 != 0 || non_zero) {
			non_zero = true;
			r = r * 10 + (u % 10);
		}
		u /= 10;
	}
	
	return r;
}

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		int t, y;
		cin >> t >> y;
		cout << reversed(reversed(t) + reversed(y)) << "\n";
	}
	return 0;
}
