/*
ID: pushkar7
LANG: C++
PROB: comehome
*/
#include <iostream>
#include <fstream>
#include <cassert>
#define SIZE (26+26)
#define MAX_DIST (1001)
#define FOR(i, l, h)    for(int i = l; i < h; ++i)
//#define NDEBUG
using namespace std;
int connected[SIZE][SIZE];
bool visited[SIZE];
int cow_name, cow_dist;
// dist from source
int dist[SIZE];
inline int to_vertex(char c) {
    if(c >= 'A' && c <= 'Z')
        return int(c - 'A');
    else
        return 26 + int(c - 'a');
}

inline char to_name(int i) {
    if(i < 26) return char('A' + i);
    else       return char('a' + i - 26);
}

// short circuited Dijkstra's algorithm
void shortest_path() {
    int v = to_vertex('Z');
    visited[v] = true;
    dist[v] = 0;
    int nearest, d;
    // find next closest vertex
    while(1) {
        // find tentative dists
        nearest = -1;
        d = MAX_DIST * SIZE;
        FOR(i, 0, SIZE) {
            if(!visited[i]) continue;
            FOR(j, 0, SIZE) {
                if(visited[j]) continue;
                if(connected[i][j] != 0 && connected[i][j] + dist[i] < d) {
                    nearest = j;
                    d = connected[i][j] + dist[i];
                }
            }
        }

        visited[nearest] = 1;
        dist[nearest] = d;
        char name = to_name(nearest);
        if(name >= 'A' && name <= 'Z') {
            cow_name = (int) name;
            cow_dist = d;
            break;
        }
    }
}

int main() {
    ifstream in("comehome.in");
    ofstream out("comehome.out");

    // asserts for sample functions
    assert(to_vertex('A') == 0 && to_vertex('Z') == 25);
    assert(to_vertex('a') == 26 && to_vertex('z') == 51);
    assert(to_name(0) == 'A' && to_name(25) == 'Z');
    assert(to_name(26) == 'a' && to_name(51) == 'z');

    FOR(i, 0, SIZE)
        dist[i] = MAX_DIST;

    int N, dist, from, to;
    char c1, c2;
    in >> N;
    FOR(i, 0, N) {
        in >> c1 >> c2 >> dist;
        from = to_vertex(c1);
        to = to_vertex(c2);
        connected[from][to] = connected[to][from] = dist;
    }

    shortest_path();
    out << (char) cow_name << " " << cow_dist << "\n";

    in.close();
    out.close();
    return 0;
}
