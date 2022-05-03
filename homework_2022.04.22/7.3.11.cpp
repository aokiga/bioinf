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

int source() {
    int n;
    cin >> n;
    int J;
    cin >> J;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        if (i == J) continue;
        for (int k = 0; k < n; ++k) {
            if (k == J || k == i) continue;
            int curans = a[i][J] + a[J][k] - a[i][k];
            if (ans == -1 || ans >curans ) {
                ans = curans;
            }
        }
    }
    cout << ans / 2;
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
