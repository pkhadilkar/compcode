/*
ID: pushkar7
LANG: C++
PROB: maze1
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <queue>
#define PII  pair<int, int>
#define MAX_H (100)
#define MAX_W (38)
#define EXTREME(i, h) (i == 0 || i == h)
#define OOB(i, h) (i < 0 || i >= h)
using namespace std;

int h, w;
char grid[2* MAX_H + 1][2 * MAX_W + 1 + 1];
int md[MAX_H][MAX_W];
// N E S W
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

// every node has two neighbours
PII nbr[4];
int exits[2][2];

// returns number of "accessible' neighbours
int get_neighbours(int x, int y) {
	int n = 0;
	for(int i = 0; i < 4; ++i) {
		int x1 = (x * 2) + 1 + dx[i];
		int y1 = (y * 2) + 1 + dy[i];
		if(grid[x1][y1] == ' ') {
			nbr[n++]= make_pair(x + dx[i], y + dy[i]);
			//cout << x + dx[i] << " " << y + dy[i] << "\n";
		}
	}
	return n;
}

// find distances to all points
// given distance to x, y
void distances(int x, int y) {
	queue< PII > q;
	q.push(make_pair(x, y));
	while(!q.empty()) {
		PII p = q.front();
		q.pop();
		int n = get_neighbours(p.first, p.second);
		for(int i = 0; i < n; ++i) {
			int x1=nbr[i].first, y1 = nbr[i].second;
			if(OOB(x1, h) || OOB(y1, w)) continue;
			if(md[x1][y1] > md[p.first][p.second] + 1) {
				md[x1][y1] = md[p.first][p.second] + 1;
				q.push(nbr[i]);
			}
		}
	}
}

int main() {
	ifstream in("maze1.in");
	ofstream out("maze1.out");

	in >> w >> h;
	in.getline(grid[0], sizeof(grid[0]));
	fill(&md[0][0], &md[0][0] + sizeof(md) / sizeof(md[0][0]), MAX_W * MAX_H + 1);
	for(int i = 0; i < 2 * h + 1; ++i) 
		in.getline(grid[i], sizeof(grid[i]));

	int e = 0;
	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			if(!(EXTREME(i, h - 1) || EXTREME(j, w - 1))) continue;
			int n = get_neighbours(i, j);
			for(int k = 0; k < n;++k)
				if(OOB(nbr[k].first, h) || OOB(nbr[k].second, w)){
					exits[e][0] = i;
					exits[e++][1] = j;
					md[i][j] = 1;
					distances(i, j);
				}
		}
	}
	
	int d = 0;
	for(int i = 0; i < h; ++i)
		for(int j = 0; j < w; ++j)
			d = (d < md[i][j]) ? md[i][j]: d;

	out << d << "\n";
	in.close();
	out.close();
	return 0;
}
