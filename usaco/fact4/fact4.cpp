/*
ID: pushkar7
LANG: C++
PROB: fact4
*/
#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>

using namespace std;

int main() {
    ifstream in("fact4.in");
    ofstream out("fact4.out");

    int n;
    long long d = 1;
    int CEIL = pow(10, 7);
    in >> n;

    assert(sizeof(long long) > 4);

    for(int i = 2; i <= n; ++i) {
        d *= i;
        while(!(d % 10))
            d /= 10;
        d = d % CEIL;
        //cout << i << " " << d << "\n";
    }

    out << d % 10 << "\n";

    in.close();
    out.close();

    return 0;
}
