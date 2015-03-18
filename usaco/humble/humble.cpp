/*
ID: pushkar7
LANG: C++
PROB: humble
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <climits>
#define MAX_N (100001)
#define MAX_K (101)

using namespace std;
long numbers[MAX_N];
long base[MAX_K];
int K, N;

long solve() {
    numbers[0] = 1;
    int ptrs[MAX_K] = {0};
    long tmp;
    int current;
    for(int i = 1; i <= N; ++i) {
        // generate i'th number
        tmp = LONG_MAX;
        // advance pointers
        for(int j = 0; j < K; ++j) {
            long l = base[j] * numbers[ptrs[j]];
            while(l <= numbers[i - 1] && ptrs[j] < i) {
                ++ptrs[j];
                //assert(ptrs[j] < i);
                l = base[j] * numbers[ptrs[j]];
            }

            if(l < tmp) {
                tmp = l;
                current = j;
            }
        }

        assert(current >= 0 && current < K);
        numbers[i] = tmp;
        // cout << i << "    " << numbers[i] << "\n";
    }

    return numbers[N];
}


int main() {
    ifstream in("humble.in");
    ofstream out("humble.out");

    in >> K >> N;
    for(int i = 0; i < K; ++i)
        in >> base[i];

    out << solve() << "\n";

    in.close();
    out.close();
    return 0;
}
