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
    vector<ll> a, b;
    ll x;
    while (cin >> x) {
        a.push_back(x);
    }
    ll n = a.size() / 2;
    for (int i = 0; i < n; ++i) {
        b.push_back(a.back());
        a.pop_back();
    }
    reverse(all(b));
    for (int i = 0; i < n; ++i) {
        if (abs(a[i]) != abs(b[i])) {
            int j = i + 1;
            for (; j < n; ++j) {
                if (abs(a[j]) == abs(b[i])) {
                    break;
                }
            }
            if (j == n) --j;
            reverse(a.begin() + i, a.begin() + j + 1);
            for (int k = i; k <= j; ++k) a[k] *= -1;
            print(a);
        }
        if (a[i] * b[i] < 0) {
            a[i] *= -1;
            print(a);
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