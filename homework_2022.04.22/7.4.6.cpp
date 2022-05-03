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

int findLimbLength(vector<vector<int>> &a, int J, int n) {
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        if (i == J) continue;
        for (int k = 0; k < n; ++k) {
            if (k == J || k == i) continue;
            int curans = a[i][J] + a[J][k] - a[i][k];
            if (ans == -1 || ans > curans) {
                cerr << "MEMEME" << i << ' ' << J << ' ' << k << '\n';
                ans = curans;
            }
        }
    }
    return ans / 2;
}

bool dfs(int v, map<int, bool> &used, int x, int &ans, par &edgeInfo,int &depth1, map<int, map<int, int>> &g, int end, int depth = 0) {
    used[v] = true;
    if (v == end) {
        if (depth == x) {
            ans = v;
            depth1 = depth;
        }
        return true;
    }
    for (auto to : g[v]) {
        if (used.count(to.first) && used[to.first]) continue;
        if (dfs(to.first, used, x, ans, edgeInfo, depth1, g, end, depth + to.second)) {
            if (depth == x) {
                ans = v;
                depth1 = depth;
            } else {
                if (depth < x && depth + to.second > x) {
                    ans = v;
                    edgeInfo = to;
                    depth1 = depth;
                }
            }
            return true;
        }
    }
    return false;
}
int cnt;

void AdditivePhylogeny(vector<vector<int>> &a, int n, map<int, map<int, int>> &ans) {
    if (n == 2) {
        ans[0][1] = a[0][1];
        ans[1][0] = a[0][1];;
        return;
    }
    ll limblen = findLimbLength(a, n - 1, n);
    std::cerr << n << "       " << limblen << '\n';

    for (int i = 0; i < n - 1; ++i) {
        a[n - 1][i] -= limblen;
        a[i][n - 1] = a[n - 1][i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cerr << a[i][j] << ' ';
        }
        cerr << '\n';
    }

    par mem = par(-1, -1);
    ll x;
    bool flag = false;
    for (int i = 0; i < n - 1; ++i) {
        if (flag) break;
        for (int j = 0; j < n - 1; ++j) {
            if (i == j) continue;
            if (a[i][j] == a[i][n - 1] + a[n - 1][j]) {
                mem = par(i, j);
                x = a[i][n - 1];
                flag = true;
                break;
            }
        }
    }
    AdditivePhylogeny(a, n - 1, ans);

    int anss = -1;
    par edgeInfo = par(-1, -1);
    map<int, bool> used;
    std::cerr << "sdsd " << mem.first << ' ' << mem.second << ' '  << x << '\n';
    int depth1;
    dfs(mem.first, used, x, anss, edgeInfo, depth1, ans, mem.second);
    std::cerr << "qweqwe " << anss << ' ' << edgeInfo.first << ' ' << edgeInfo.second << '\n';
    if (edgeInfo != par(-1, -1)) {
        ll len = edgeInfo.second;
        ans[edgeInfo.first].erase(anss);
        ans[anss].erase(edgeInfo.first);
        ll ans1 = cnt++;
        ans[anss][ans1] = x - depth1;
        ans[ans1][anss] = x - depth1;
        ans[edgeInfo.first][ans1] = len + depth1 - x;
        ans[ans1][edgeInfo.first] = len + depth1 - x;
        anss = ans1;
    }
    ans[n - 1][anss] = limblen;
    ans[anss][n - 1] = limblen;

    for (auto &i : ans) {
        for (auto to : i.second) {
            cerr << i.first << "->" << to.first << ":" << to.second << '\n';
        }
    }
}

int source() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    cnt = n;
    map<int, map<int, int>> g;
    AdditivePhylogeny(a, n, g);
    for (auto &i : g) {
        for (auto to : i.second) {
            cout << i.first << "->" << to.first << ":" << to.second << '\n';
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