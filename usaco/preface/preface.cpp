/*
ID: pushkar7
LANG: C++
PROG: preface
*/

#include <iostream>
#include <fstream>

using namespace std;
enum Numerals {I, V, X, L, C, D, M};
int denom[7] = {1, 5, 10, 50, 100, 500, 1000};
char lc[3501][7];


bool v[3501];


void split(int & msb, int & r, int x) {
	int pt = 1;
	int t = x;
	while(t >= 10) {
		pt *= 10;
		t /= 10;
	}
	r = (x < 10) ? 0: x % pt;
	msb = x - r;
}

void add(int from, int to) {
	for(int i = 0; i < 7; ++i)
		lc[to][i] += lc[from][i];
}

// find Roman representation and set counts
// for numerals
void repr(int x) {
	if(v[x])	return;
	int msb, r;
	split(msb, r, x);
	// r must have been processed before
	if(r == 0) {
		int i = 6;
		while(denom[i] > msb) --i;
		int msb_1 = msb - denom[i], msb_2=denom[i];
		add(msb_1, x);
		add(msb_2, x);
	} else {
		add(r, x);
		add(msb, x);
	}
}

int main() {
	ifstream in("preface.in");
	ofstream out("preface.out");


	lc[1][I] = lc[5][V] = lc[10][X] = lc[50][L] = lc[100][C] = lc[500][D] = lc[1000][M] = 1;
	lc[2][I] = lc[20][X] = lc[200][C] = lc[2000][M] = 2;
	lc[3][I] = lc[30][X] = lc[300][C] = lc[3000][M] = 3;
	lc[4][I] = lc[4][V] = lc[9][I] = lc[9][X] = lc[40][X] = lc[40][L] = lc[90][X] = lc[90][C] = lc[400][C] = lc
	[400][D] =lc[900][C] = lc[900][M] = 1;

	v[0] = v[1] = v[5] = v[10] = v[50] = v[100] = v[500] = v[1000 ] = 1;
	v[2] = v[20] = v[200] = v[2000] = 1;
	v[3] = v[30] = v[300] = v[3000] = 1;
	v[4] = v[9] = v[40] = v[90] =v[400] = v[900] = 1;
	int N;
	in >> N;

	// solve for all numbers upto N
	for(int i = 1; i <= N; ++i) {
		repr(i);
	}
	
	int count[7] = {0};
	for(int j = 0; j <= N; ++j) {
		for(int i = 0; i < 7; ++i) {
			count[i] += lc[j][i];
		}
	}
	char to_print[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
	for(int i = 0; i < 7; ++i) {
		if(count[i]) {
			out << to_print[i] << " " << count[i] << "\n";
		}
	}
	in.close();
	out.close();
	return 0;
}

