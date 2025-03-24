#include <cstdio>
#include <stack>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           p;

string p2ten(int x)
{
    string      ans = "";
    stack<char> s;
    while (x) {
        char cur;
        if (x % p <= 9 && x % p >= 0)
            cur = x % p + '0';
        else
            cur = x % p + 'A' - 10;
        s.push(cur);
        x /= p;
    }
    while (!s.empty()) {
        ans = ans + s.top();
        s.pop();
    }
    return ans;
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
    cin >> p;
    for (int i = 1; i < p; i++) {
        for (int j = 1; j <= i; j++) {
            cout << p2ten(i) << '*' << p2ten(j) << '=' << p2ten(i * j) << ' ';
        }
        cout << '\n';
    }
    return 0;
}