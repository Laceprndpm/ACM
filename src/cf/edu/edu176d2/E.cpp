#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 1001010
    // 假如矩阵各位相同，那么。。。
    // 若随机选择k个行或者k个列，甚至可以选择莫一行和某一列。。。
    // 有点难缠
    // 1011
    //     1
    //     1
    //     0
    // 假如不一样在这一位上，那么这一位就可以这样。。。
    // 如果下一位依然不一样，那么也得按照这样的方法排列
    // 如果一样，就要
    // 枚举每一位，可能是一样位（2*2）和不一样位（2 * 2），共8，然后不一样位的话只记一次，
    return 0;
}