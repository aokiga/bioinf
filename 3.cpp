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
    int mm = 0;
    vector<int> ans;
    ans.push_back(0);
    int n = s.size();
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'G') {
            cur++;
        }
        if (s[i] == 'C') {
            cur--;
        }
        if (mm == cur) {
            ans.push_back(i);
            continue;
        }
        if (mm > cur) {
            ans.clear();
            mm = cur;
            ans.push_back(i);
        }
    }
    for (auto x : ans) {
        cout << x + 1 << '\n';
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