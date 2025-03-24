#include <cstdio>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    // 主要矛盾在于无法及时调整道上的人，难道只要保证最大化乘法就最优吗？
    // 1  1
    // +1 x3
    // got 1+3
    // 1   1
    // x2  +5   but next is +1 x99,seems will change?
    // if 5 1
    // 5   1
    // got
    // 5 + 6 11
    // 11 + 1 = 12
    // 是的，至少会增加一倍，所以放在乘法一定最优，如果加法，则要找到下一个乘法点位
    //
    // 感觉思路没问题啊，假如当前extra = x，那么放到一个乘法赛道一定是赚的吗？哦，对，在
    //
    i64 a = 1, b = 1;
    i64 extra = 0;
    for (int i = 1; i <= n; i++) {
        char op1, op2;
        int  val1, val2;
        while ((op1 = getchar()) != '+' && (op1 != 'x'))
            ;
        scanf("%d", &val1);
        while ((op2 = getchar()) != '+' && (op2 != 'x'))
            ;
        scanf("%d", &val2);
        if (op1 == 'x' && op2 == 'x') {
            if (val1 > val2) {
                a += extra;
            } else if (val1 < val2) {
                b += extra;
            } else {
                extra = extra * val1 + (a + b) * (val1 - 1);
                continue;
            }
            extra = a * (val1 - 1) + b * (val2 - 1);
            // 1  1  2
            // x3 x3
            // +1 x3
            continue;
        }
        if (op1 == 'x' && op2 == '+') {
            a += extra;
            extra = a * (val1 - 1) + val2;
            continue;
        }
        if (op1 == '+' && op2 == 'x') {
            b += extra;
            extra = val1 + b * (val2 - 1);
            continue;
        }
        if (op1 == '+' && op2 == '+') {
            extra += val1 + val2;
        }
    }
    cout << a + b + extra << '\n';
}

signed main(int argc, char** argv)
{
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