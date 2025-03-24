// #include <bits/stdc++.h>
#include <iostream>
using namespace std;
using ll = long long;

const int N = 2e5;
int       a[N];

int solve()
{
    int n;
    cin >> n;
    int  c = 0;
    bool f = 0;
    int  s, e;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i && a[i] <= a[i - 1]) {
            if (f == 0) {
                s = i - 1;
                f = 1;
            }
            e = i;
            c++;
        }
    }
    if (c == 0) return 0;
    if (c & 1) return (c >> 1) + 1;
    return (c >> 1) + (a[e] < a[s] + e - s);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        cout << solve() << '\n';
}