#include<iostream>
#include<cassert>
#define MAX (100)
#define MAX_INT (10000000)
using namespace std;

int mixtures[MAX];
int min_smoke[MAX][MAX];
int residue[MAX][MAX];

int N;

int solve() {
	//fill(&min_smoke[0][0], &min_smoke[0][0] + sizeof(min_smoke) / sizeof(min_smoke[0][0]), MAX_INT);
	// find optimal smoke and residue for (0, i) , (i, N - 1)
	// for all 0 <= i <= N
	for(int j = 0; j < N; ++j) {
		min_smoke[j][j] = 0;
		residue[j][j] = mixtures[j];
	}

	for(int n = 2; n <= N; ++n) {
		// find answer for length equal to n
		for(int i = 0, j; (i + n - 1) < N; ++i) {
			j = i + n - 1;
			// find answer for (i, j)
			min_smoke[i][j] = MAX_INT;
			int smoke = MAX_INT, r = -1;
			for(int k = i; k < j; ++k) {
				// i to k and k + 1 to j is combined and
				// then residue and smoke remaining is combined
				int l_residue = residue[i][k], r_residue = residue[k + 1][j];
				int l_smoke = min_smoke[i][k], r_smoke = min_smoke[k + 1][j];
				int new_residue = (l_residue + r_residue) % MAX;
				int new_smoke = (l_smoke) + (r_smoke) + (l_residue * r_residue);
				if(new_smoke < smoke) {
					smoke = new_smoke;
					r = new_residue;
				}
			}
			assert(smoke < MAX_INT);
			min_smoke[i][j] = smoke;
			residue[i][j] = r;
		}
	}

	return min_smoke[0][N - 1];
}

int main() {
	
	while(cin >> N) {
		for(int j = 0; j < N; ++j) cin >> mixtures[j];
		cout << solve() << "\n";
	}
	return 0;
}
