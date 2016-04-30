#include <iostream>
#include <cmath>
#define MAX (999999999)
using namespace std;

int main() {
	int n;
	while(1) {
		cin >> n;
		if(!n) break;
		unsigned long smallest = MAX;
		for(int i = 1; i <= n; ++i) {
			int v, s;
			cin >> v >> s;
			if(s >= 0) {
				unsigned long r = ceil(4.5 / v * 60 * 60 + s);
				smallest = min(smallest, r);
			}
		}
		cout << smallest << "\n";
	}
	return 0;
}

