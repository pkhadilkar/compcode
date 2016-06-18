#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>
#define MAX 	(100000)
#define M(p)	(p.first)
#define F(p)	(p.second)
#define pu	pair<ui, ui>
#define MIN(x, y)	(x < y ? x : y)
using namespace std;

typedef unsigned int ui;
typedef unsigned long ul;
pair<ui, ui> lpairs[MAX];
ui	females[MAX];
ui	tmp[MAX];

// merge females[i, mid - 1] and females[mid + 1, right - 1]
ul inline merge(int left, int mid, int right) {
	ul intersections = 0;
	int i = left, j = mid, k = left;
	while (i < mid && j < right) {
		if (females[i] < females[j]) {
			tmp[k++] = females[i++];
		} else {
			tmp[k++] = females[j++];
			// female j intersects with all
			// females remaining in left
			// cout << (mid - i) << endl;
			intersections += (mid - i);
		}
	}
	while(i < mid)
		tmp[k++] = females[i++];
	while(j < right)
		tmp[k++] = females[j++];
	// copy back tmp
	for(int l = left; l < right; ++l)
		females[l]=tmp[l];
	return intersections;
}

// returns number of conflicting pairs through merge sort
ul merge_count(int N) {
	ul intersections = 0;
	
	for(int width = 1; width < N; width *= 2)
	{
		for(int i = 0; (i + width) < N; i += 2 * width) {
			int left = i;
			int mid  = i + width;
			int right = MIN(i + 2 * width, N);
			// [mid + 1] to right must contain atleast one element to merge
			// mid is guaranteed to be less than N. Thus, right to mid
			// must have atleast one element
			//assert(right - mid > 0);
			intersections += merge (left, mid, right);
		}
	}

	return intersections;
}


int main() {
	int N;

	ios_base::sync_with_stdio(false);
	cin >> N;
	for(int i = 0; i < N; ++i) {
		cin >> M(lpairs[i]) >> F(lpairs[i]);
	}

	sort(lpairs, lpairs + N);
	for(int i = 0; i < N; ++i) {
		females[i] = F(lpairs[i]);
	}

	// find intersecting pairs
	cout << merge_count(N) << "\n";

	return 0;
}
