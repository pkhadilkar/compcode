#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#define MIN_VAL (-2000000000)
#define MAX_VAL (2000000000)
using namespace std;

class UnionOfIntervals {
public:
	int nthElement(vector<int> lowerBound, vector<int> upperBound, int n);
};

// pred should return true if position of x is
// greater than or equal to n.
bool pred(long x, vector<int> & l, vector<int> & r, int n) {
	long position = 0;
	bool first = true;
	// duplicates complicate this predicate
	// they can occur anywhere in the interval
	for(int i = 0; i < (int) l.size(); ++i) {
		if(l[i] <= x && r[i] >= x) {
			position += x - l[i];
			if(!first) ++position;
			first = false;
		}
		else if(r[i] < x) {
			position +=  r[i] - l[i] + 1;
		}
	}

	return (position >= n);
}

int UnionOfIntervals::nthElement(vector<int> lowerBound, vector<int> upperBound, int n) {
	long low = MAX_VAL, high = MIN_VAL, mid;
	for(int i = 0; i < (int)lowerBound.size(); ++i) {
		low = min(low, long(lowerBound[i]));
		high = max(high, long(upperBound[i]));
	}

	while(low < high) {
		mid = low + (high - low) / 2;

		if(pred(mid, lowerBound, upperBound, n)) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}

	bool exists = false;
	int next = MAX_VAL;	// smallest number larger than x that is in interval
	for(int i = 0; i < (int) lowerBound.size() && !exists; ++i) {
		if(lowerBound[i] <=low && upperBound[i] >= low){
			exists = true;
		}
		if(lowerBound[i] > low)
			next = min(next, lowerBound[i]);
	}

	if(exists)	return low;
	else	return next;

}

//-------------------------------------------------
void atov(int * a, int n, vector<int> & v) {
	for(int i = 0; i < n; ++i)
		v.push_back(a[i]);
}

int main() {
	UnionOfIntervals u;
	vector<int> a, b;
	int x[] = {-1500000000};
	int y[] = {1500000000};
	atov(x, 1, a);
	atov(y, 1, b);
	cout << u.nthElement(a, b, 1500000091) << "\n";
}
