/*
ID: pushkar7
LANG: C++
PROB: ratios
*/
#include <iostream>
#include <cassert>
#include <fstream>
#define MIX 3
#define DIM 3
#define LARGE (99 * 99)
#define MAX_MULT 99
using namespace std;
int goal[DIM];
int mixture[MIX][DIM];
int ratios[MIX];
bool dp[DIM][LARGE + 1];

void solve_dim(int d) {
	dp[d][0] = 1;
	for(int target = 1; target <= LARGE; ++target) {
		
		// is value target possible in dimension ?

		for(int m = 0; m < MIX && !dp[d][target]; ++m) {
			
			for(int mult = 1; mult < MAX_MULT && !dp[d][target]; ++mult) {
				int remaining = target - mult * mixture[m][d];
				if(remaining < 0)	break;
				dp[d][target] |= dp[d][remaining];
			}
		}
		//cout << "d:" << d << " target:" << target << " dp: " << dp[d][target] << "\n";
	}
}

// percolate multiples for each mixture
// choose a multiple at top level and verify at lower levels
bool possible(int m, int target[3]) {

	if(m < 0) {
		bool pos = true;
		for(int d = 0; d < DIM; ++d)	pos &= (target[d] == 0);
		return pos;
	}

	int local_target[3];

	for(int mult = 0; mult <= MAX_MULT; ++mult) {
	
		for(int j = 0; j < DIM; ++j) {
	
			local_target[j] = target[j] - mixture[m][j] * mult;
			if(local_target[j] < 0)	return false;		// non-negative mixture components and increasing multiples
		}

		ratios[m] = mult;
		// got a valid multiple for mixture m

		if(possible(m - 1, local_target)) {
			return true;	
		}
		
		ratios[m] = -1;
	}
	return false;
}


int solve() {
	// initial dynamic programming
	for(int i = 0; i < DIM; ++i)	solve_dim(i);

	// try all multiples of goal ratios
	for(int i = 1; i < MAX_MULT; ++i) {
		int target[DIM], k;
		for(int x = 0; x < DIM; ++x) {
			target[x] = i * goal[x];
			assert(goal[x] <= 100);
		}
		// is jth target individually possible ?	
		for(k = 0; k < DIM && dp[k][target[k]]; ++k);

		if(k < DIM)	continue;	// one of the "targets" not possible

//		cout << "calling possible for multiple " << i << "\n";

		// particular multiple check
		if(possible(MIX- 1, target)) {
			return i;
		}
	}
	return 0;
}

int main() {
	ifstream in("ratios.in");
	ofstream out("ratios.out");

	for(int i = 0; i < DIM; ++i)	{in >> goal[i]; ratios[i] = -1;}

	for(int i = 0; i < MIX; ++i)
		for(int j = 0; j < MIX; ++j)
			in >> mixture[i][j];

	int multiple = solve();
	if(multiple) {
		for(int i = 0; i < MIX; ++i)
			out << ratios[i] << " ";
		out << multiple;
	} else {
		out << "NONE";
	}

	out << endl;
	in.close();
	out.close();
	return 0;
}
