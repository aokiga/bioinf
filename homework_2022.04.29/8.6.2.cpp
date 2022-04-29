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

void addPoint(vector<vector<ld>> &pos, vector<vector<ld>> &center, int i, int m) {
    int n = center.size();
    center.push_back(vector<ld>(m));
    for (int j = 0; j < m; ++j) {
        center[n][j] = pos[i][j];
    }
}

ld dist(vector<ld> &pt1, vector<ld> &pt2) {
    ld sum = 0;
    for (int i = 0; i < pt1.size(); ++i) {
        ld dx = pt1[i] - pt2[i];
        sum += dx * dx;
    }
    return sqrt(sum);
}

int source() {
    ll k, m;
    cin >> k >> m;
    ll n = 0;
    vector<vector<ld>> pos;
    ld c;
    while (cin >> c) {
        pos.push_back(vector<ld>(m));
        pos[n][0] = c;
        for (int i = 1; i < m; ++i) {
            cin >> pos[n][i];
        }
        ++n;
    }
    std::cerr << n << '\n';
    vector<vector<ld>> centers;
    addPoint(pos, centers, 0, m);
    set<ll> inCenters;
    inCenters.insert(0);
    while (centers.size() < k) {
        int pp = -1;
        ld maxdist = 0;
        for (int i = 1; i < n; ++i) {
            if (inCenters.count(i)) continue;
            ld curdist = dist(pos[i], centers[0]);
            for (auto &center : centers) {
                ld d = dist(pos[i], center);
                curdist = min(curdist, d);
            }
            //std::cerr << i << ' ' << curdist << '\n';
            if (pp == -1 || maxdist < curdist) {
                pp = i;
                maxdist = curdist;
            }
        }
        //std::cerr << "ADD " << pp << '\n';
        inCenters.insert(pp);
        addPoint(pos, centers, pp, m);
    }
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << centers[i][j] << ' ';
        }
        cout << '\n';
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