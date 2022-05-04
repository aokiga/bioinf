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

int f(char c) {
    if (c == 'A') return 1;
    if (c == 'C') return 2;
    if (c == 'G') return 3;
    if (c == 'T') return 4;
    if (c == '$') return 0;
}

char f1(int c) {
    if (c == 0) return '$';
    if (c == 1) return 'A';
    if (c == 2) return 'C';
    if (c == 3) return 'G';
    if (c == 4) return 'T';
}

struct Node {
    vector<ll> go;
    vector<par> st;

    bool isTerminal;
    int num;

    Node() {
        go.assign(5, -1);
        st.resize(5);
        isTerminal = false;
    }
};

vector<Node> t;

void addString(string &s, int begin) {
    int v = 0;
    for (int i = begin; i < s.size(); ++i) {
        int c = f(s[i]);
        if (t[v].go[c] == -1) {
            t[v].go[c] = t.size();

            t[v].st[c] = par(i, s.size() - i);
            t.push_back(Node());
            v = t[v].go[c];
            break;
        }
        par tmp = t[v].st[c];
        bool flag = true;
        int len = 0;
        for (; len < tmp.second; ++len) {
            if (s[tmp.first + len] == s[i]) {
                i++;
                continue;
            }
            flag = false;
            break;
        }
        if (!flag) {
            int tmpNodeNum = t.size();
            t.push_back(Node());
            ll c2 = f(s[tmp.first + len]);
            t[tmpNodeNum].st[c2] = par(tmp.first + len, tmp.second - len);
            t[tmpNodeNum].go[c2] = t[v].go[c];
            t[v].go[c] = tmpNodeNum;
            t[v].st[c] = par(tmp.first, len);
        }
        --i;
        v = t[v].go[c];
    }
    t[v].isTerminal = true;
    t[v].num = begin;
}

vector<int> ans;

string text;

void dfs(int v) {
    if (t[v].isTerminal) {
        ans.push_back(t[v].num);
    }
    for (int i = 0; i < 5; ++i) {
        if (t[v].go[i] == -1) continue;
        dfs(t[v].go[i]);
    }
}

int source() {
    cin >> text;
    t.push_back(Node());
    for (int i = 0; i < text.size(); ++i) {
        addString(text, i);
    }
    dfs(0);
    for (auto x : ans) {
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