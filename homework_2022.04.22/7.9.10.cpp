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

vector<string> s;

int n, m;

vector<vector<ll>> g;

vector<pair<par, ll>> ans;

vector<vector<vector<ll>>> d;

const ll INF = 1e9;

string string_to_dna(string &s) {
    string res = s;
    for (char &re : res) {
        if (re == 'A') re = '0';
        if (re == 'C') re = '1';
        if (re == 'G') re = '2';
        if (re == 'T') re = '3';
    }
    return res;
}

string dna_to_string(string &s) {
    string res = s;
    for (char & re : res) {
        if (re == '0') re = 'A';
        if (re == '1') re = 'C';
        if (re == '2') re = 'G';
        if (re == '3') re = 'T';
    }
    return res;
}

void dfs(int v, int prev = -1) {
    //cerr << v << '\n';
    if (!s[v].empty()) {
        for (int i = 0; i < m; ++i) {
            d[v][i][s[v][i] - '0'] = 0;
        }
    }
    if (g[v].size()) {
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < 4; ++k) {
                d[v][i][k] = 0;
            }
        }
    }
    for (auto to : g[v]) {
        if (to == prev) continue;
        dfs(to, v);
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < 4; ++k) {
                ll kk = INF;
                for (int j = 0; j < 4; ++j) {
                    int cost = (k == j ? 0 : 1);
                    kk = min(kk, d[to][i][j] + cost);
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

void dfs1(int v, vector<int> bestv, int prev = -1) {
    for (auto to : g[v]) {
        if (to == prev) continue;
        s[to].resize(m);
        ll sum = 0;
        vector<int> bestto(m, 0);
        for (int i = 0; i < m; ++i) {
            int kek = bestv[i];
            int cts = (kek == 0 ? 0 : 1);
            for (int j = 1; j < 4; ++j) {
                int cost = (kek == j ? 0 : 1);
                if (d[to][i][j] + cost < d[to][i][bestto[i]] + cts) {
                    bestto[i] = j;
                    cts = cost;
                }
            }
            sum += (bestto[i] != kek ? 1 : 0);
            //std::cerr << sum << '\n';
            s[to][i] = bestto[i] + '0';
        }
        ans.push_back(make_pair(par(v, to), sum));
        dfs1(to, bestto, v);
    }
}

int source() {
    cin >> n;
    s.assign(n * 2, "");
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

    d.assign(2 * n, vector<vector<ll>>(m, vector<ll>(4, INF)));
    dfs(root);

    vector<int> best(m, 0);

    ll sum = 0;

    s[root].resize(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < 4; ++j) {
            if (d[root][i][j] < d[root][i][best[i]]) {
                best[i] = j;
            }
        }
        sum += d[root][i][best[i]];
        s[root][i] = char(best[i] + '0');
    }

    cout << sum << '\n';

    dfs1(root, best);

    for (auto v : ans) {
        cout << dna_to_string(s[v.first.first]) << "->" << dna_to_string(s[v.first.second]) << ":" << v.second << '\n';
        cout << dna_to_string(s[v.first.second]) << "->" << dna_to_string(s[v.first.first]) << ":" << v.second << '\n';
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