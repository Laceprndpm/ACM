#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    int  ans    = 0;
    bool hasTwo = false;  // 标记当前连续非零子序列中是否包含2

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            // 当前元素为0，需要检查前面的连续非零子序列
            if (!hasTwo) {
                // 如果序列中没有2，则需要考虑如何变红
                if (i > 0 && arr[i - 1] == 1) {
                    // 如果序列左边是1，则优先让左边的1变红
                    ans++;
                } else if (i + 1 < n && arr[i + 1] == 1) {
                    // 如果序列左边没有1，但右边有1，则让右边的1变红
                    ans++;
                    i++;  // 跳过下一个元素，因为它已经被变红了
                }
            }
            hasTwo = false;  // 重置标记，因为当前元素是0
        } else {
            // 当前元素为1或2
            if (arr[i] == 2) {
                hasTwo = true;  // 标记当前连续非零子序列中包含2
            }
            // 如果当前元素不是最后一个元素，或者它不是0，则不需要额外的操作
        }
    }
    cout << ans << endl;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}