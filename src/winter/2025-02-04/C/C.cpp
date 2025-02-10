#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int f(int b, int x)
{
    LL sum;
    do {
        sum = 0;
        while (x > 0) {
            sum += x % b;
            x /= b;
        }
        x = sum;
    } while (sum >= b);
    return sum;
}

bool check(int k, int b)
{
    vector<bool> flag(b, false);

    for (int i = 0; i < b; i++) {
        flag[f(b, i * k)] = true;
    }

    for (int i = 0; i < b; i++) {
        if (!flag[i]) {
            return false;
        }
    }
    return true;
}

signed main(signed argc, char** argv)
{
#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int K, B;
    cin >> K >> B;
    vector<int> k(K + 1);
    vector<int> b(B + 1);
    for (int i = 1; i <= K; i++) {
        cin >> k[i];
    }
    for (int i = 1; i <= B; i++) {
        cin >> b[i];
    }
    LL ans = 0;
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= B; j++) {
            if (check(k[i], b[j]))
                ans++;
        }
    }
    cout << ans << endl;

    // for (int i = 9; i < 10; i++) {
    //     for (int j = 1; j < 20; j++) {
    //         cout << i << ' ' << j << ' ' << (check(i, j) ? 1 : 0) << '\n';
    //     }
    // }
    return 0;
}