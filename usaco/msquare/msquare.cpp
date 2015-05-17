/*
ID: pushkar7
LANG: C++
PROB: msquare
*/
#include<iostream>
#include<fstream>
#include<set>
#include<queue>
#include <map>
#include<cassert>
#define SIZE (8)
#define STATE (40320)
#define DEBUG 0
#define STARTSTATE (12345678)
using namespace std;
// 1 2 3 4 8 7 6 5
int map_index[] = {0, 1, 2, 3, 7, 6, 5, 4};
// 0, 1, 2, 3, 4, 5, 6, 7
int transform1[3][8] = {
	{4, 5, 6, 7, 0, 1, 2, 3},
	{3, 0, 1, 2, 7, 4, 5, 6},
	{0, 5, 1, 3, 4, 6, 2, 7}
};
// transform[i][j] indicates index of element j in one configuration after 
// transformation i has been applied to it
typedef unsigned short ushort ;
int conf[SIZE];
int target;
set<int> visited;
map<int, int> parent_of;
map<int, char> sq;
int depth;

void print_state(int state[SIZE]) {
	for(int i = 0; i < SIZE; ++i) {
		if(i % (SIZE / 2) == 0)
			cout << "\n";
		cout << state[i] << " ";
	}
}

int state_to_int(int s[SIZE]) {
	int t = 0;
	for(int i = 0; i < SIZE /  2; ++i)
		t = t * 10 + s[i];
	for(int i = SIZE - 1; i >= SIZE / 2; --i)
		t = t * 10 + s[i];
	if(DEBUG) {
		print_state(s);	
		cout << "state_to_int: integer: " << t << "\n";
	}
	return t;
}


// apply transformation t to get adjacent vertex
int transform(int neighbour[SIZE], int t) {
	for(int i = 0; i < SIZE; ++i)
		neighbour[i] = conf[transform1[t][i]];
	if(DEBUG) {
		cout << "transformed: \n"	;
		print_state(neighbour);
	}
	return state_to_int(neighbour);
}

void int_to_state(int t) {
	for(int x = SIZE - 1; x >= 0; --x, t = t / 10) 
		conf[map_index[x]] = t % 10;
	if(DEBUG) {
		cout << "int_to_state: integer : " << t << "\n";
		print_state(conf);
	}
}

string bfs() {
	int_to_state(STARTSTATE);
	queue<int> q;
	int neighbour[SIZE];
	string path = "";
	
	int c = state_to_int(conf);
	assert(c == STARTSTATE);
	q.push(c);	
	visited.insert(c);
	depth = 0;
	parent_of[c] = -1;

	while(!q.empty()) {
		c = q.front(); q.pop();
		int_to_state(c);
		for(int i = 0; i < 3; ++i) {
			int next = transform(neighbour, i);
			if(visited.find(next) == visited.end()) {

				parent_of[next] = c;
				sq[next] = char('A' + i);

				if(next == target) {
					int t = next;
					while(t != STARTSTATE) {
						path = path + sq[t];
						t = parent_of[t];
					}
					return string(path.rbegin(), path.rend());
				}

				visited.insert(next);
				q.push(next);
			}
		}
	}
	return path;
}


int main() {
	ifstream in("msquare.in");
	ofstream out("msquare.out");

	
	for(int i = 0; i < SIZE; ++i)
		in >> conf[map_index[i]];
	
	target = state_to_int(conf);

	for(int i = 0; i < 3; ++i) {
		int neighbour[SIZE];
		//cout << "transformation number: " << i << "\n";
		transform(neighbour, i);
	}

	string s = bfs();
	out << s.length() << "\n";
	int i;
	for(i = 0; i < (int) s.length(); ++i) {
		if(i && (i % 60 == 0)) out << "\n";
		out << s[i];
	}
	if(i == 0 || (i % 60 != 0))
		out << "\n";

	in.close();
	out.close();
}

