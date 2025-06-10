#include <bits/stdc++.h>
using namespace std;
int a, b;
signed main()
{
    cin >> a >> b;
    a %= 10;
    b -= a;
    cout << (b + 10) % 10;
    return 0;
}