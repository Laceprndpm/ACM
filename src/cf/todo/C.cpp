#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n, m;
    cin >> n >> m;
    string input;
    cin >> input;
    // 010101000
    // 当l为1，除非l-r全部为1，否则l变换必然不同？如果左面是0依然相同
    // 当r为0，除非l-r全部为0，否则r变换比如不同，除非右面1
    // 尝试l算左面，r算右面
    // 11101011
    //
    // 假如l-1和l都是0，或者r和r+1都是1，那么[l-1,r],[l,r]...都等价，其余则都不然
    // 存在[l1,r1]，[l2,r2]，l1与l2属于同一个线，r1与r2属于同一个，则重复计数，我可以存储每个边界，进行离散化
    vector<int> rank2val;
    int         l = 0, r = 0;
    for (; r < n; r++) {
        if (input[l] != input[r]) {
            l = r;
            rank2val.emplace_back(r - 1);
        }
    }
    rank2val.emplace_back(n - 1);
    set<pair<int, int>> unique01;
    set<pair<int, int>> unique11;
    set<pair<int, int>> unique00;
    set<pair<int, int>> unique10;
    bool                unchange = false;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (input[l] == '0' && input[r] == '1') {
            int L = lower_bound(rank2val.begin(), rank2val.end(), l) - rank2val.begin();
            int R = lower_bound(rank2val.begin(), rank2val.end(), r) - rank2val.begin();
            if (L == R - 1) {
                unchange = true;
                continue;
            }
            unique01.insert({L, R});
        } else if (input[l] == '1' && input[r] == '1') {
            if (lower_bound(rank2val.begin(), rank2val.end(), l) == lower_bound(rank2val.begin(), rank2val.end(), r)) {
                unchange = true;
                continue;
            }
            // 010100010100000001111100
            if (l > 0 && input[l - 1] == '0') {
                int L = lower_bound(rank2val.begin(), rank2val.end(), l - 1) - rank2val.begin();
                int R = lower_bound(rank2val.begin(), rank2val.end(), r) - rank2val.begin();
                unique01.insert({L, R});
                continue;
            }
            int R = lower_bound(rank2val.begin(), rank2val.end(), r) - rank2val.begin();
            unique11.insert({l, R});
        } else if (input[l] == '0' && input[r] == '0') {
            if (lower_bound(rank2val.begin(), rank2val.end(), l) == lower_bound(rank2val.begin(), rank2val.end(), r)) {
                unchange = true;
                continue;
            }
            if (r < n - 1 && input[r + 1] == '1') {
                int L = lower_bound(rank2val.begin(), rank2val.end(), l) - rank2val.begin();
                int R = lower_bound(rank2val.begin(), rank2val.end(), r + 1) - rank2val.begin();
                unique01.insert({L, R});
                continue;
            }
            int L = lower_bound(rank2val.begin(), rank2val.end(), l) - rank2val.begin();
            unique00.insert({L, r});
        } else {
            if (l > 0 && input[l - 1] == '0') {
                if (r < n - 1 && input[r + 1] == '1') {
                    int L = lower_bound(rank2val.begin(), rank2val.end(), l - 1) - rank2val.begin();
                    int R = lower_bound(rank2val.begin(), rank2val.end(), r + 1) - rank2val.begin();
                    unique01.insert({L, R});
                    continue;
                } else {
                    int L = lower_bound(rank2val.begin(), rank2val.end(), l - 1) - rank2val.begin();
                    unique00.insert({L, r});
                    continue;
                }
            }
            if (r < n - 1 && input[r + 1] == '1') {
                int R = lower_bound(rank2val.begin(), rank2val.end(), r + 1) - rank2val.begin();
                unique11.insert({l, R});
                continue;
            }
            // int L = lower_bound(rank2val.begin(), rank2val.end(), l - 1) - rank2val.begin();
            // int R = lower_bound(rank2val.begin(), rank2val.end(), r + 1) - rank2val.begin();
            unique10.insert({l, r});
        }
    }
    int ans = unique00.size() + unique01.size() + unique10.size() + unique11.size();
    cout << ans + unchange << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// 000000001010101111111