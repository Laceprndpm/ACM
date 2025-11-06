#include <bits/stdc++.h>
using namespace std;
int b[99][99];

int main()
{
    int n;
    cin >> n;
    for (int i = 0, v; i < n; i++) {
        b[i][i]++, cin >> v;
        for (int j = 0; j < n; j++) b[i][j] += v, b[i][j] %= 998244353, cout << b[i][j] << " \n"[j == n];
    }
}