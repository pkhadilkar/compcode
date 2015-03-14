/*
ID: pushkar7
LANG: C++
PROB: fracdec
*/
#include <iostream>
#include <fstream>
#include <sstream>
#define MAX (100000)
using namespace std;

int N, D;
int a[MAX];
int r[MAX];
int index = MAX;      // index where repeats
int i;

void solve() {
    int rem, tmp;
    int n = N % D;

    while(n) {
        n *= 10;
        rem = n % D;
        tmp = n / D;
        if(r[rem] < MAX && a[r[rem]] == tmp) {
            // do something special here
            index = r[rem];
            break;
        }

        r[rem] = i;
        a[i++] = tmp; //n / D;
        //cout << "n = " << n << ", rem = " << rem << ", r[rem] =" << r[rem] << ", a[i] =" << a[i - 1] << "\n";
        n = rem;
    }
}

int main() {
    ifstream in("fracdec.in");
    ofstream out("fracdec.out");
    stringstream ss;
    string s;
    int decimal;

    in >> N >> D;
    decimal = N / D;

    for(int k = 0; k < D; ++k) {
        r[k] = MAX;
    }

    solve();

    ss << decimal << ".";

    if(N % D) {
    for(int j = 0; j < i; ++j) {
            if(j == index)
                ss << "(";
            ss << a[j];
    }

    if(index != MAX)
        ss << ")";
    } else  {
        ss << "0";
    }
    ss << "\n" ;
    s = ss.str();

    for(int j = 0; j < (int) s.length(); ++j) {
        if((j % 76) == 0 && j != 0)
            out << "\n";
        out << s[j] ;
    }

    in.close();
    out.close();
    return 0;
}
