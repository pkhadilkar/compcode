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

enum lamp_state {
	ANY = 0, ON, OFF
};

// globals to avoid arg passing
int N, C;
// take advantage of 0 initialization to default state of all lamps to 
// ANY = 0
lamp_state  lamps[TOTAL];

void val_combs(vector<string> & configs) {

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
