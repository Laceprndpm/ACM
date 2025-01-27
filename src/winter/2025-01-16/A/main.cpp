#include <bits/stdc++.h>
using namespace std;
#define int long long
int a, b, c;
signed main()
{
    cin >> a >> b >> c;
    int fen_dan = min(c * 3 / 10, a);
    if (c - fen_dan >= b) // 总伤害大于b
    {
        cout << a << ' ' << 0; // 不分担伤害
    }
    else // 分担
    {
        cout << a - fen_dan << ' ' << b - c + fen_dan;
    }
    return 0;
}