#include <bits/stdc++.h>

#include <vector>
using i64 = long long;
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    vector<int> brr(m);
    for (int &i : arr) {
        cin >> i;
    }
    for (int &i : brr) {
        cin >> i;
    }
    i64         ans = 0;
    for (int i = 1; i < n; i++) {
        ans += abs(arr[i] - arr[i - 1]);
    }
    for (int i = 1; i < m; i++) {
        ans += abs(brr[i] - brr[i - 1]);
    }
    cout << ans << '\n';
}