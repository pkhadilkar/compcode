#include <iostream>
#include <string>
#define COST_DOT	1
#define	COST_COMMA	2
#define COST_EXCL	3
#define COST_SPACE	1
using namespace std;

int main() {
	string slogan;
	getline(cin, slogan);
	int cost = 0;
	for(int i = 0; i < (int) slogan.length(); ++i) {
		switch(slogan[i]) {
			case '.':	cost = cost + COST_DOT; break;
			case ',':	cost = cost + COST_COMMA; break;
			case '!':	cost = cost + COST_EXCL; break;
			case ' ':	cost = cost + COST_SPACE; break;
			default:	cost = cost + ((slogan[i] - 'a') % 3) + 1;
		}
	}
	cout << cost << "\n";
	return 0;
}
