#include <cstdint>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr i64 MOD = INT64_MAX;

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

void solve()
{
    // x=1011, y=1001
    // query 0 z=10100
    // 10|(分割)100
    // 1+1/10+1||||100+0/11+1/10+10
    // 是否只有这种可能？
    // 比如说前两个是有后一段的贡献的，不过这在确定后一段后是否能简单算出？
    // 从低位到高位，每次以1分界
    // 1000000这样
    // 0101010模,发现差
    // 0101100
    // 倒数第二位一定是00
    // 如果某一位|1后，还是0，有两种情况，一是进位了，那么只能是00
    // 一是原本全1，而这两种的区别就在于第二位
    // 0111111模这个?
    // 和原本答案的差值肯定可以用二进制表示
    // 0101010比如这个
    // 假如第一个1是由后两位溢出得出的，那么就是00
    // 假如是由倒数第二位0变成1得出的，也说的道理
    //
    // 若还是0，且溢出计数器为0，则肯定为11？或00.。。
    // 若还是0，且溢出计数器为1，则？
    // 若变成1，且溢出计数器为0，则10
    // 若变成1，且溢出计数器为1，则11或者00。。。
    //
    // 莫非是对每一个存疑点进行|操作？
    // 100/000
    // 110
    // 010/010
    // 110无法辨别！
    // 不能简单|1啊
    // 100/000 | 10
    // 1000
    // 10/10 | 10
    // 100
    // 011/001|10
    // 这个z可能对应了多少xy?
    // 10100|0
    // 100|10000
    // 为什么不同的解，对应的|m值会不同？因为如果是10 + 0和1+1，分别|1后，结果不同，为什么？
    // 对于z的每一位，可能由x^y，并往高位进一得到，或者单纯的x|y
    // query 1
    // 还是z=10100
    // 可以说明什么？x和y的最低位都是1，那么x和y都倒数第二位
    // 就只有一个1，倒数第三位也就不可能是有进位的了，倒数第四位可能有进位，
    // 也可能没有，也就是说无法确认是10+0还是1+1，这是致命的
    //
    i64 input1, input2;
    cout << 0 << endl;  // 先看看0
    cin >> input1;
    cout << 357913941ll << endl;  // 解释0001 0101 0101 0101 0101 0101 0101 0101
    ;                             //     32   28   24   20   16   12   8    4
    cin >> input2;
    i64         delta = input2 - input1;
    vector<int> a(40);
    vector<int> b(40);
    // delta相当于全部的奇数位补0
    // 357913941
    // 715827882
    for (int j = 30; j >= 1; j--) {
        if (delta >> (j - 1) & 1) {
            if (j % 2) {
                a[j] = 1;
                b[j] = 0;
            } else {
                a[j - 1] = 0;
                b[j - 1] = 0;
            }
        } else {
            if (j % 2 && !(delta >> j & 1)) {
                a[j] = 1;
                b[j] = 1;
            }
        }
    }
    i64 delta2 = 0;
    i64 cursum = 0;
    for (int i = 1; i <= 31; i++) {
        if (a[i]) {
            cursum += qpow(2, i - 1);
        }
        if (b[i]) {
            cursum += qpow(2, i - 1);
        }
    }
    delta2 = input1 - cursum;
    for (int j = 31; j >= 1; j--) {
        if (delta2 >> (j - 1) & 1) {
            if (j % 2) {
                a[j - 1] = 1;
                b[j - 1] = 1;
            } else {
                a[j] = 1;
                b[j] = 0;
            }
        }
    }
    cout << '!' << endl;
    i64 m;
    cin >> m;
    i64 curans = 0;
    for (int i = 1; i <= 31; i++) {
        if (m >> (i - 1) & 1) {
            curans += qpow(2, i);
        } else {
            if (a[i]) {
                curans += qpow(2, i - 1);
            }
            if (b[i]) {
                curans += qpow(2, i - 1);
            }
        }
    }
    cout << curans << endl;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
