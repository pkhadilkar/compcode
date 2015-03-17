/*
LANG: C++
ID: pushkar7
PROB: inflate
*/
#include <iostream>
#include <fstream>
#define MAX (10001)
using namespace std;

int M, N;
int dp[MAX];
int points[MAX];
int minutes[MAX];

int solve() {
    int  p;
    for(int m = 1; m <= M; ++m) {
        int tmp = 0;
        // points using 1 instance of category c
        for(int c = 0; c < N; ++c, p = 0) {
            if(minutes[c]  <= m) {
                p = points[c];
                if(m - minutes[c] > 0)
                    p += dp[m - minutes[c]];
            }
            tmp = (tmp < p) ? p : tmp;
        }
        dp[m] = tmp;
    }
    return dp[M];
}

int main() {
    ifstream in("inflate.in");
    ofstream out("inflate.out");

    in >> M >> N;

    for(int i = 0; i < N; ++i)
        in >> points[i] >> minutes[i];

    out << solve() << endl;


    in.close();
    out.close();
    return 0;
}
