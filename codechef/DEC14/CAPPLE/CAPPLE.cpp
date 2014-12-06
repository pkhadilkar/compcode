/*
 * Codechef DEC14 challenge
 * Chef and Apple
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#define MAX 100001

using namespace std;
// we don't want to deal with changing offset here
bool apples[MAX + 1];

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	int N;
	int x;	// tmp variable
	for(int i = 0; i < t; ++i) {
		fill(apples, apples + MAX + 1, false);
		int count = 0;
		cin >> N;
		for(int j = 0; j < N; ++j) {
			cin >> x;
			count += (!apples[x]); 
			apples[x] = true;
		}
		cout << count << "\n";
	}

	return 0;
}
