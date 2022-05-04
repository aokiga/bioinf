#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> par;

#define all(x) (x).begin(), (x).end()

int f(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'T') return 2;
    if (c == 'G') return 3;
}

char f1(int c) {
    if (c == 0) return 'A';
    if (c == 1) return 'C';
    if (c == 2) return 'T';
    if (c == 3) return 'G';
}

struct Node {
    vector<int> go;

    bool isTerminal;

    Node() {
        go.assign(4, -1);
        isTerminal = false;
    }
};

vector<Node> t;

void addString(string &s) {
    int v = 0;
    for (auto cc : s) {
        int c = f(cc);
        if (t[v].go[c] == -1) {
            t[v].go[c] = t.size();
            cout << v << ' ' << t.size() << ' ' << cc << '\n';
            t.push_back(Node());
        }
        v = t[v].go[c];
    }
    t[v].isTerminal = true;
}

int source() {
    t.push_back(Node());
    string tmp;
    while (cin >> tmp) {
        addString(tmp);
    }

    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    for (int i = 0; i < t; ++i) {
        source();
    }
}