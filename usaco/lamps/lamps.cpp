/*
ID: pushkar7
LANG: C++
PROB: lamps
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#define TOTAL (100 + 1)
using namespace std;
#define OFF 0
#define ON 1
#define ANY 2
// globals to avoid arg passing
int N, C;
int  lamps[TOTAL];
// max four switches 
// max 2^4 permutatiosn
int perms[16][4];

void inline swap(int i, int j, int * seq) {
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
		// toggle all
		if(seq[i] == 0) {
			for(int j = 1; j <= N; ++j)
				aux[j] = (aux[j] + 1) % 2;
		} // toggle odd
		else if(seq[i] == 1) {
			for(int j = 1; j <= N; j += 2) {
				aux[j] = (aux[j] + 1) % 2;
			}
		} // toggle even
		else if(seq[i] == 2) {
			for(int j = 2; j <= N; j += 2) {
				aux[j] = (aux[j] + 1) % 2;
			}
		} // toggle (3k + 1)
		else {
			for(int j = 1, k = 0; j <= N; ++k, j = 3 * k + 1) {
				aux[j] = (aux[j] + 1) % 2;
			}
		}
	}
}

bool matches(int * aux, int * lamps) {
	for(int i = 1; i <= N; ++i) {
		if(lamps[i] == ANY || lamps[i] == aux[i]) ;
		else return false;
	}
	return true;
}

void add_config(int * aux, vector<string> & configs) {
	string s = "";
	for(int i = 1; i <= N; ++i) {
		// for some reason this char
		// is very important and gives
		// non-platform specific behaviour
		s += char('0' + aux[i]);
	}
	configs.push_back(s);
}

void val_combs(vector<string> & configs) {
	int seq[4];
	for(int i = 0; i < 16; ++i) {
		int j = i, count = 0, k = 0;
		
		while(j) {
			if(j & 1) seq[count++] = k;
			j >>= 1;
			++k;
		}
		// we can only have as many as C
		// button presses
		if(count > C) continue;

		int n = gen_perm(seq, count);
		for(int j = 0; j < n || C == 0; ++j) {
			// apply j'th sequence
			int aux[TOTAL];
			fill(aux, aux + TOTAL, ON);
			apply(aux, perms[j], count);
			if(matches(aux, lamps)) {
				add_config(aux, configs);
			}
			if(!C) break;
		}
	}
}


int main() {
	ifstream in("lamps.in");
	ofstream out("lamps.out");
	ios_base::sync_with_stdio(false);
	in >> N >> C;

	int x = 0;
	fill(lamps, lamps + TOTAL, ANY);
	while((in >> x) && x != -1) {
		lamps[x] = ON;
	}
	x =0;
	while((in >> x) && x != -1) {
		lamps[x] = OFF;
	}

	vector<string> configs;
	val_combs(configs);

	sort(configs.begin(), configs.end());
	string prev="";
	for(int i = 0; i < configs.size(); ++i) {
		if(prev.compare("") == 0 || !(prev.compare(configs[i]) == 0))
			out << configs[i] << "\n";
		prev = configs[i];
	}

	if(configs.size() == 0) {
		out << "IMPOSSIBLE\n";
	}

	in.close();
	out.close();
	return 0;
}
