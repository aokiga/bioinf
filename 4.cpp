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
    int cnt = 0;
    string s, t;
    cin >> t >> s;
    int p;
    cin >> p;
    vector<int> ans;
    for (int i = 0; i <= s.size() - t.size(); ++i) {
        string tmp = "";
        for (int j = 0; j < t.size(); ++j) {
            tmp.push_back(s[j + i]);
        }
        int k = 0;
        int dk = 0;
        for (int j = 0; j < t.size(); ++j) {
            if (tmp[j] != t[j]) dk++;
        }
        if (dk <= p) {
            ans.push_back(i);
        }
    }
    for (auto x : ans) {
        cout << x << ' ';
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