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
    string s;
    cin >> s;
    int k, d;
    cin >> k >> d;
    vector<string> ans;
    int anss = 0;
    for (int y = 0; y <= s.size() - k; ++y) {
        string t = "";
        for (int i  = 0; i < k; ++i) {
            t.push_back(s[i + y]);
        }

        string t1 = t;
        reverse(t1.begin(), t1.end());
        for (int i = 0; i < k; ++i) {
            if (t1[i] == 'A') {
                t1[i] = 'T';
                continue;
            }
            if (t1[i] == 'T') {
                t1[i] = 'A';
                continue;
            }
            if (t1[i] == 'G') {
                t1[i] = 'C';
                continue;
            }
            if (t1[i] == 'C') {
                t1[i] = 'G';
                continue;
            }
        }
        int ans1 = 0;
        int ans2 = 0;
        for (int i = 0; i <= s.size() - t.size(); ++i) {
            string tmp = "";
            for (int j = 0; j < t.size(); ++j) {
                tmp.push_back(s[j + i]);
            }
            int dk = 0;
            for (int j = 0; j < t.size(); ++j) {
                if (tmp[j] != t[j]) dk++;
            }
            if (dk <= d) {
                ans1++;
            }
        }
        for (int i = 0; i <= s.size() - t1.size(); ++i) {
            string tmp = "";
            for (int j = 0; j < t.size(); ++j) {
                tmp.push_back(s[j + i]);
            }
            int dk = 0;
            for (int j = 0; j < t1.size(); ++j) {
                if (tmp[j] != t1[j]) dk++;
            }
            if (dk <= d) {
                ans2++;
            }
        }
        if (ans1 + ans2 == anss) {
            ans.push_back(t);
            ans.push_back(t1);
            continue;
        }
        if (ans1 + ans2 > anss) {
            anss = ans1 + ans2;
            ans.clear();
            ans.push_back(t);
            ans.push_back(t1);
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    for (int i = 0; i < t; ++i) {
        source();
    }
}