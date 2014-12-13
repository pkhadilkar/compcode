/*
LANG: C
ID: pushkar7
PROB: zerosum
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 9
int N;	// number of integets allowed
FILE * in;
FILE * out;
int total = 0;
char s[2* MAX];
char all[4374][2 * MAX];

int qsort_strcmp(const void * p, const void * q) {
	char* x = (char *) p;
	char* y = (char *) q;
	return strcmp(x, y);
}

// aggr = total expression value
// prev_sum = useful if space is used as prev operator. absolute value.
// prepend operators. latest_arith -1 for -, +1 otherwise
void rec_sum(int start, int aggr, int prev_sum, int latest_arith){

	if(start > N) {
		// can't have aggr = 0 unless we use 
		// atleast one non-space
		if(aggr == 0) {
			strcpy(all[total++], s);
		}
		return;
	}
	
	// try all operators
	s[2 * start - 2] = (char)('0' + start);
	s[2 * start - 3] = '+';
	rec_sum(start + 1, aggr + start, start, 1);
	s[2 * start - 3] = '-';
	rec_sum(start + 1, aggr - start, start, -1);
	s[2 * start - 3] = ' ';
	int x = (prev_sum * 10 + start);
	rec_sum(start + 1, aggr - latest_arith * (prev_sum - x), x, latest_arith);
}

int main() {
	int i;
	in = fopen("zerosum.in", "r");
	out = fopen("zerosum.out", "w");

	fscanf(in, "%d", &N);
	s[0] = '1';
	rec_sum(2, 1, 1, 1);

	qsort(all, total, 2 * MAX * sizeof(char), qsort_strcmp);
	for(i = 0; i < total; ++i) {
		fprintf(out, "%s\n",all[i]);
	}
	fclose(in);
	fclose(out);
	return 0;
}
