#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;

    unordered_map<int, int> num_v;
    num_v.reserve(4e5);
    num_v.max_load_factor(0.5);
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        num_v.clear();
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        for (int i = 0; i < n; i++) {
            num_v[arr[i]]++;
        }

        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        std::unordered_map<int, int> r2v;
        for (int i = 0; i < (int)arr.size(); ++i) {
            r2v[i] = arr[i];  // 映射排名到值
        }
        int l = 0, r = 0;
        int max_d = -1;
        int Ml = 0, Mr = 0;
        while (r < (int)arr.size()) {
            if (num_v[r2v[r]] >= k) {
                if (r2v[r] == (r2v[l] + (r - l))) {
                    if ((r2v[r] - r2v[l]) >= max_d) {
                        max_d = r - l;
                        Ml    = r2v[l];
                        Mr    = r2v[r];
                    }
                    r++;
                } else {
                    l = r;
                }
            } else {
                l = ++r;
            }
        }
        if (max_d == -1) {
            cout << -1 << '\n';
        } else {
            cout << Ml << ' ' << Mr << '\n';
        }
    }
    return 0;
}