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
    while (q--) {
        string t;
        int    a;
        cin >> t >> a;
        int         len = t.size();
        vector<int> arr(len, 0);
        for (int i = 0; i <= len - 1; i++) {
            if (t[i] == s[i + a - 1]) {
                arr[i] = 1;
            }
        }
        ll sum = 0;
        ll res = 0;
        for (int i = 0; i <= len - 1; i++) {
            if (arr[i] == 1) {
                res++;
            } else {
                sum += (res + 1) * res / 2;
                res = 0;
            }
        }
        sum += (res + 1) * res / 2;
        cout << sum << endl;
    }
    return 0;
}