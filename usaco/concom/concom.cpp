/*
ID: pushkar7
LANG: C++
PROB: concom
*/

#include <iostream>
#include <fstream>
#include <set>
#define MAX (100 + 1)

using namespace std;

bool controls[MAX + 1][MAX + 1];
short owns[MAX + 1][MAX + 1];
bool exists[MAX + 1];	// 1 indicates that company is in the set of current companies
int N;
set<int> current;
set<int> next;

// return if i controls j
bool is_controls(int i, int j) {
	if(i == j) return true;
	if(owns[i][j] >= 50) return true;
	int t = owns[i][j];
	for(int k = 0; k < MAX; ++k) {
		if(i == k || i == j || !exists[k]) continue;
		if(controls[i][k])
			t += owns[k][j];
	}

	return (t >= 50);
}

void solve() {
	int level = 0;
	while(level < MAX) {
		next.clear();
		for(set<int>::iterator it = current.begin(); it != current.end(); ++it) {
			int i = *it;
			for(int j = 0; j < MAX;++j) {
				if(i == j || !exists[j]) continue;
				// check if i owns j
				if(is_controls(i, j)) {
					next.insert(i);
					controls[i][j] = true;
				}
			}
		}

		if(next.empty())	break;
		current.clear();
		current.insert(next.begin(), next.end());
		++level;
	}
}


int main() {
	ifstream in("concom.in");
	ofstream out("concom.out");

	int N;
	in >> N;

	for(int i = 0; i < N; ++i) {
		int x, y, z;
		in >> x >> y >> z;
		owns[x][y] = z;
		if(z >= 50) {
			controls[x][y] = true;
			current.insert(x);
		}

		exists[x] = exists[y] = true;
		controls[x][x] = controls[y][y] = true;
	}

	solve();

	for(int i = 0; i < MAX; ++i) {
		if(!exists[i]) continue;
		for(int j = 0; j < MAX; ++j) {
			if(!exists[j] || i == j) continue;
			if(controls[i][j])
				out << i << " " << j << "\n";
		}
	}

	in.close();
	out.close();
	return 0;
}
