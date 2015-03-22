/*
LANG: C++
PROB: contact
ID: pushkar7
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <fstream>
#define MAX (200000+1)
#define PAIR(i, j)  (pair<int, int>(i, j))
using namespace std;
int A, B, N, L;
char str[MAX];
// map from frequency to patterns that occur in that frequency
map< int, set< pair<int, int> > > pcnt;
// pair.first will number of digits
// pair.second will contain decimal number whose binary representation is
// the pattern we want

// return decimal representation of the string
// between start and stop index
int inline get_decimal(int start, int stop) {
    int n = 0;
    for(int i = start; i < stop; ++i) {
        n = n * 2 + int(str[i] - '0');
    }
    return n;
}

string to_binary(int n, int d) {
    string s = "";
    while(n) {
        s += char(n % 2 + '0');
        n /= 2;
        --d;
    }

    while(d) {
        s += '0';
        --d;
    }

    return string(s.rbegin(), s.rend());
}
// m is a map from pattern to frequency
void most_frequent(map<int, int> & m , int i) {
    vector< pair<int, int> > v;
    for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
        v.push_back(PAIR(it->second, it->first));
    }

    sort(v.rbegin(), v.rend());
    // insert top N in map
    //int h = N > (int) v.size() ? v.size() : N;
    for(int k = 0, j = 0; j < (int) v.size() && k <= N; ++j) {
        if(j == 0 || v[j].first != v[j - 1].first) {
            // found new frequency
            ++k;
        }

        set< pair<int, int> > * s;
        int value = v[j].first;
        int number = v[j].second;
        if(pcnt.find(value) == pcnt.end())
            pcnt[value] = set < pair <int, int> >();
        s = &pcnt[value];
        s->insert(PAIR(i, number));
        //pcnt[PAIR(i, v[j].second)] = v[j].first;
    }
}

// find patterns of length i
void search_pattern(int i) {
    map<int, int> patternMap;
    if(i > L)   return;
    // we know atleast one pattern exists
    // construct first string
    int n = get_decimal(0, i);
    int mask = (int) pow(2, i - 1);
    // process the first pattern
    patternMap[n] += 1;

    for(int j = 1; j + i <= L; ++j) {
        // one character goes out of scope and the next comes in scope
        if(n >= mask)   n -= mask;
        n = n * 2 + int(str[j + i - 1] - '0');
        patternMap[n] += 1;
    }
    // retain top N patterns or all if there are only N
    most_frequent(patternMap, i);
}

void solve() {

    for(int i = A; i <=B; ++i) {
            // handle patterns of length i
            //cout << "searching patterns of length " << i << endl;
            search_pattern(i);
    }
}

int main() {
    ifstream in("contact.in");
    ofstream out("contact.out");
    char c;

    in >> A >> B >> N;

    while(in >> c) {
        str[L++] = c;
    }

    solve();
    //cout << "solved\n";
    //cout << pcnt.size() << "\n";
    // get overall most frequent
    int j = 0;
    for(map<int, set < pair<int, int> > >::reverse_iterator it = pcnt.rbegin(); (it != pcnt.rend()) && j < N; ++it, ++j) {
        int value = it->first;
        set< pair <int, int> > * s = &(it->second);
        out << value;
        int k = 0, i = s->size();
        //cout << value << ", set size = " << i << "\n";
        for(set< pair<int, int> >::iterator st = s->begin(); st != s->end(); ++st, ++k, --i) {
            if(k % 6 == 0)  out << "\n";
            out << to_binary(st->second, st->first);
            if((k + 1) % 6 != 0 && i > 1)       out << " ";
        }
        if((k - 1) % 6 != 0 || (k % 6) == 1)
            out << endl;
    }

    in.close();
    out.close();
    return 0;
}
