#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int init(string& pattern, vector<int>& nextarr)
{
    nextarr.assign(pattern.size(), 0);
    int m = pattern.size();
    int i, j;
    for (i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = nextarr[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        nextarr[i] = j;
    }
    return j;
}

template <class T, class U>
class Ping {
public:
    T&  a;
    T&  b;
    int lengthA;

    Ping(T& a_, T& b_, int len) : a(a_), b(b_), lengthA(len) {}

    U& operator[](int idx)
    {
        if (idx >= lengthA) {
            return b[idx - lengthA];
        } else {
            return a[idx];
        }
    }
};

void go(string& pre, string& patt, int initial, int j, vector<int>& nextcrr, vector<int>& nextarr)
{
    int                    m = patt.size();
    Ping<string, char>     pattern(pre, patt, pre.size());
    Ping<vector<int>, int> nextbrr(nextarr, nextcrr, pre.size());
    for (int i = initial; i < m + initial; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = nextbrr[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        nextbrr[i] = j;
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    string s;
    cin >> s;
    vector<int> nextarr;
    int         j = init(s, nextarr);
    int         t;
    cin >> t;
    map<string, vector<int>> mpV;
    map<string, int>         mpJ;
    while (t--) {
        string      cur;
        vector<int> nextcrr;
        cin >> cur;
        int nowj = j;
        for (int i = 1; i <= cur.size(); i++) {
            if (!mpJ.count(string(cur.begin(), cur.begin() + i))) {
                nextcrr = mpV[string(cur.begin(), cur.begin() + i)];
                nowj    = mpJ[string(cur.begin(), cur.begin() + i)];
            }
        }
        nextcrr.resize(cur.size());
        go(s, cur, s.length(), nowj, nextcrr, nextarr);
        for (int i = s.length(); i < s.length() + cur.length(); i++) {
            cout << nextarr[i] << ' ';
        }
    }
}
