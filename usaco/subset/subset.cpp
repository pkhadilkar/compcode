/*
ID: pushkar7
LANG: C++
PROG: subset
*/
#include <iostream>
#include <fstream>
#include <map>
#define MAX 40
using namespace std;

map<int, int> subs;

int inline key(int i, int j, int k) {
	return i * 100000 + j * 100 + k;
}


// find number of ways elements [1, k]
// can be partitioned in two sets with
// sums i and j (i <= j)
int subset_rec(int i, int j, int k) {
	// computed already ? return
	if(subs.find(key(i, j, k)) != subs.end())	return subs[key(i, j, k)];
	// compute now
	int n = 0;

	if(j >= k) {
		int i1 = min(i, j - k);
		int j1 = max(i, j - k);
		int m = subset_rec(i1, j1, k - 1);
		n =  (i1 == j1) ? 2 * m : m;		/* k can be added to either of the sets
							   which are guranteed to be distinct.
							   For example, {1, 2} and {3} form 1
							   pair, but with 4 we can have {1, 2, 4}
							   or {3, 4} both with (3, 7, 4*) */
		if(i != j && i >= k) {
			n += subset_rec(i - k, j, k - 1);
		}	
	}

	subs[key(i, j, k)] = n;

	return n;
}


// count number of 2-partitions
// such that sum is identical
int subsets(int n) {
	// initial known
	// (0, 1, 1) = 1
	for(int i = 0; i <= n; ++i)	subs[key(0, i, i)] = 1;
	int x = n * (n + 1);
	int sum = x / 4;
	if( (x % 4) != 0)
		return 0;
	else
		return  subset_rec(sum, sum, n);
}

int main(){
	ifstream in("subset.in");
	ofstream out("subset.out");

	int N;
	in >> N;

	out << subsets(N) << "\n";
	
	in.close();
	out.close();

	return 0;
}
