#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class CombinationLock {
public:
	double degreesTurned(vector <int> combo, int size, int start);
};

int inline distance(int p, int q, int direction, int size) {
	if(direction == 1) { // anti-clockwise i.e. increasing 
		if(p <= q)	return (q - p);
		else		return ((size - p) + q);
	} else {
		if(p <= q)	return (p + (size - q));
		else		return (p - q);
	}
}

double CombinationLock::degreesTurned(vector <int> combo, int size, int start) {
	double d = 0;
	int n = combo.size();
	int direction = 1;	// 1 is anit-clockwise
	double unit = 360.0 / size;
	int current = 0;
	for(int i = n; i >= 1; --i, ++current) {
		d += 360 * i;
		d += unit * distance(start, combo[current], direction, size);
		start = combo[current];
		direction *= (-1);
	}
	return d;
}
