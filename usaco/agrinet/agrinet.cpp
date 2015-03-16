/*
ID: pushkar7
LANG: C++
PROB: agrinet
*/
#include <iostream>
#include <fstream>
#define MAX (101)
#define MAX_DIST (100001)
#define FOR(i, l, h) for(int i = l; i < h; ++i)

using namespace std;
int dist[MAX];      // min dist to a node in tree
bool visited[MAX];      // is a node in tree ?
int source[MAX];        // node which is in tree and has a min dist
int conn[MAX][MAX];

int N;

int prims() {
    int n = 1;  // number of nodes in tree
    int current = 0;    // node added in tree
    visited[0] = true;
    int t;
    int total = 0;

    while(n < N) {
        // adjust dists
        FOR(i, 0, N) {
            if(!visited[i] && dist[i] > conn[i][current]) {
                dist[i] = conn[i][current];
                source[i] = current;
            }
        }

        // find next node
        t = MAX_DIST;
        FOR(i, 0, N) {
            if(!visited[i] && dist[i] < t) {
                t = dist[i];
                current = i;
            }
        }

        //cout << "current = " << current << ", distance = " << dist[current] << "\n";
        // add node to tree
        total += t;
        visited[current] = true;
        ++n;
    }
    return total;
}

int main() {
    ifstream in("agrinet.in");
    ofstream out("agrinet.out");

    fill(dist, dist + MAX, MAX_DIST);
    fill(source, source + MAX, -1);

    in >> N;

    FOR(i, 0, N) {
        FOR(j, 0, N) {
            in >> conn[i][j];
        }
    }

    out << prims() << "\n";

    in.close();
    out.close();
    return 0;
}
