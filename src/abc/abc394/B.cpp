#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<string>         arr(n);
    vector<pair<int, int>> brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        brr[i].first  = arr[i].size();
        brr[i].second = i;
    }
    sort(brr.begin(), brr.end());
    string ans;
    for (int i = 0; i < n; i++) {
        ans = ans + arr[brr[i].second];
    }
    cout << ans;
    return 0;
}