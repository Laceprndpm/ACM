#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<bool> arr(n + 1, 0);
    vector<bool> brr(n + 1, 0);
    while (q--) {
        int x;
        cin >> x;
        if (x == 1) {
            int l, r;
            cin >> l >> r;
            arr[l - 1] = !arr[l - 1];
            arr[r]     = !arr[r];
        } else {
            brr[0] = arr[0];
            for (int i = 1; i <= n - 1; i++) {
                brr[i] = brr[i - 1] ^ arr[i];
            }
            int l, a, b;
            cin >> l >> a >> b;
            ll sum = 0;
            ll res = 0;
            for (int i = 0; i <= l - 1; i++) {
                if (s[i + a - 1] != s[i + b - 1]) {
                    if (brr[i + a - 1] != brr[i + b - 1]) {
                        res++;
                    } else {
                        sum += (res + 1) * res / 2;
                        res = 0;
                    }
                } else {
                    if (brr[i + a - 1] == brr[i + b - 1]) {
                        res++;
                    } else {
                        sum += (res + 1) * res / 2;
                        res = 0;
                    }
                }
            }
            sum += (res + 1) * res / 2;
            cout << sum << endl;
        }
    }
    return 0;
}