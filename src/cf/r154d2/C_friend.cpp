#include <bits/stdc++.h>
using namespace std;
int    t;
string s;

void solve()
{
    cin >> s;
    int n  = s.size();
    int bf = 1e9, now = 0, minn = 1e9;
    int flag = 1;
    int f1   = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '+') {
            now++;
            f1++;
        }
        if (s[i] == '-') {
            now--;
            minn = min(minn, now);
            f1--;
            f1 = max(0, f1);
        }

        if (s[i] == '1') {
            if (flag == 0) {
                if (minn >= bf) {
                    cout << "NO\n";
                    return;
                }
            }
            bf   = 1e9;
            minn = 1e9;
            flag = 1;
            f1   = 0;
        }

        if (s[i] == '0') {
            if (flag == 1) {
                if (f1 == 0) {
                    cout << "NO\n";
                    return;
                }
            }
            if (now <= 1) {
                cout << "NO\n";
                return;
            }
            bf   = min(now, bf);
            minn = 1e9;
            flag = 0;
            f1   = 0;
        }
    }

    cout << "YES\n";
}

int main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    cin >> t;
    while (t--)
        solve();
    return 0;
}