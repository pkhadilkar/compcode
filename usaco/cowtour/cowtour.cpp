/*
ID: pushkar7
LANG: C++
PROB: cowtour
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <fstream>
#include <iomanip>
#define FOR(i, l, h)	for(int i = l; i < h; ++i)
#define MAX_PASTURES (150)
#define MAX_DISTANCE (150000.0)
#define SI set<int>::iterator
using namespace std;
int N;
double D = -1;
bool adj[MAX_PASTURES][MAX_PASTURES];
int loc[MAX_PASTURES][2];
double dist[MAX_PASTURES][MAX_PASTURES];
int leader[MAX_PASTURES];
map<int, set<int>* > pastures;	// get pasture given leader id

double compute_distance(int i, int j) {
	double x = 1.0 * pow(loc[i][0] - loc[j][0], 2);
	double y = 1.0 * pow(loc[i][1] - loc[j][1], 2);
	return sqrt(x + y);
}

void pasture_of(int l) {
	cout << "computing pasture of " << l << endl;
	leader[l] = l;
	set<int> * s = new set<int>();
	queue<int> q;
	s->insert(l);
	q.push(l);
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		FOR(i, 0, N) {
			if(adj[x][i] && s->find(i) == s->end()) {
				q.push(i);
				s->insert(i);
				leader[i] = l;
			}
		}
	}
	pastures[l]= s;
}

void modify_shortest(set<int> & s) {
	double dist_copy[MAX_PASTURES][MAX_PASTURES];
	memcpy(&dist_copy[0][0], &dist[0][0], sizeof(dist));
	for(SI j = s.begin(); j != s.end(); ++j) {
		for(SI i = s.begin(); i != s.end(); ++i) {
			if(*i == *j)	continue;
			for(SI k = s.begin(); k != s.end(); ++k) {
				if(*i == *k || *j == *k)	continue;
				// find shortes path from i to k through j
				double x = dist_copy[*i][*j] + dist_copy[*j][*k];
				if(dist_copy[*i][*k] > x) {
					dist_copy[*i][*k] = x;
				}
			}
		}
	}

	double local_max = 0.0;

	for(SI i = s.begin(); i != s.end(); ++i) {
		for(SI j = s.begin(); j != s.end(); ++j) {
			if(*i == *j)	continue;
			if(dist_copy[*i][*j] > local_max)
				local_max = dist_copy[*i][*j];
		}
	}

	if(D == -1 || local_max < D)
		D = local_max;
}


void precompute() {
	fill(leader, leader + N, -1);
	FOR(i, 0, N) {
		if(leader[i] == -1) {
			pasture_of(i);
		}
	}
}

int main() {
	ifstream in("cowtour.in");
	ofstream out("cowtour.out");
	ios_base::sync_with_stdio(false);
	in >> N;
	FOR(i, 0, N) {
		in >> loc[i][0] >> loc[i][1];
	}

	FOR(i, 0, N) {
		string s;
		in >> s;
		FOR(j, 0, N) {
			adj[i][j] = (s[j] == '1');
			if(adj[i][j] && i < j) {
				dist[i][j] = dist[j][i] = compute_distance(i, j);
			} else if(dist[i][j] == 0){
				dist[i][j] = MAX_DISTANCE;
			}
		}
	}

	precompute();

	// compute all pairs shortest paths

	FOR(i, 0, N) {
		FOR(j, i + 1, N) {
			if(!adj[i][j] && leader[i] != leader[j]) {
				cout << "i: " << i << " j: " << j << endl;
				adj[i][j] = adj[j][i] = true;
				dist[i][j] = dist[j][i] = compute_distance(i, j);
				set<int> s;
				set<int> *s_i = pastures[leader[i]];
				set<int> *s_j = pastures[leader[j]];
				
				s.insert(s_i->begin(), s_i->end());
				s.insert(s_j->begin(), s_j->end());
				modify_shortest(s);
				adj[i][j] = adj[j][i] = false;
				dist[i][j] = dist[j][i] = MAX_DISTANCE;
			}
		}
	}

	out << fixed << setprecision(6) << D << "\n";

	in.close();
	out.close();
	return 0;
}
