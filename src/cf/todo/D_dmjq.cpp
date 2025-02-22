#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long

void print()
{
    cout << "hell" << '\n';
}

int www(int x)
{
    return x + 1;
}

int main()
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    print();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i <= n - 1; i++) {
        cin >> arr[i];
    }
    int ans = 0;
    for (int i = 0; i <= n - 1; i++) {
        if (arr[i] == 0) {
            if (i == n - 1 || arr[i + 1] == 0) {
                ans += 1;
            } else {
                bool l = false;
                i++;
                while (i <= n - 1 && arr[i] != 0) {
                    if (arr[i] == 2) l = true;
                    i++;
                }
                if (l == false) {
                    i--;
                }
                ans += 1;
            }
        } else if (arr[i] == 1 || arr[i] == 2) {
            while (i <= n - 1 && arr[i] != 0) {
                i++;
            }
            ans += 1;
        }
    }
    cout << ans << endl;
    return 0;
}
