#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int k = 0; k < t; k++) {
        int n, ans = -1, sum;
        cin >> n;
        vector<int>  a(n), p(n);
        vector<bool> is_yz(n, 1);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 1; i < n; i++) {
            cin >> p[i];
            p[i]--;
            is_yz[p[i]] = 0;
        }
        for (int i = 1; i < n; i++) {
            if (is_yz[i]) {
                sum   = a[i];
                int q = i;
                while (p[q] != 0) {
                    if (a[p[q]] < sum) sum = (sum + a[p[q]]) / 2;
                    q = p[q];
                }
                if (ans == -1 || ans > sum) ans = sum;
            }
        }
        cout << ans + a[0] << endl;
    }
    return 0;
}