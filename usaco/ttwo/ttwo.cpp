/*
ID: pushkar7
LANG: C++
PROB: ttwo
*/
#include <iostream>
#include <fstream>
#include <cstring>
#define N (0)
#define E (1)
#define S (2)
#define W (3)
#define FOR(i, l, h) for(int i = l; i < h; ++i)
#define OOB(x)	(x < 0 || x >= 10)
#define COMMENT if(0)
#define LARGE 99999
bool obstacle[10][10];	// true if there is an obstacle at (i, j)
int cowx, cowy;
int jx, jy;
int cow_cycle, john_cycle;
int cow_start, john_start;	// cycle start for cow and john
int cow[10 * 10 * 4];
int john[10 * 10 * 4];

using namespace std;

int gcd(int x, int y) {
	if(y == 0)	return x;
	else	return gcd(y, x % y);
}

void getnext(int & x, int & y, int direction) {
	int fromx = x, fromy = y;
	switch(direction) {
		case N: x -= 1; break;
		case E: y += 1; break;
		case W: y -= 1; break;
		case S: x += 1; break;
	}
	// see if we overshot or there is an obstacle
	if(OOB(x))	x = fromx;
	else if(OOB(y)) y = fromy;
	else if(obstacle[x][y])	{
		x = fromx; y = fromy;
	}
}

int key(int x, int y, int direction) {
	return ((10 * x + y) * 4) + direction;
}

// simulate traversal
void traverse(int x, int y, int * pos, int & cycle, int & start) {
	// starting direction is north
	int direction = N;
	int time = 0;
	int i;
	while(1) {
		// try continuing in the current direction
		int ox = x, oy = y;
		i = key(x, y, direction);
		if(pos[i] != -1) {
			// visited alread
			COMMENT cout << x << " " << y << " " << i << " " << pos[i] << "\n";
			break;
		}
		pos[i] = time++;
		getnext(x, y, direction);
		COMMENT cout << ox << " " << oy << " " << i << " " << pos[i] << "\n";
		// obstacle or overshoot
		if(ox == x && oy == y) {
			// change direction
			direction = (direction + 1) % 4;
		}
	}
	cycle = time - pos[i];
	start = pos[i];
	COMMENT cout << "cycle = " << cycle << " cycle_start = " << start << "\n";
}

int solve() {
	COMMENT	cout << "Cows\n";
	traverse(cowx, cowy, cow, cow_cycle, cow_start);
	COMMENT	cout << "John\n";
	traverse(jx, jy, john, john_cycle, john_start);
	// now we want to check for each vertex
	// at a given position, we have to check
	// if cows and Farmer John will meet. Now
	// if gcd of times is > 1 then they will
	// meet at that position at some time
	int j_c_gcd = gcd(cow_cycle, john_cycle);
	int smallest = LARGE;
	for(int x = 0; x < 10; ++x) {
		for(int y = 0; y < 10; ++y) {
			//cout << x << " " << y  << endl;
			FOR(cd, 0, 4) {
				FOR(jd, 0, 4) {
					int c = cow[key(x, y, cd)];
					int j = john[key(x, y, jd)];
					int old_c = c, old_j = j;
					if(c == -1 || j == -1)	continue;
					if(c < cow_start && j < john_start) {
						if(c == j && c != 0)
							smallest = (smallest < c) ? smallest: c;
					} else if(c < cow_start && j >= john_start) {
						while(j < c) {
							j += john_cycle;
						}
						if(c == j && old_j != 0)
							smallest = (smallest < c) ? smallest: c;
					} else if(c >= cow_start && j < john_start) {
						while(c < j) {
							c += cow_cycle;
						}
						if(c == j && old_c != 0)
							smallest = (smallest < c) ? smallest: c;
					}
					else if( ((c - j) % j_c_gcd) == 0) {
						// raise c and j appropriately
						while(c != j) {
							if(c < j) c += cow_cycle;
							else	  j += john_cycle;
						}
						smallest = (smallest < c) ? smallest: c;
					}
				}
			}
		}
	}
	return (smallest == LARGE) ? 0 : smallest;
}

int main() {
	ifstream in("ttwo.in");
	ofstream out("ttwo.out");
	
	ios_base::sync_with_stdio(false);
	memset(cow, -1, sizeof(cow));
	memset(john, -1, sizeof(john));

	FOR(i, 0, 10) {
		FOR(j, 0, 10) {
			char x;
			in >> x;
			if(x == '*')	obstacle[i][j] = true;
			else if(x == 'C') {
				cowx = i; cowy = j;
			} else if(x == 'F') {
				jx = i; jy = j;
			}
		}
	}

	out << solve() << "\n";
	in.close();
	out.close();
	return 0;
}
