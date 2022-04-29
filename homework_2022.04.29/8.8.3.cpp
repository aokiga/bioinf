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

void addPoint(vector<Point> &pos, vector<Point> &center, int i, int m) {
    int n = center.size();
    center.push_back(Point(m));
    for (int j = 0; j < m; ++j) {
        center[n][j] = pos[i][j];
    }
}

ld dist(Point &pt1, Point &pt2) {
    ld sum = 0;
    for (int i = 0; i < pt1.size(); ++i) {
        ld dx = pt1[i] - pt2[i];
        sum += dx * dx;
    }
    return sqrt(sum);
}

void splitToClusters(vector<Point> &pos, vector<Point> &centers, vector<int> &groups) {
    int k = centers.size();
    int n = pos.size();
    for (int i = 0; i < n; ++i) {
        ld mindist = -1;
        ll closest = -1;
        for (int j = 0; j < k; ++j) {
            ld curdist = dist(pos[i], centers[j]);
            if (closest == -1 || mindist > curdist) {
                closest = j;
                mindist = curdist;
            }
        }
        groups[i] = closest;
    }
}

Point countGravityCenter(vector<Point> &points) {
    int m = points[0].size();
    int n = points.size();
    Point res(m);
    for (auto &point : points) {
        for (int i = 0; i < m; ++i) {
            res[i] += point[i];
        }
    }
    for (int i = 0; i < m; ++i) {
        res[i] /= n;
    }
    return res;
}

void choose_centers(vector<Point> &pos, vector<Point> &centers, vector<int> &groups) {
    ll k = centers.size();
    ll n = pos.size();
    vector<vector<Point>> kk(k);
    for (int i = 0; i < n; ++i) {
        kk[groups[i]].push_back(pos[i]);
    }
    for (int i = 0; i < k; ++i) {
        centers[i] = countGravityCenter(kk[i]);
    }
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
    vector<Point> centers(k);
    for (int i = 0; i < k; ++i) {
        centers[i] = pos[i];
    }

    vector<int> groups(n, 0);
    splitToClusters(pos, centers, groups);

    vector<int> prev_groups = groups;

    while (true) {
        choose_centers(pos, centers, groups);
        splitToClusters(pos, centers, groups);
        bool flag = true;
        //for (int i = 0; i < k; ++i) {
        //    cerr << groups[i] << ' ';
        //}
        //cerr << '\n';
        for (int i = 0; i < n; ++i) {
            if (prev_groups[i] != groups[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        }
        prev_groups = groups;
    }
    choose_centers(pos, centers, groups);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << fixed << setprecision(3) << centers[i][j] << ' ';
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