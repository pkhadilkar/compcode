#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include<cassert>
#define MAX (10000)
using namespace std;

bool composite[10000];

void init_primes() {
	for(int i = 2; i < MAX; ++i) {
		if(!composite[i])
			for(int mult = 2; i * mult < MAX; ++mult) 
				composite[i * mult] = true;
	}
}

bool inline is_prime(int i) {
	return !composite[i];
}

int dist(int s, int d) {
	queue<int> q;
	q.push(s);
	map<int, int> level;	// nodeid to level
	level[s] = 0;

	if(s == d)	return 0;

	while(!q.empty()) {
		int n = q.front(); q.pop();

		// process neighbours
		for(int pos = 0, p_ten = 1; pos < 4; ++pos, p_ten *= 10) {
			
			// p_ten ranges from 1 to 1000
			int x = (n % (p_ten * 10)) / p_ten;
			int y = n - x * p_ten;		// nullify appropriate digit

			for(int digit = int(pos == 3); digit < 10; ++digit) {

				int next = y + digit * p_ten;
				if(is_prime(next) && level.find(next) == level.end()) {
					assert(level.find(n) != level.end());
					level[next] = level[n] + 1;

					if(next == d) 	return level[next];
					q.push(next);
				}
			}
		}
	}

	return 0;
}

int main() {
	int n;
	cin >> n;

	init_primes();

	for(int i = 0; i < n; ++i) {
		int s, d;
		cin >> s >> d;
		cout << dist(s, d) << "\n";
	}
	return 0;
}
