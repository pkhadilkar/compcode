/*
ID: pushkar7
LANG: C++
PROB: butter
*/
#include<iostream>
#include<vector>
#include<set>
#include<utility>
#include<fstream>
#define MAX_PASTURES (800)
#define MAX_PATHS (1450)
#define MAX_COWS (500)
#define FOR(i, l, h)	for(int i = (l); i < (h); ++i)
#define pi	 pair<int, int> 
#define DEBUG	0
#define MAX_INT (800 * 225 * 500 + 1)
using namespace std;

int N, P, C;
vector< pi > graph[MAX_PASTURES];
int cows[MAX_PASTURES];	// track number of cows in pasture 

int min_dist(int n) {
	set< pi , less< pi > >  heap;
	int dist[P];	// distance to pasture n
	int tot_dist = 0;
	
	fill(dist, dist + P, MAX_INT);
	dist[n] = 0;
	heap.insert(pi(0, n));
	while(!heap.empty()) {
		pi next = *(heap.begin());
		int v = next.second, d = next.first;
		heap.erase(pi(d, v));
		tot_dist += d * cows[v];
		if(DEBUG) cout << "\t min dist to " << v << " is " << d << "\n";	
		FOR(i, 0, int(graph[v].size())) {
			int new_dist = d + graph[v][i].second;
		  	int new_v = graph[v][i].first;
			if(dist[new_v] > new_dist) {
				heap.erase(pi(dist[new_v], new_v));
				dist[new_v] = new_dist;
				heap.insert(pi(dist[new_v], new_v));
			}
		}
	}

	return tot_dist;
}

// run Dijkstra's algorithm from each pasture as starting
// point. Calculate weighted average of distance and return
// minimum
int cube_pos() {
	int dist = MAX_INT;
	FOR(i, 0, P) {
		int x = min_dist(i);
		if(DEBUG) cout << x << " " << i << "\n";
		if(x < dist) 	dist = x;
	}

	return dist;
}

int main() {
	ifstream in("butter.in");
	ofstream out("butter.out");
	

	in >> N >> P >> C;

	FOR(i, 0, N) {
		int j;
		in >> j;
		++cows[j - 1];
	}		

	FOR(x, 0, C) {
		int i, j, l;
		in >> i >> j >> l;
		--i;
		--j;
		graph[i].push_back(pi(j, l));
		graph[j].push_back(pi(i, l));
	}

	out << cube_pos() << "\n";
	
	in.close();
	out.close();
	return 0;
}
