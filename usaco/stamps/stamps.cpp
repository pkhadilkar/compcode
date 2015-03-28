/*
ID: pushkar7
LANG: C++
PROB: stamps
*/
#include <iostream>
#include <algorithm>
#include <cassert>
#include <fstream>
#define MAX_N (51)
#define MAX_K (201)
#define MAX_D (10000)
using namespace std;

int K, N;
int stamps[MAX_N];
// store for each i how many coins does it take to make that much change
// if there are multiple ways, store the one that uses minimum coins
int coins[MAX_D + 1];

int possible(int n) {
	int c = MAX_K;
	for(int d = 0; (d < N) && (n - stamps[d]) >= 0; ++d) {
		// when this is called, all lower denominations must be possible
		c = min(c, coins[(n - stamps[d]) % (MAX_D + 1)]);
	}
	assert(c >= 0);
	return (c + 1);
}

int solve() {
	if(stamps[0] != 1)
		return 0;
	int i = 1, j;
	coins[0] = 0;
	while(1) {
		j = possible(i);
		if(j > K)	break;
		assert(j <= K);
		// max is 10000. Thus, possible[i] needs access to (i - 10000, i -1)
		// 10001 will need access to (1, 10001)
		coins[i % (MAX_D + 1)] = j;
		++i;
	}
	return (i - 1);
}

int main() {
	ifstream in("stamps.in");
	ofstream out("stamps.out");
	
	in >> K >> N;
	for(int i = 0; i < N; ++i) {
		in >> stamps[i];
	}

	sort(stamps, stamps + N);
	fill(coins, coins + N, (-1));
	out << solve() << "\n";

	in.close();
	out.close();
	return 0;
}
