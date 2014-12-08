/*
LANG: C++
ID: pushkar7
PROB: prefix
*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

char pr[200 + 1][11];
int prl[200 + 1];
char s[200000+1];
int longest[200000 + 1];
int n = 0;	// number of primitives
int sl = 0; 	//sequence length

bool prefix_of(char * s, char * p) {
	while(*p && *s) {
		if(*s != *p)	return false;
		++s;
		++p;
	}

	return (*p == 0);
}

// find longest prefix
int lp() {
	// find largest prefix length for
	// string s[i .... (sl - 1)] and
	// propogate that length backwards
	int total = 0, x;
	for(int i = sl - 1; i >= 0; --i) {
		for(int j = 0; j < n; ++j) {
			// check if pr is prefix of string
			if(prefix_of(&s[i], pr[j])) {
				x = prl[j] + i;
				total = prl[j] + (x < sl ? longest[x] : 0);
				longest[i] = max(longest[i],  total);
			}
		}
	}
	return longest[0];
}

int main() {
	FILE * in = fopen("prefix.in", "r");
	FILE * out = fopen("prefix.out", "w");
	
//	int n = 0;			// number of primitives
	do {
		fscanf(in, "%s", pr[n]);
		prl[n] = strlen(pr[n]);
		++n;
	}while(strcmp(pr[n - 1], "."));

	char c;
	while(1) {
		fscanf(in, "%c", &c);
		if(feof(in)) {
			s[sl++]='\0';
			break;
		}
		if(c != '\n')
			s[sl++] = c;	
	}

	int l = lp();
	fprintf(out, "%d\n", l);

	fclose(in);
	fclose(out);
	return 0;
}
