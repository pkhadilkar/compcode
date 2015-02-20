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
double D = MAX_DISTANCE * 2;
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
	 //cout << "computing pasture of " << l << endl;
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
				 //cout << i << " ";
			}
		}
	}
	//cout << endl;
    	pastures[l]= s;
}

void precompute() {

    // compute all pairs shortest paths
	FOR(k, 0, N) {
		FOR(i, 0, N) {
			FOR(j, 0, N) {
				double tmp = dist[i][k] + dist[k][j];
				if(tmp < dist[i][j]) {
					dist[i][j] = tmp;
				}
			}
		}
	}

	/*FOR(i, 0, N) {
		FOR(j, 0, N) {
			 cout << dist[i][j] << " ";
		}
		cout << endl;
	}*/


	fill(leader, leader + N, -1);
	FOR(i, 0, N) {
		if(leader[i] == -1) {
			pasture_of(i);
		}
	}
}

// p1 and p2 are now connected find new diameter
void find_diameter(set<int> *f1, set<int> * f2, int p1, int p2, double edge_distance) {
    double d = 0;

    for(SI xt = f1->begin(); xt != f1->end(); ++xt) {
        for(SI yt = f2->begin(); yt != f2->end(); ++yt) {
            double tmp = dist[*xt][p1] + dist[p2][*yt] + edge_distance;
            if(d < tmp)    {
		//cout << "d1 :" << d << "xt: " << *xt  << " yt: " << *yt << endl;
		d = tmp;
	    }
        }
    }

    set<int> * s = 0;

    if(f1->size() == 1 && f2->size() > 1) {
	s = f2;
    } else if(f2->size() == 1 && f1->size() > 1) {
	s = f1;
    }

    if(s != 0) {
    	for(SI xt = s->begin(); xt != s->end(); ++xt) {
        	for(SI yt = s->begin(); yt != s->end(); ++yt) {
	            double tmp = dist[*xt][*yt];
        		if(d < tmp)    {
				//cout << "d2 :" << d << "xt: " << *xt  << " yt: " << *yt << endl;
				d = tmp;
	    		}
        	}
    	}
    }

    /* cout << "D: " << D<< "\n"; */
    if(D > d)    D = d;
    //cout << "After D: " << D << "\n";
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
			}else if(dist[i][j] == 0 && i != j){
				dist[i][j] = MAX_DISTANCE;
			}
		}
	}

	precompute();

	// compute all pairs shortest paths

	FOR(i, 0, N) {
		FOR(j, i + 1, N) {
			if(!adj[i][j] && leader[i] != leader[j]) {
				 //cout << "i: " << i << " j: " << j << endl;

				set<int> *s_i = pastures[leader[i]];
				set<int> *s_j = pastures[leader[j]];
	            find_diameter(s_i, s_j, i, j, compute_distance(i, j));
			}
		}
	}

	out << fixed << setprecision(6) << D << "\n";

	in.close();
	out.close();
	return 0;
}
