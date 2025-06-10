#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           k;
constexpr int MOD = 998244353;
vector<int>   inputArr;
i64           ans = 1;
vector<int>   fac((1 << 19) + 1);
int           totalcnt = 0;

i64 qpow(i64 n, i64 q, i64 mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

void divideAndControl(int depth)
// 当前总人数位1<<depth
{
    if (depth != 0) {
        divideAndControl(depth - 1);
    }
    int r   = (1 << depth) - 1;
    int mid = r / 2;
    int cnt = 0;
    // 假设赢的人全部排好序了
    // 对即将死亡的人
    vector<bool> antiCrush(mid + 1, 0);
    for (int i = mid + 1; i <= r; i++) {
        if (inputArr[i] == -1) {
            cnt++;
        } else {
            int place = inputArr[i] / (1 << (k - depth + 1));
            if (antiCrush[place]) {
                cout << 0 << '\n';
                exit(0);
            } else {
                antiCrush[place] = 1;
            }
        }
    }
    ans *= fac[cnt];
    ans %= MOD;
    ans %= MOD;
    antiCrush.resize(1);
}

signed main(int argc, char** argv)
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    cin >> k;
    int n = 1 << k;
    inputArr.resize(n);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        if (tmp != -1) {
            tmp--;
        }
        inputArr[i] = tmp;
    }
    vector<int> temp(inputArr.size(), -1);
    for (int i = 0; i < n; i++) {
        if (inputArr[i] != -1) {  // 第i号种子没人拿
            temp[inputArr[i]] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ((temp[i] != -1) ? temp[i] + 1 : -1) << ' ';
    }
    cout << endl;
    swap(temp, inputArr);
    fac[0] = 1;
    for (int i = 1; i <= n / 2; i++) {
        fac[i] = (fac[i - 1] * (long long)i) % MOD;
    }

    divideAndControl(k);
    cout << ans;
    // 考虑 1 3 2 4
    // 毫无疑问的，需要分块或者归并，其中假如1在[0,2^(k-1) )，2就在[2^(k-1), 2^k)，可以互换
    // 3和4可以随便填补，从小到大考虑？
    // 考虑 1 2 3 4 5 6 7 8
    //      1 5
    // 3 4 不能开局被淘汰，也许从大到小
    // 2e19，支持的时间复杂度为O(nlogn)
    // dp不可能
    // 贪心不可能
    // 假如我规定每场比赛的一号位获胜
    // 有2^k个人，第一场淘汰2^(k-1)个人，检查这2^(k-1)个人中是否有冲突，且这2^(k-1)人互相可互换，如果另外
    //  1  2  3  4，2*2*2*2 == 16 true
    // -1 -1 -1 -1
    //  1  2  3  4  5  6  7  8
    // -1 -1 -1 -1  2 -1 -1 -1
    // 3! * 2 * 2 * 2 * 2! * 2 * 2 * 2
    //

    return 0;
}
