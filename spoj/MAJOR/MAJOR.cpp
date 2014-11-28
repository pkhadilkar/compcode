#include <iostream>
#include <cmath>
#define MIN -1000
#define MAX 1000
#define TOTAL 2001
#define OFFSET 1000
int count[TOTAL];
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int c;
	cin >> c;
	
	for(int i = 0; i < c; ++i) {
		int n;
		cin >> n;
		fill(count, count + TOTAL, 0);
		int found = MIN - 1;
		for(int i = 0, y; i < n; ++i) {
			cin >> y;
			++count[y + OFFSET];
			if(count[y + OFFSET] > floor(n / 2.0))
				found = y;
		}
		if(found != MIN - 1) 
			cout << "YES " << found << "\n";
		else 	cout << "NO\n";
	}

	return 0;
}
