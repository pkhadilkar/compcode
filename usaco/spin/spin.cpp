/*
ID: pushkar7
LANG: C++
PROB: spin
*/
#include <iostream>
#include <fstream>
#include <cassert>
#define WHEELS (5)
#define WEDGES (5)
#define START	(0)
#define STOP	(1)
#define DEBUG	(0)
using namespace std;

int wheel_wedge[WHEELS][WEDGES][2];
int wedge_count[WHEELS];
int velocity[WHEELS];

int pos_n(int wheel, int wedge, int which, int time) {
	return (wheel_wedge[wheel][wedge][which] + velocity[wheel] * time) % 360;
}

bool overlaps(int start, int stop, int d) {
	if(start <= stop) {
		return (start <= d && d <= stop);
	} else {
		return !(d > stop && d < start);
	}
}

int main() {
	ifstream in("spin.in");
	ofstream out("spin.out");

	for(int i = 0; i < WHEELS; ++i) {
		in >> velocity[i] >> wedge_count[i];
		for(int j = 0; j < wedge_count[i]; ++j) {
			int p, q;
			in >> p >> q;
			wheel_wedge[i][j][START] = p;
			wheel_wedge[i][j][STOP] = (p + q) % 360;
			if(DEBUG) cout << "wheel  : " << "\t" << wheel_wedge[i][j][START] << "\t"<< wheel_wedge[i][j][STOP] << "\n";
		}
	}

	// solve
	int earliest = 361;
	for(int t = 0; t < 360; ++t) {	// time
		for(int d = 0; d < 360; ++d) {	// angle
			int is_wedge[WHEELS] = {0};
			for(int w = 0; w < WHEELS; ++w) {	// wheels
				for(int wd = 0; (wd < wedge_count[w]) && (is_wedge[w] == 0); ++wd) {	// wedges
					int start = pos_n(w, wd, START, t), stop = pos_n(w, wd, STOP, t);
					//if(t == 9) cout << w << "\t" << wd << "\t" << start << "\t" << stop << "\n";
					if(overlaps(start, stop, d)) {
						if(DEBUG)	assert(is_wedge[w] <= 1);
						is_wedge[w] = 1;
					}
				}
			}
			
			int i = 0;
			for(; i < WHEELS && is_wedge[i] == 1; ++i);
			if(i == WHEELS) {
				earliest = t;
				goto found_answer;
			}
		}
	}

found_answer:
	if(earliest == 361) {
		out << "none\n";
	} else {
		out << earliest << "\n";
	}

	in.close();
	out.close();
	return 0;
}
