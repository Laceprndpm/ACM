#include <bits/stdc++.h>
#define int     long long
#define in      inline
#define ri      register
#define _123hh2 0
using namespace std;

in int read()
{
    int  x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x  = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

in void write(int x)
{
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 1e6 + 5;
int       awa[maxn], vis[maxn];

void check(int n, int k)
{
    int f = 0, a = 0, b = 0;
    for (int i = 1; i <= n; i++)
        vis[i] = 0;
    for (int i = k + 1; i <= n; i++) {
        if (awa[i] == awa[i - k])
            vis[i] = 1;
        else
            break;
    }
    for (int i = n - k; i >= 1; i--) {
        // cout<<awa[i]<<" "<<awa[i+k]<<"!!!"<<endl;
        if (awa[i] == awa[i + k]) {
            a = i - 1;
            b = n - a;
            if (vis[i] == 1) f++;
        } else
            break;
    }
    if (n == 2 * k) {
        cout << "! " << k << " " << k << endl;
        cout.flush();
        return;
    }
    if (!f)
        cout << "! " << a << " " << b << endl;
    else
        cout << "! -1" << endl;
    cout.flush();
}

int judge(int n, int k, int wz, int mid)
{
    cout << "? " << k * (mid - 1) + wz << endl;
    cout.flush();
    return (read() == awa[wz]);
}

void deal(int n, int k)
{
    for (int i = 1; i <= k; i++) {
        cout << "? " << i << endl;
        cout.flush();
        awa[i] = read();
    }
    for (int i = n; i >= n - k + 1; i--) {
        cout << "? " << i << endl;
        cout.flush();
        awa[i] = read();
    }
    int wz = 0;
    for (int i = 1; i <= n; i++) {
        if (awa[i] != awa[n - k + i]) {
            wz = i;
            break;
        }
    }
    int l = 1, r = n / k, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (judge(n, k, wz, mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    ans++;
    int pos = k * (ans - 1) + wz - 1;
    cout << pos << endl;
    if (pos <= k) {
        cout << "! " << k << " " << n - k << endl;
        cout.flush();
        return;
    }
    cout << "? " << pos << endl;
    cout.flush();
    int now = read();
    int q   = n - k + wz - 1;
    if (wz == 1) q += k;
    if (awa[q] == now) {
        cout << -1 << endl;
        cout.flush();
    } else {
        cout << "! " << pos - 1 << " " << n - pos + 1 << endl;
        cout.flush();
    }
}

signed main()
{
    int t = read();
    while (t-- > 0) {
        int n = read(), k = read();
        if (n == 2 * k) {
            cout << "! " << k << " " << k << endl;
            cout.flush();
            continue;
        }
        // if(n<=250)
        // {
        //     for(int i=1;i<=n;i++)
        //     {
        //         cout<<"? "<<i<<endl;
        //         cout.flush();
        //         awa[i]=read();
        //     }
        //     check(n,k);
        // }
        // else
        {
            deal(n, k);
        }
    }
    return _123hh2;
}

/*
6
5 2
1
2
2
1
2
18 4
2
4
3
1
2
4
3
1
2
1
3
2
4
1
3
2
4
1
3 1
1
1
1
10 4
1
2
3
4
5
1
2
3
4
5
9 3
1
2
3
1
2
3
1
3
2
12 4
1
3
2
4
1
3
4
2
1
3
4
2
*/