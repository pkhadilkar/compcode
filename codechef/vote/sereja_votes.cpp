#include <iostream>

using namespace std;

int main() {
	int T;

	cin >> T;

	for(int t = 0; t < T; ++t) {
		int n;

		cin >> n;
		unsigned long sum = 0;
		unsigned x;
		unsigned int zeroes = 0;
		for(int i = 0; i < n; ++i) {
			cin >> x;
			if (x == 0) {
				++zeroes;
			} else {
				sum += x;
			}
		}
		if (sum >= 100 && (sum - 100  + 1 + zeroes <= n)) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
