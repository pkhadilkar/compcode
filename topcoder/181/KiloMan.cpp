#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class KiloMan {
public:
	int hitsTaken(vector <int> pattern, string jumps);
};

int KiloMan::hitsTaken(vector <int> pattern, string jumps) {
	int c = 0;
	for(int i = 0; i < pattern.size(); ++i) {
		c += (pattern[i] <= 2 && jumps[i] = 'S'
				|| pattern[i] > 2 && jumps[i] = 'J');
	}
	return c;
}
