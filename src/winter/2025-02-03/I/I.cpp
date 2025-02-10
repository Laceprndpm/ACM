#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int countMinutesTo20clock(int hh, int mm)
{
    return (20 - hh) * 60 - mm;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int hh, mm;
    cin >> hh >> mm;
    int H, D, C, N;
    cin >> H >> D >> C >> N;
    double ans;
    if (hh < 20) {
        int    result1 = ((H - 1) / N + 1) * C;
        int    temp    = (H + D * countMinutesTo20clock(hh, mm) - 1) / N + 1;
        double result2 = temp * C * 0.8;
        ans            = min((double)result1, result2);
    } else {
        int temp = (H - 1) / N + 1;
        ans      = temp * C * 0.8;
    }
    printf("%.4lf", ans);
    return 0;
}