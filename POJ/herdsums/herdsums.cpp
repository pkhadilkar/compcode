#include <iostream>
#define LINE endl
using namespace std;

int main() {
	int n;
	cin >> n;
	int herdsums = 0;
	for(int i = n; i > 0; --i) {
		int sum = i, j;
		for(j = i - 1; j > 0 && sum < n; --j) {
			sum += j;
		}
		if(sum == n) {
			++herdsums;
		}
	}

	cout << herdsums << LINE;
	return 0;
}
