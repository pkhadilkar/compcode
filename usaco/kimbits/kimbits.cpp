/*
ID: pushkar7
LANG: C++
PROB: kimbits
*/
#include <iostream>
#include <cmath>
#include <fstream>
#include <cassert>

unsigned int N, L, I;
char bits[32];
// N: NUmber of bits
// L: Number of 1's max
// I: Index of number to print
using namespace std;
typedef unsigned long ulong;

ulong gcd(ulong x, ulong y) {
	if(y == 0)	return x;
	else	return gcd(y, x % y);
}

ulong choose(ulong n, ulong k) {
	if(k == 0)	return 1;
	ulong r = choose(n - 1, k - 1);
	if (r % k == 0) {
		r /= k;
	} else {
		ulong x = gcd(n , k);
		n /= x;
		k /= x;
		x = gcd(k, r);
		k /= x;
		r /= x;
	}
		return (n * r);
}

int to_bits(ulong n) {
	int d = 0;
	for(int i = 0; i <= 32; ++i) bits[i] = '0';
	while(n) {
		bits[d++] = char((n & 1) + '0');
		n >>= 1;
	}
	return d;
}

// how many numbers smaller or equal than bits are not valid
ulong smaller_not_valid(int d) {

	ulong not_valid = 0;

	// among those invalid, count ones that have exactly i 1's
	for(int i = L + 1; i <= (int) N; ++i) {

		not_valid += choose(N, i);

		int count1 = 0;	// count of 1's
		for(int j = N - 1; j >= 0; --j) {
			if(bits[j] == '1') { ++count1; continue;}
			// positions d through j are fixed
			// some 1s have already been spent in fixed posiitions
			//  combinations of remaining ones need to be considered
			int number_of_1s = i - count1 - 1;
			if(number_of_1s < 0)	break;
			not_valid -= choose(j, number_of_1s);
		}
	}

	return not_valid;

}

// predicate(n) returns true if the index of current number in seq. of valid
// numbers is >= I
bool predicate(ulong n) {
	int d = to_bits(n);
	ulong a = smaller_not_valid(d);
	ulong index = n - a + 1;
	//cout << "n " << n  << ", a: " << a << ", index: " << index <<"\n";
	return index >= I;
}

void solve() {
	ulong low = 0, high = pow(2, N);
	ulong mid = 0;
	//cout << low << " " << high << "\n";
	while(low < high) {
		mid = low + (high - low) / 2;
		if(predicate(mid))	high = mid;
		else				low = mid + 1;
	}
	//cout << "answer is: " << low << "\n";
	to_bits(low);
}

int main() {
    ifstream in("kimbits.in");
    ofstream out("kimbits.out");

    in >> N >> L >> I;
	solve();

	for(int i = N - 1; i >= 0; --i) {
		out << bits[i];
	}

	out << "\n";
    in.close();
    out.close();
    return 0;
}
