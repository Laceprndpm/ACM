#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 2e6 + 5;

int weight[N];
int value[N];
int left_bound[N];
int right_bound[N];
LL  presum_val[N];
LL  presum_cnt[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    LL n, m, s;
    cin >> n >> m >> s;
    int r = INT32_MIN;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
        r = max(r, weight[i]);
    }
    int l = 0;
    for (int i = 1; i <= m; i++) {
        cin >> left_bound[i] >> right_bound[i];
    }
    r++;
    int L = l;
    int R = r;

    LL y = 0;

    while (l < r) {
        memset(presum_cnt, 0, sizeof(presum_cnt));
        memset(presum_val, 0, sizeof(presum_val));
        int mid = (r - l) / 2 + l;
        for (int i = 1; i <= n; i++) {
            if (weight[i] >= mid) {
                presum_cnt[i] = presum_cnt[i - 1] + 1;
                presum_val[i] = presum_val[i - 1] + value[i];
            } else {
                presum_cnt[i] = presum_cnt[i - 1];
                presum_val[i] = presum_val[i - 1];
            }
        }
        y = 0;
        for (int i = 1; i <= m; i++) {
            y += (presum_cnt[right_bound[i]] - presum_cnt[left_bound[i] - 1])
                 * (presum_val[right_bound[i]] - presum_val[left_bound[i] - 1]);
        }
        if (s - y >= 0) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    {
        memset(presum_cnt, 0, sizeof(presum_cnt));
        memset(presum_val, 0, sizeof(presum_val));
        int mid = l;  // [l,r)
        for (int i = 1; i <= n; i++) {
            if (weight[i] >= mid) {
                presum_cnt[i] = presum_cnt[i - 1] + 1;
                presum_val[i] = presum_val[i - 1] + value[i];
            } else {
                presum_cnt[i] = presum_cnt[i - 1];
                presum_val[i] = presum_val[i - 1];
            }
        }
        y = 0;
        for (int i = 1; i <= m; i++) {
            y += (presum_cnt[right_bound[i]] - presum_cnt[left_bound[i] - 1])
                 * (presum_val[right_bound[i]] - presum_val[left_bound[i] - 1]);
        }
    }
    LL y2 = y;

    l = L;
    r = R;
    while (l < r) {
        memset(presum_cnt, 0, sizeof(presum_cnt));
        memset(presum_val, 0, sizeof(presum_val));
        int mid = (r - l - 1) / 2 + 1 + l;  // < r
        for (int i = 1; i <= n; i++) {
            if (weight[i] >= mid) {
                presum_cnt[i] = presum_cnt[i - 1] + 1;
                presum_val[i] = presum_val[i - 1] + value[i];
            } else {
                presum_cnt[i] = presum_cnt[i - 1];
                presum_val[i] = presum_val[i - 1];
            }
        }
        y = 0;
        for (int i = 1; i <= m; i++) {
            y += (presum_cnt[right_bound[i]] - presum_cnt[left_bound[i] - 1])
                 * (presum_val[right_bound[i]] - presum_val[left_bound[i] - 1]);
        }
        if (s - y <= 0) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    {
        memset(presum_cnt, 0, sizeof(presum_cnt));
        memset(presum_val, 0, sizeof(presum_val));
        int mid = l;
        for (int i = 1; i <= n; i++) {
            if (weight[i] >= mid) {
                presum_cnt[i] = presum_cnt[i - 1] + 1;
                presum_val[i] = presum_val[i - 1] + value[i];
            } else {
                presum_cnt[i] = presum_cnt[i - 1];
                presum_val[i] = presum_val[i - 1];
            }
        }
        y = 0;
        for (int i = 1; i <= m; i++) {
            y += (presum_cnt[right_bound[i]] - presum_cnt[left_bound[i] - 1])
                 * (presum_val[right_bound[i]] - presum_val[left_bound[i] - 1]);
        }
    }
    LL y1 = y;
    y1    = abs(y1 - s);
    y2    = abs(y2 - s);
    cout << min(y1, y2);

    return 0;
}