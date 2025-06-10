#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e6 + 1;

int       t[kMaxN], n, c;
long long ans;
string    s;

int main()
{
    cin >> n >> s;
    int v;
    v    = 3 * n;
    t[v] = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            c += t[++v - 2];
        } else {
            c -= t[v-- - 2], c -= t[v-- - 2], c -= t[v-- - 2];
        }
        ans += c + t[v + 1], t[v]++;
    }
    cout << ans;
    return 0;
}