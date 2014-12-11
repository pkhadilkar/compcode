/*
ID: pushkar7
LANG: C++
PROB: nocows
*/
#include <iostream>
#include <cmath>
#include <fstream>
#define MAX_N 200
#define MAX_K 100
#define LIMIT 9901
using namespace std;
int num[MAX_N][MAX_K];
int main() {
	ifstream in("nocows.in");
	ofstream out("nocows.out");
	ios_base::sync_with_stdio(false);

	int N, K;
	num[0][0] = num[1][1] = 1;
	in >> N >> K;
	// zero / pre-computed for first row and first column
	for(int n = 3; n <= N; ++n) {
		for(int k = 2; (k <= K) && (k <= (n + 1) / 2); ++k) {
			int t = 0;
			// try different combinations of node
			// on each side. We'll later multiply by
			// 2 to ensure that (1, 2) and (2, 1)
			// are counted as distinct
			int to = (n % 2) == 0 ? ((n / 2) - 1): (n / 2);
			for(int i = 0; i <= to; ++i) {
				int x = 0;
				int l = i, r = n - i - 1;
				for(int j = 1; j <= (k - 1); ++j) {
					x += ((num[l][k - 1] * num[r][j]) % LIMIT);
					if(j != k - 1) 
						x += (num[l][j] * num[r][k -1]) ;//% LIMIT;
					x = (x % LIMIT);
				}
				if(l != r) 	x = (2 * x) % LIMIT;
				t = (t + x) % LIMIT;
			}
			num[n][k] = t;
			//cout << "["<<n << "," << k << "] :" << num[n][k] << "\n";
		}
	}

	out << num[N][K] << "\n";
	in.close();
	out.close();
	return 0;
}
