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

vector<string> s, ss;

int n, m;

vector<set<ll>> g;

vector<pair<par, ll>> ans, sans;

vector<vector<vector<ll>>> d;

const ll INF = 1e9;

string string_to_dna(string &s) {
    string res = s;
    for (char &re : res) {
        if (re == 'A') re = '0';
        if (re == 'C') re = '1';
        if (re == 'G') re = '2';
        if (re == 'T') re = '3';
    }
    return res;
}

string dna_to_string(string &s) {
    string res = s;
    for (char & re : res) {
        if (re == '0') re = 'A';
        if (re == '1') re = 'C';
        if (re == '2') re = 'G';
        if (re == '3') re = 'T';
    }
    return res;
}

void dfs(int v, int prev = -1) {
    //cerr << v << '\n';
    if (!s[v].empty()) {
        for (int i = 0; i < m; ++i) {
            d[v][i][s[v][i] - '0'] = 0;
        }
    }
    if (g[v].size()) {
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < 4; ++k) {
                d[v][i][k] = 0;
            }
        }
    }
    for (auto to : g[v]) {
        if (to == prev) continue;
        dfs(to, v);
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < 4; ++k) {
                ll kk = INF;
                for (int j = 0; j < 4; ++j) {
                    int cost = (k == j ? 0 : 1);
                    kk = min(kk, d[to][i][j] + cost);
                }
                d[v][i][k] += kk;
            }
        }
    }
    /*
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < 4; ++k) {
            std::cerr << d[v][i][k] << ' ';
        }
        cerr << '\n';
    }
     */
}

void dfs1(int v, vector<int> bestv, int prev = -1) {
    for (auto to : g[v]) {
        if (to == prev) continue;
        s[to].resize(m);
        ll sum = 0;
        vector<int> bestto(m, 0);
        for (int i = 0; i < m; ++i) {
            int kek = bestv[i];
            int cts = (kek == 0 ? 0 : 1);
            for (int j = 1; j < 4; ++j) {
                int cost = (kek == j ? 0 : 1);
                if (d[to][i][j] + cost < d[to][i][bestto[i]] + cts) {
                    bestto[i] = j;
                    cts = cost;
                }
            }
            sum += (bestto[i] != kek ? 1 : 0);
            //std::cerr << sum << '\n';
            s[to][i] = bestto[i] + '0';
        }
        ans.push_back(make_pair(par(v, to), sum));
        dfs1(to, bestto, v);
    }
}

void dfs2(int v, vector<par> &lst, vector<set<ll>> &gg, int prev = -1, int depth = 0) {
    if (depth >= 1) return;
    for (auto to : gg[v]) {
        if (prev == to) continue;
        lst.push_back(par(v, to));
        dfs2(to, lst, gg, v, depth + 1);
    }
}

int source() {
    cin >> n;
    s.assign(n * 2, "");
    g.resize(n * 2);
    string tmp;
    int cnt = 0;
    int root = n;
    vector<string> leafs(n);
    while (cin >> tmp) {
        int ind = 0;
        string num = "", num2 = "";
        for (ind = 0; ind < tmp.size(); ind++) {
            if (tmp[ind] == '-') break;
            num.push_back(tmp[ind]);
        }
        ind++;
        for (ind = ind + 1; ind < tmp.size(); ind++) {
            num2.push_back(tmp[ind]);
        }
        if ('0' <= num[0] && num[0] <= '9') {
            int nn = std::stoi( num );
            //std::cerr << tmp << '\n';
            root = max(root, nn);
            if ('0' <= num2[0] && num2[0] <= '9') {
                int nn2 = std::stoi( num2 );
                g[nn].insert(nn2);
                g[nn2].insert(nn);
            } else {
                g[nn].insert(cnt);
                s[cnt] = string_to_dna(num2);
                leafs[cnt] = string_to_dna(num2);
                cnt++;
            }
        }
    }
    m = s[0].size();

    d.assign(2 * n, vector<vector<ll>>(m, vector<ll>(4, INF)));
    dfs(root);

    vector<int> best(m, 0);

    ll score = 0;

    s[root].resize(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < 4; ++j) {
            if (d[root][i][j] < d[root][i][best[i]]) {
                best[i] = j;
            }
        }
        score += d[root][i][best[i]];
        s[root][i] = char(best[i] + '0');
    }

    dfs1(root, best);

    vector<set<ll>> g1;

    ll prevScore = INF;

    vector<set<ll>> g2 = g;

    cerr << "GRAPH\n";
    for (int v1 = 0; v1 < 2 * n; ++v1) {
        for (auto to1 : g[v1]) {
            cerr << v1 << ' ' << to1 << '\n';
        }
    }



    while (score < prevScore) {
        prevScore = score;

        g1 = g2;

        for (int v = n; v < 2 * n; ++v) {
            for (auto to : g1[v]) {
                if (to < n) continue;

                vector<par> gl, gr;
                dfs2(v, gl, g1, to);
                dfs2(to, gr, g1, v);
                if (gl.empty() || gr.empty()) continue;
                cerr << "MEM\n";
                for (auto e1 : gl) {
                    cerr << e1.second << ' ';
                }
                cerr << "\n";
                for (auto e1 : gr) {
                    cerr << e1.second << ' ';
                }
                cerr << "\n";


                for (auto e1 : gl) {

                    for (auto e2: gr) {
                        g = g1;


                        g[e1.first].erase(e1.second);
                        g[e1.second].erase(e1.first);

                        g[e2.first].erase(e2.second);
                        g[e2.second].erase(e2.first);

                        g[e1.first].insert(e2.second);
                        if (e2.second >= n) g[e2.second].insert(e1.first);
                        g[e2.first].insert(e1.second);
                        if (e1.second >= n) g[e1.second].insert(e2.first);
                        cerr << "CHANGED\n";
                        cerr << e1.first << ' ' << e1.second << '\n';
                        cerr << e2.first << ' ' << e2.second << '\n';
                        cerr << "GRAPH\n";
                        for (int v1 = 0; v1 < 2 * n; ++v1) {
                            for (auto to1 : g[v1]) {
                                cerr << v1 << ' ' << to1 << '\n';
                            }
                        }

                        ans.clear();
                        d.clear();

                        d.assign(2 * n, vector<vector<ll>>(m, vector<ll>(4, INF)));
                        for (int i = n; i < 2 * n; ++i) {
                            s[i] = "";
                        }
                        for (int i = 0; i < n; ++i) s[i] = leafs[i];
                        dfs(root);

                        vector<int> best(m, 0);

                        int curscore = 0;

                        s[root].resize(m);
                        for (int i = 0; i < m; ++i) {
                            for (int j = 1; j < 4; ++j) {
                                if (d[root][i][j] < d[root][i][best[i]]) {
                                    best[i] = j;
                                }
                            }
                            curscore += d[root][i][best[i]];
                            s[root][i] = char(best[i] + '0');
                        }

                        dfs1(root, best);

                        if (curscore <= score) {
                            score = curscore;
                            g2 = g;
                            sans = ans;
                            ss = s;
                        }
                    }
                }
            }
        }
        if (score < prevScore) {
            cout << score << '\n';
            for (auto v: sans) {
                cout << dna_to_string(ss[v.first.first]) << "->" << dna_to_string(ss[v.first.second]) << ":" << v.second
                     << '\n';
                cout << dna_to_string(ss[v.first.second]) << "->" << dna_to_string(ss[v.first.first]) << ":" << v.second
                     << '\n';
            }
            cout << "\n";
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