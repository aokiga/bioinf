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
    map<string, int> a;
    int x = 0;
    ll k;
    cin >> k;
    for (int i = 0; i + k <= s.size(); ++i) {
        string tmp = "";
        for (int j = 0; j < k; ++j) {
            tmp.push_back(s[i + j]);
        }
        a[tmp]++;
        if (a[tmp] > x) {
            x = a[tmp];
        }
    }
    for (auto y: a) {
        if (y.second == x) {
            cout << y.first << ' ';
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    for (int i = 0; i < t; ++i) {
        source();
    }
}