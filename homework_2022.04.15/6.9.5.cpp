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

void read(vector<vector<ll>> &a) {
    char c;
    string buff = "";
    while (scanf("%c", &c) == 1) {
        if (c == '\n') break;
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == ')') {
            if (buff.empty()) continue;
            ll x = stoll(buff);
            a[a.size() - 1].push_back(x);
            buff.clear();
            continue;
        }
        if (c == '(') {
            a.push_back(vector<ll>(0));
            continue;
        }
        buff.push_back(c);
    }
}

vector<ll> genomeToGraph(vector<vector<ll>> &a) {
    ll n = 0;
    vector<vector<ll>> a1;
    for (auto &ai : a) {
        n += ai.size() * 2;
        a1.push_back(vector<ll>(0));
        for (auto x : ai) {
            ll x1 = abs(x) - 1;
            ll a2 = x1 * 2;
            ll b2 = x1 * 2 + 1;
            if (x < 0) swap(a2, b2);
            a1[a1.size() - 1].push_back(a2);
            a1[a1.size() - 1].push_back(b2);
        }
    }
    vector<ll> g(n, -1);
    for (auto &ai : a1) {
        for (int i = 1; i < ai.size(); i += 2) {
            int j = (i + 1) % ai.size();
            g[ai[i]] = ai[j];
            g[ai[j]] = ai[i];
        }
    }
    return g;
}

vector<char> used;
vector<ll> g1, g2;

vector<ll> path;


void dfs(int v, bool flag = false) {
    used[v] = true;
    path.push_back(v);
    int to;
    if (flag) {
        to = g2[v];
    } else {
        to = g1[v];
    }
    if (used[to]) return;
    dfs(to, !flag);
}

void dfs2(int v, bool flag = false) {
    used[v] = true;
    path.push_back(v);
    cerr << v << ' ';
    int to;
    if (flag) {
        to = v ^ 1;
    } else {
        to = g1[v];
    }
    if (used[to]) return;
    dfs2(to, !flag);
}


void printG(int v) {
    int n = g1.size();
    for (int i = 0; i < n; ++i) {
        cerr << i << ' ' << g1[i] << '\n';
    }
    cerr << "\n\n";
    used.assign(n, 0);
    for (int v = 0; v < n; ++v) {
        if (used[v]) continue;
        cout << "(";
        dfs2(v);
        cerr << "\n\n";
        reverse(all(path));
        for (int i = 1; i < path.size(); i += 2) {
            int j = (i + 1) % path.size();
            if (i > 1) cout << " ";
            if (path[j] > path[i]) cout << "+";
            else cout << "-";
            cout << path[i] / 2 + 1;
        }
        cout << ")";
        path.clear();
    }
    cout << "\n";
}

int source() {
    vector<vector<ll>> a, b;
    read(a);
    read(b);
    g1 = genomeToGraph(a);
    g2 = genomeToGraph(b);
    int n = g1.size();
    bool flag = true;
    printG(0);
    while (flag) {
        flag = false;
        used.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            dfs(i);

            int sz = path.size();
            path.clear();
            if (sz != 2) {
                g1[i] = path[3];
                g1[path[3]] = i;
                g1[path[1]] = path[2];
                g1[path[2]] = path[1];
                flag = true;
                break;
            }
        }
        if (flag) {
            printG(0);
        }
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