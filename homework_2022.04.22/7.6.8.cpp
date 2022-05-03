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

typedef vector<ld> Point;

pair<int, int> findClosestClusters(vector<vector<ld>> &m, set<ll> &clusters) {
    pair<int, int> res = make_pair(-1, -1);
    ld maxdist = -1;
    for (auto &i : clusters) {
        for (auto &j: clusters) {
            if (i == j) continue;
            ld curdist = m[i][j];
            if (res == make_pair(-1, -1) || maxdist > curdist) {
                maxdist = curdist;
                res = make_pair(i, j);
            }
        }
    }
    return res;
}

int source() {
    int n;
    cin >> n;
    vector<vector<ld>> m(n, vector<ld>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }
    ll N = n;
    set<ll> clusters;
    for (int i = 0; i < n; ++i) {
        clusters.insert(i);
    }
    vector<vector<ll>> cc(n);
    for (int i = 0; i < n; ++i) {
        cc[i].push_back(i);
    }
    vector<ld> age(n, 0);
    map<int, map<int, ld>> ans;
    while (clusters.size() > 1) {
        auto closestClusters = findClosestClusters(m, clusters);
        int i = closestClusters.first;
        int j = closestClusters.second;
        clusters.erase(i);
        clusters.erase(j);

        clusters.insert(N);

        ld sum1 = 0;
        for (auto v : cc[i]) {
            for (auto to: cc[j]) {
                sum1 += m[v][to];
            }
        }
        sum1 /= cc[i].size() * cc[j].size();
        age.push_back(sum1);

        ans[N][i] = age[N] - age[i];
        ans[N][j] = age[N] - age[j];
        ans[i][N] = age[N] - age[i];
        ans[j][N] = age[N] - age[j];

        for (int k = 0; k < N; ++k) {
            ld sum = 0;
            for (auto v : cc[i]) {
                for (auto to : cc[k]) {
                    sum += m[v][to];
                }
            }
            for (auto v : cc[j]) {
                for (auto to : cc[k]) {
                    sum += m[v][to];
                }
            }
            sum /= (cc[i].size() + cc[j].size()) * cc[k].size();
            m[k].push_back(sum);
        }

        m.push_back(vector<ld>(N + 1, 0));
        for (int k = 0; k < N; ++k) {
            m[N][k] = m[k][N];
        }

        clusters.insert(N);
        cc.push_back(vector<ll>(cc[i].size() + cc[j].size()));

        for (int k = 0; k < cc[N].size(); ++k) {
            if (k < cc[i].size()) cc[N][k] = cc[i][k];
            else cc[N][k] = cc[j][k - cc[i].size()];
        }
        N++;
    }
    for (auto &v : ans) {
        for (auto &s : v.second) {
            cout << v.first << "->" << s.first << ":" << s.second / 2 << "\n";
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