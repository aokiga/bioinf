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

vector<vector<int>> s;

int n, m;

vector<vector<ll>> g;

vector<pair<par, ll>> ans;

vector<vector<vector<ll>>> d;

const ll INF = 1e9;

string mem = "ACDEFGHIKLMNPQRSTVWY";
//string mem = "ACTG";

vector<int> string_to_dna(string &s) {
    vector<int> res;
    res.resize(s.size());
    for (int i = 0; i < s.size(); ++i) {
        char re = s[i];
        for (int j = 0; j < mem.size(); ++j) {
            if (re == mem[j]) {
                res[i] = j;
            }
        }
    }
    return res;
}
/*
   A  C  D  E  F  G  H  I  K  L  M  N  P  Q  R  S  T  V  W  Y
A  4  0 -2 -1 -2  0 -2 -1 -1 -1 -1 -2 -1 -1 -1  1  0  0 -3 -2
C  0  9 -3 -4 -2 -3 -3 -1 -3 -1 -1 -3 -3 -3 -3 -1 -1 -1 -2 -2
D -2 -3  6  2 -3 -1 -1 -3 -1 -4 -3  1 -1  0 -2  0 -1 -3 -4 -3
E -1 -4  2  5 -3 -2  0 -3  1 -3 -2  0 -1  2  0  0 -1 -2 -3 -2
F -2 -2 -3 -3  6 -3 -1  0 -3  0  0 -3 -4 -3 -3 -2 -2 -1  1  3
G  0 -3 -1 -2 -3  6 -2 -4 -2 -4 -3  0 -2 -2 -2  0 -2 -3 -2 -3
H -2 -3 -1  0 -1 -2  8 -3 -1 -3 -2  1 -2  0  0 -1 -2 -3 -2  2
I -1 -1 -3 -3  0 -4 -3  4 -3  2  1 -3 -3 -3 -3 -2 -1  3 -3 -1
K -1 -3 -1  1 -3 -2 -1 -3  5 -2 -1  0 -1  1  2  0 -1 -2 -3 -2
L -1 -1 -4 -3  0 -4 -3  2 -2  4  2 -3 -3 -2 -2 -2 -1  1 -2 -1
M -1 -1 -3 -2  0 -3 -2  1 -1  2  5 -2 -2  0 -1 -1 -1  1 -1 -1
N -2 -3  1  0 -3  0  1 -3  0 -3 -2  6 -2  0  0  1  0 -3 -4 -2
P -1 -3 -1 -1 -4 -2 -2 -3 -1 -3 -2 -2  7 -1 -2 -1 -1 -2 -4 -3
Q -1 -3  0  2 -3 -2  0 -3  1 -2  0  0 -1  5  1  0 -1 -2 -2 -1
R -1 -3 -2  0 -3 -2  0 -3  2 -2 -1  0 -2  1  5 -1 -1 -3 -3 -2
S  1 -1  0  0 -2  0 -1 -2  0 -2 -1  1 -1  0 -1  4  1 -2 -3 -2
T  0 -1 -1 -1 -2 -2 -2 -1 -1 -1 -1  0 -1 -1 -1  1  5  0 -2 -2
V  0 -1 -3 -2 -1 -3 -3  3 -2  1  1 -3 -2 -2 -3 -2  0  4 -3 -1
W -3 -2 -4 -3  1 -2 -2 -3 -3 -2 -1 -4 -4 -2 -3 -3 -2 -3 11  2
Y -2 -2 -3 -2  3 -3  2 -1 -2 -1 -1 -2 -3 -1 -2 -2 -2 -1  2  7
 */

vector<vector<ll>> blosum= {
        {4,  0,  -2, -1, -2, 0,  -2, -1, -1, -1, -1, -2, -1, -1, -1, 1,  0,  0,  -3, -2},
        {0,  9,  -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2},
        {-2, -3, 6,  2,  -3, -1, -1, -3, -1, -4, -3, 1,  -1, 0,  -2, 0,  -1, -3, -4, -3},
        {-1, -4, 2,  5,  -3, -2, 0,  -3, 1,  -3, -2, 0,  -1, 2,  0,  0,  -1, -2, -3, -2},
        {-2, -2, -3, -3, 6,  -3, -1, 0,  -3, 0,  0,  -3, -4, -3, -3, -2, -2, -1, 1,  3},
        {0,  -3, -1, -2, -3, 6,  -2, -4, -2, -4, -3, 0,  -2, -2, -2, 0,  -2, -3, -2, -3},
        {-2, -3, -1, 0,  -1, -2, 8,  -3, -1, -3, -2, 1,  -2, 0,  0,  -1, -2, -3, -2, 2},
        {-1, -1, -3, -3, 0,  -4, -3, 4,  -3, 2,  1,  -3, -3, -3, -3, -2, -1, 3,  -3, -1},
        {-1, -3, -1, 1,  -3, -2, -1, -3, 5,  -2, -1, 0,  -1, 1,  2,  0,  -1, -2, -3, -2},
        {-1, -1, -4, -3, 0,  -4, -3, 2,  -2, 4,  2,  -3, -3, -2, -2, -2, -1, 1,  -2, -1},
        {-1, -1, -3, -2, 0,  -3, -2, 1,  -1, 2,  5,  -2, -2, 0,  -1, -1, -1, 1,  -1, -1},
        {-2, -3, 1,  0,  -3, 0,  1,  -3, 0,  -3, -2, 6,  -2, 0,  0,  1,  0,  -3, -4, -2},
        {-1, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2, 7,  -1, -2, -1, -1, -2, -4, -3},
        {-1, -3, 0,  2,  -3, -2, 0,  -3, 1,  -2, 0,  0,  -1, 5,  1,  0,  -1, -2, -2, -1},
        {-1, -3, -2, 0,  -3, -2, 0,  -3, 2,  -2, -1, 0,  -2, 1,  5,  -1, -1, -3, -3, -2},
        {1,  -1, 0,  0,  -2, 0,  -1, -2, 0,  -2, -1, 1,  -1, 0,  -1, 4,  1,  -2, -3, -2},
        {0,  -1, -1, -1, -2, -2, -2, -1, -1, -1, -1, 0,  -1, -1, -1, 1,  5,  0,  -2, -2},
        {0,  -1, -3, -2, -1, -3, -3, 3,  -2, 1,  1,  -3, -2, -2, -3, -2, 0,  4,  -3, -1},
        {-3, -2, -4, -3, 1,  -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11, 2},
        {-2, -2, -3, -2, 3,  -3, 2,  -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1, 2,  7}
};

string dna_to_string(vector<int> &s) {
    string res;
    res.resize(s.size());
    for (int i = 0; i < s.size(); ++i) {
        int pos = s[i];
        cerr << pos << ' ' << mem[pos] << '\n';
        res[i] = mem[pos];

    }
    return res;
}

void dfs(int v, int prev = -1) {
    //cerr << v << '\n';
    if (!s[v].empty()) {
        for (int i = 0; i < m; ++i) {
            d[v][i][s[v][i]] = 0;
        }
    }
    if (g[v].size()) {
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < mem.size(); ++k) {
                d[v][i][k] = 0;
            }
        }
    }
    for (auto to : g[v]) {
        if (to == prev) continue;
        dfs(to, v);
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < mem.size(); ++k) {
                ll kk = -INF;
                for (int j = 0; j < mem.size(); ++j) {
                    //int cost = (k == j ? 0 : 1);
                    int cost = blosum[k][j];
                    kk = max(kk, d[to][i][j] + cost);
                }
                d[v][i][k] += kk;
            }
        }
    }
    /*
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < 4; ++k) {
            std::cerr << d[v][i][k] << ' ';
        }
        cerr << '\n';
    }
     */
}

int source() {
    cin >> n;
    s.resize(n * 2);
    g.resize(n * 2);
    string tmp;
    int cnt = 0;
    int root = n;
    while (cin >> tmp) {
        int ind = 0;
        string num = "", num2 = "";
        for (ind = 0; ind < tmp.size(); ind++) {
            num.push_back(tmp[ind]);
            if (tmp[ind] == '-') break;
        }
        ind++;
        for (ind = ind + 1; ind < tmp.size(); ind++) {
            num2.push_back(tmp[ind]);
        }
        if ('0' <= num[0] && num[0] <= '9') {
            int nn = std::stoi( num );
            root = max(root, nn);
            if ('0' <= num2[0] && num2[0] <= '9') {
                int nn2 = std::stoi( num2 );
                g[nn].push_back(nn2);
                g[nn2].push_back(nn);
            } else {
                g[nn].push_back(cnt);
                s[cnt] = string_to_dna(num2);

                cnt++;
            }
        }
    }
    m = s[0].size();

    d.assign(2 * n, vector<vector<ll>>(m, vector<ll>(mem.size(), -INF)));
    dfs(root);

    cerr << m << '\n';

    vector<int> best(m, 0);

    ll sum = 0;

    s[root].resize(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < mem.size(); ++j) {
            if (d[root][i][j] > d[root][i][best[i]]) {
                best[i] = j;
            }
        }
        sum += d[root][i][best[i]];
        s[root][i] = best[i];
    }

    cout << sum << '\n';
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