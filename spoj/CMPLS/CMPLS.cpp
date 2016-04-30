#include<iostream>
#define MAX_LEN (100)
#define DEBUG (0)
using namespace std;

int S, C;
int table[MAX_LEN][MAX_LEN];

inline int layer_n(int layer) {
	return (S - layer);
}

bool is_constant(int layer) {
	int l = table[layer][0];
	for(int i = 0; i < layer_n(layer); ++i) {
		if(table[layer][i] != l)
			return false;
	}
	return true;
}

void print_table() {
	for(int i = 0; i < S; ++i) {
		for(int j = 0; j < S + C; ++j)
			cout << table[i][j] << "\t";
		cout << "\n";
	}
}

void solve() {
	int layer = 0;
	while(!is_constant(layer)) {
		// do something 
		for(int i = 0; i + 1 < layer_n(layer); ++i) 
			table[layer + 1][i] = table[layer][i + 1] - table[layer][i];
		++layer;
	}


	// now re-construct remaining numbers
	for(int i = layer_n(layer); i < layer_n(layer) + C; ++i)	if(i) table[layer][i] = table[layer][i - 1];
	--layer;
	for(int i = layer; i >= 0; --i) {
		for(int j = layer_n(i); j < layer_n(i) + C; ++j) {
			table[i][j] = table[i][j - 1] + table[i + 1][j - 1];
			if(DEBUG) cout << i << " " << j << ":" << table[i][j] << "\n";
		}
	}

	if(DEBUG) print_table();
	if(DEBUG) cout << "\n";
}


void print() {
	for(int i = 0; i < C; ++i) {
		cout << table[0][S + i] << " ";
	}
	cout << "\n";
}

int main() {
	int t;
	cin >> t;

	for(int i = 0; i < t; ++i) {
		cin >> S >> C;
		for(int j = 0; j < S; ++j) {
			cin >> table[0][j];
		}
		solve();
		print();
	}
}
