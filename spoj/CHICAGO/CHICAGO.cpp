#include <iostream>
#include <functional>
#include <iomanip>
#include <set>
#include <list>
#define MAX_N (100)
#define pi pair<int, int>
#define MIN_DIST (0)
#define DEBUG (0)
using namespace std;
int N, M;
double dist[MAX_N];
bool visited[MAX_N];
list< pi > adj[MAX_N];


void print_list(list< pi > l) {
	for(list< pi >::iterator it = l.begin(); it != l.end(); ++it)
		cout << it->first << ", " << it->second << "\t";
	cout << "\n";
}

double longest_path() {
	set< pair<double, int> , greater<pair<double, int> > > heap;
	fill(visited, visited + MAX_N, false);
	fill(dist, dist + N, MIN_DIST);
	dist[0] = 1; 	// probablity of reaching 1 is 1
	heap.insert( pair<double, int>(1, 0) );

	while(!heap.empty()) {
		pair<double, int> p = *heap.begin();
		int vertex = p.second;
		double d = p.first;
		visited[vertex] = true;
		if(DEBUG) cout << "vertex: " << vertex << ", distance:" << d << "\n";
		heap.erase(heap.begin());
		if(DEBUG) print_list(adj[vertex]);
		// adjust distances to neighbours of p.second
		for(list< pi >::iterator it = adj[vertex].begin(); it != adj[vertex].end(); ++it){
			double next = d * (it->second / 100.0);
			if(DEBUG) cout << "\tnext: " << next << "\n";
			if(!visited[it->first] && next > dist[it->first]) {
				if(DEBUG) cout << "\tUpdating : " << it->first << "\n";
				heap.erase( pair<double, int> (dist[it->first], it->first));
				heap.insert(pair<double, int>(next, it->first));
				dist[it->first] = next;
			}
		}
	}
	
	return dist[N - 1];
}

void init() {
	for(int i = 0; i < N; ++i)	adj[i].clear();
}

int main() {
	while(1) {
		cin >> N;
		if(N == 0) break;
		init();
		cin >> M;
		for(int i = 0; i < M; ++i) {
			int x, y, z;
			cin >> x >> y >> z;
			--x; --y;
			adj[x].push_back(pi(y, z));
			adj[y].push_back(pi(x, z));
		}
		cout << fixed << setprecision(6) << 100 * longest_path() << " percent\n";
	}

	return 0;
}
