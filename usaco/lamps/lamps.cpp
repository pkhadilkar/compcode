/*
 * ID: pushkar7
 * LANG: C++
 * PROG: lamps
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#define TOTAL 100
using namespace std;
#define OFF 0
#define ON 1
#define ANY 2
// globals to avoid arg passing
int N, C;
int  lamps[TOTAL] = {2};
// max four switches 
// max 2^4 permutatiosn
int perms[16][4];

void inline swap(int i, int j, vector<int> & seq) {
	int t = seq[i];
	seq[i] = seq[j];
	seq[j] = t;
}

void gen_perm_rec(int start, int length, int * seq, int & index) {
	if(start == length - 1) {
		// found next permutation
		for(int i = 0; i < length; ++i)
			perms[index][i] = seq[i];
		++index;
		return;
	}
	
	for(int i = start; i < length; ++i) {
		// new start followed by all 
		// permutations of remaining
		swap(i, start, seq);
		gen_perm_rec(start + 1, length, seq, index);
		swap(i, start, seq);
	}

}

int gen_perm(int * seq, int n) {
	int index = 0;
	gen_perm_rec(0, n, seq, index);
	return index;
}

// input consists of sequence of n button presses
void apply(int * aux, int * seq, int n) {
	for(int i = 0; i < n; ++i) {
		if(seq[i] == 0) {
			for(int j = 0; j < N; ++j)
				aux[j] = (aux[j] + 1) % 2;
		}
	}
}

void val_combs(vector<string> & configs) {
	int seq[4];
	for(int i = 0; i < 16; ++i) {
		int j = i, count = 0;
		
		while(j) {
			if(j & 1) seq[count] = count++;
			j >>= 1;
		}
		// we can only have as many as C
		// button presses
		if(count > C) continue;

		int n = gen_perm(seq, count);
		for(int j = 0; j < n; ++j) {
			// apply j'th sequence
			int aux[TOTAL] = {ON};
			apply(aux, perms[j], count);
			if(matches(aux, lamps)) {
				add_config(aux, configs);
			}
		}
	}
}


int main() {
	ifstream in("lamps.in");
	ofstream out("lamps.out");
	ios_base::sync_with_stdio(false);
	in >> N >> C;

	int x = 0;
	while((in >> x) && x != -1) {
		lamps[x] = ON;
	}
	x =0;
	while((in >> x) && x != -1) {
		lamps[x] = OFF;
	}

	vector<string> configs;
	val_combs(configs);

	sort(configs)
	for(string s: configs) {
		out << s << "\n";
	}

	in.close();
	out.close();
	return 0;
}
