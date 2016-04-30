#include <iostream>
#include <map>
#include <cassert>
#define MAX_N (30000)
#define DEBUG (0)
using namespace std;
int N;
int order[MAX_N];
int tmp[MAX_N];

int combine(int * source, int low, int mid, int high) {
	int l = low, r = mid + 1, n = 0;
	int inv = 0;
	while(l <= mid && r <= high) {
		if(source[l] <= source[r]) {
			tmp[n++] = source[l++];
		} else {
			inv += (mid - l + 1);
			tmp[n++] = source[r++];
		}
	}
	while(l <= mid)	tmp[n++] = source[l++];
	while(r <= high) tmp[n++] = source[r++];
	assert(n == high - low + 1);
	for(int i = low; i - low < n; ++i)	source[i] = tmp[i - low];

	return inv;	
}

int merge_and_count(int * source, int low, int high) {
	if (low >= high)
		return 0;	// no inversions, already sorted
	int mid = low + (high - low) / 2;
	int l = merge_and_count(source, low, mid);
	int r = merge_and_count(source, mid + 1, high);
	return l + r + combine(source, low, mid, high);
}

int inversion_count() {
	return merge_and_count(order, 0, N - 1);
}

void print_order() {
	for(int i = 0; i < N; ++i)
		cout << order[i] << " ";
	cout << "\n";
}

int main() {
	int t;
	cin >> t;

	for(int i = 0; i < t; ++i) {
		cin >> N;
		map<string, int> wp;
		for(int j = 0; j < N; ++j) {
			string s;
			cin >> s;
			wp[s] = j;
		}
		for(int j = 0; j < N; ++j) {
			string s;
			cin >> s;
			//if(DEBUG) cout << s << " " << wp[s] << " " << j << endl;
			order[wp[s]] = j;	
		}
		if(DEBUG) print_order();
		cout << inversion_count() << "\n";
		if(DEBUG) print_order();
	}

	return 0;
}
