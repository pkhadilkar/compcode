/*
PROG: runround
LANG: C++
ID: pushkar7
*/

#include <iostream>
#include <fstream>

using namespace std;

bool is_runround(int l, char * d, bool seen[10]) {
	// use seen as a scratch array	
	// runround must be for each digit
	// must not stop at a digit more than once
	int c = l - 1;
	for(int i = 0; i < l; ++i) {
		int digit = d[c];
		while(digit != 0) {
			c = ((c > 0) ? c : l) - 1;
//			cout << c << " " << digit << "\n";
			--digit;
		}
		if(!seen[d[c]]) return false;
		seen[d[c]] = false;
	}
	return (c == l - 1);
}


int solve(int n) {
	char d[10];		// number will have max 9 digits
	int x;
//	bool found;
	--n;
	while(1) {
outer:		++n;
//		found = true;
		// check if runround
		int m = n, i = 0;
		bool s[10] = {0};
		while(m) {
			x = m % 10;
			if(s[x] || x == 0) goto outer;
			s[x] = true;
			d[i++] = x;
			m /= 10;
		}
		// number has unique digits and no zero
		if(is_runround(i, d, s))
			return n;
	}
}



int main() {
	ifstream in("runround.in");
	ofstream out("runround.out");

	int n;
	in >> n;

	out << solve(n + 1) << "\n";

	in.close();
	out.close();
	
	return 0;
}
