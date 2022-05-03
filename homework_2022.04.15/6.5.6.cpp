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

void print(vector<ll> &a) {
    cout << "";
    for (int i = 0; i < a.size(); ++i) {
        if (i) cout << " ";
        if (a[i] > 0) cout << "+";
        cout << a[i];
    }
    cout << "\n";
}

int source() {
    vector<ll> a;
    ll x;
    a.push_back(0);
    while (cin >> x) {
        a.push_back(x);
    }
    int n = a.size() - 1;
    a.push_back(n + 1);
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (a[i + 1] - a[i] != 1) ans++;
    }
    cout << ans;
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