/*
 * SPOJ AIBOPHOBIA problem
 * Minimum insertions required to convert a string to palindrome
 * Use DP. Store answers for all substrings
 */
#include <iostream>
#include <fstream>



using namespace std;

short a[6100][6100] = {0};


int min_req(string & s) {
	int l = s.length();
	
	for(int i = 0; i < (l - 1); ++i) {
		a[i][i+1] =  (s[i] == s[i+1]) ? 0 : 1;	
	}

	// find minimum insertions required for strings
	// of length 3 to l
	for(int length = 3; length <= l; ++length) {
		for(int i = 0; i + length - 1 < l; ++i) {
			int j = i + length - 1;
			// s[i] amd s[j] match. So no extra
			// insertions are required
			if(s[i] == s[j])
				a[i][j] = a[i + 1][j - 1];
			else	a[i][j] = 1 + min(a[i + 1][j], a[i][j - 1]);
		}
	}
	return a[0][l - 1];
}

int main() {
	int t;
	ios_base::sync_with_stdio(false);	
	cin >> t;

	string s;

	for(int i = 0; i < t; ++i) {
		cin >> s;
		cout << min_req(s) << "\n";
	}

	return 0;
}
