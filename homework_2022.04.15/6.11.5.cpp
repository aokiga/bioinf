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

ll P = 253;
ll MOD1 = ll(1e9) + 7;
ll MOD2 = ll(1e9) + 19;

vector<par> p;

par getH(vector<par> &h1, ll b1, ll k) {
    ll hl = (h1[b1 + k].first - (h1[b1].first * p[k].first) % MOD1 + MOD1) % MOD1;
    ll hr = (h1[b1 + k].second - (h1[b1].second * p[k].second) % MOD2 + MOD2) % MOD2;
    return par(hl, hr);
}

int source() {
    ll k;
    cin >> k;
    string s, t;
    cin >> s >> t;
    ll n = s.size();
    ll m = t.size();

    string rt = t;
    reverse(all(rt));
    for (int i = 0; i < m; ++i) {
        if (rt[i] == 'A') {
            rt[i] = 'T';
            continue;
        }
        if (rt[i] == 'T') {
            rt[i] = 'A';
            continue;
        }
        if (rt[i] == 'C') {
            rt[i] = 'G';
            continue;
        }
        if (rt[i] == 'G') {
            rt[i] = 'C';
            continue;
        }
    }

    p.assign(max(n, m) + 1, par(1, 1));
    for (int i = 1; i < p.size(); ++i) {
        p[i].first = (p[i - 1].first * P) % MOD1;
        p[i].second = (p[i - 1].second * P) % MOD2;
    }
    vector<par> hs(n + 1, par(0, 0)), ht(m + 1, par(0, 0)), hrt(m + 1, par(0, 0));
    for (int i = 1; i <= n; ++i) {
        hs[i].first = (hs[i - 1].first * P + s[i - 1] - '0') % MOD1;
        hs[i].second = (hs[i - 1].second * P + s[i - 1] - '0') % MOD2;
    }
    for (int i = 1; i <= m; ++i) {
        ht[i].first = (ht[i - 1].first * P + t[i - 1] - '0') % MOD1;
        ht[i].second = (ht[i - 1].second * P + t[i - 1] - '0') % MOD2;
    }
    for (int i = 1; i <= m; ++i) {
        hrt[i].first = (hrt[i - 1].first * P + rt[i - 1] - '0') % MOD1;
        hrt[i].second = (hrt[i - 1].second * P + rt[i - 1] - '0') % MOD2;
    }

    set<par> pos;

    map<par, vector<ll>> posT;

    for (int bt = 0; bt + k <= m; ++bt) {
        par hh = getH(ht, bt, k);
        posT[hh].push_back(bt);

        hh = getH(hrt, bt, k);
        posT[hh].push_back(m - (bt + k));
    }

    std::cerr << n << ' ' << m << '\n';
    for (int bs = 0; bs + k <= n; ++bs) {
        par hh = getH(hs, bs, k);
        for (auto x : posT[hh]) {
            pos.insert(par(bs, x));
        }
    }
    for (auto x : pos) {
        cout << "(" << x.first << ", " << x.second << ")\n";
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