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
typedef pair<ll, ll> par;

#define all(x) (x).begin(), (x).end()

int source() {
    string s;
    cin >> s;
    int k, l, t;
    cin >>  k >> l >> t;
    vector<string> p;
    vector<string> ans;
    int n = s.size();
    for (int i = 0; i <= n - l; ++i) {
        map<string, int> x;
        for (int j = 0; j <= l - k; ++j) {
            string tmp = "";
            for (int tt = 0; tt < k; ++tt) {
                tmp.push_back(s[i + j + tt]);
            }
            x[tmp]++;
        }
        for (auto &y : x) {
            if (y.second >= t) {
                ans.push_back(y.first);
            }
        }
    }
    set<string> ss( ans.begin(), ans.end() );
    ans.assign( ss.begin(), ss.end() );
    for (auto &x : ans) {
        cout << x << ' ';
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