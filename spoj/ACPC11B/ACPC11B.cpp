#include <iostream>
#include <cmath>
#include <fstream>
#define MAX_DIST 1000000
using namespace std;

void read_array(int * n, int * array) {
	scanf("%d", n);
	for(int j = 0; j < *n; ++j)
		scanf("%d", &array[j]);
}


inline int local_abs(int a) {
	return (a < 0 ? ((-1) * a): a);
}

int main() {
	int t;
	scanf("%d", &t);

	int a[1000], b[1000];
	for(int i = 0; i < t; ++i) {
		int n1, n2, d1, d2;
		read_array(&n1, a);
		read_array(&n2, b);

		int alt = MAX_DIST;
		for(int p = 0; p < n1; ++p) {
			for(int q = 0; q < n2; ++q) {
				alt = min(alt, local_abs(b[q] - a[p]));
			}
		}
		/*while(p < n1 && q < n2) {
			alt = min(alt, local_abs(a[p] - b[q]));
			d1 = d2 = MAX_DIST;
			if(p + 1 < n1)
				d1 = local_abs(a[p + 1] - b[q]);
			if(q + 1 < n2)
				d2 = local_abs(a[p] - b[q + 1]);
			if(d1 <= d2) ++p;
			else	++q;
		}*/
		printf("%d\n", alt);
	}

	return 0;
}
