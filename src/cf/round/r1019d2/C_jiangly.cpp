#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

void solve()
{
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + (a[i] <= k ? -1 : 1);
    }

    if (*std::min_element(pre.begin() + 2, pre.begin() + n) < 0) {
        std::cout << "YES\n";
        return;
    }

    if (std::count(pre.begin() + 2, pre.begin() + n, 0) > 1) {
        std::cout << "YES\n";
        return;
    }

    if (*std::max_element(pre.begin() + 1, pre.begin() + n - 1) > pre[n]) {
        std::cout << "YES\n";
        return;
    }
    if (std::count(pre.begin() + 1, pre.begin() + n - 1, pre[n]) > 1) {
        std::cout << "YES\n";
        return;
    }

    int l = 1, r = n - 1;
    while (l < r && pre[l] > 0) {
        l++;
    }
    while (l < r && pre[r] < pre[n]) {
        r--;
    }
    if (l < r) {
        std::cout << "YES\n";
        return;
    }

    std::cout << "NO\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}