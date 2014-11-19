/*
 * SortEstimate: Use binary search to find value of largest n such that it can
 * be sorted in c*n*log(n) time. Predicate is c*n*log(n) <= time. We have a
 * series of yes's followed by a no. We want last yes.
 */

#include <iostream>
#include <cmath>
#include <fstream>
#define ITERATIONS 400

using namespace std;

class SortEstimate {
public:
	double howMany(int c, int time);
};

bool predicate(double n, int time, int c) {
	return c * n * (log(n) / log(2)) <= time;
}

double SortEstimate::howMany(int c, int time) {
	double low = 1.0, high = time;
	double mid;
	
	int i = 0;
	while(i < ITERATIONS) {
		mid = (low * 1.0 + high) / 2;
		// yes
		if(predicate(mid, time, c)) {
			low = mid;
		} else {
			high = mid;
		}
		++i;
	}
	return mid;
}

int main() {
	ifstream in("se.in");
	int c, time;
	SortEstimate se;
	while(in >> c >> time) {
		cout << c << " " << time << " : ";
		cout << (double)se.howMany(c, time) << "\n";
	}
	in.close();
	return 0;
}
