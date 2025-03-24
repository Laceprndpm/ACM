#include <iostream>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

i64 binarySearch(i64 p1, i64 p2, i64 t1, i64 t2, i64 remain, i64 s)
{
    i64 l = 0;
    i64 r = min(((remain / (p1 - s)) + 1) * t1, (remain / (p2 - s) + 1) * t2);
    while (l < r) {
        i64 mid    = (r - l) / 2 + l;
        i64 damage = (mid / t1) * (p1 - s) + (mid / t2) * (p2 - s);
        if (damage >= remain) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

i64 mydfs(i64 p1, i64 p2, i64 t1, i64 t2, i64 h, i64 s)  // 以齐射结尾
{
    i64 minTime = binarySearch(p1, p2, t1, t2, h, s);
    for (int i = 1; i <= 5000; i++) {  // 枚举一个round里，激光1射了几次
        i64 timePerRound = i * t1;
        if (timePerRound > minTime) {
            break;
        }
        i64 timesLaser2 = timePerRound / t2;
        i64 damage;
        if (timesLaser2 > 0)
            damage = (i - 1) * (p1 - s) + (timesLaser2 - 1) * (p2 - s) + p1 + p2 - s;
        else
            continue;  // 无法以齐射结尾

        if (damage >= h) {
            minTime = min(minTime, timePerRound);
            break;
        }
        i64 timesRound = h / damage;
        i64 remainLife = (h - damage * timesRound);
        i64 remainTime = mydfs(p1, p2, t1, t2, remainLife, s);
        i64 totaltime  = timePerRound * timesRound + remainTime;
        minTime        = min(minTime, totaltime);
    }

    for (int i = 1; i <= 5000; i++) {  // 枚举一个round里，激光2射了几次
        i64 tRound = i * t2;
        if (tRound > minTime) {
            break;
        }
        i64 timesL1 = tRound / t1;
        i64 damage;
        if (timesL1 > 0)
            damage = (i - 1) * (p2 - s) + (timesL1 - 1) * (p1 - s) + p2 + p1 - s;
        else
            continue;

        if (damage >= h) {
            minTime = min(minTime, tRound);
            break;
        }
        i64 timesRound = h / damage;
        i64 remainLife = (h - damage * timesRound);
        i64 remainTime = mydfs(p1, p2, t1, t2, remainLife, s);
        i64 totaltime  = tRound * timesRound + remainTime;
        minTime        = min(minTime, totaltime);
    }
    return minTime;
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
    i64 p1, t1;
    i64 p2, t2;
    i64 h, s;
    cin >> p1 >> t1;
    cin >> p2 >> t2;
    cin >> h >> s;
    // 假如把16改17，那么最后一次直接斩杀最优，所以不能简单的要求齐射
    // 5 和 3
    // 3 * 2 + 5 wait 1     2次1单射  1次齐射
    // 3 * 3 wait 1 + 5 * 2 2次1单射  1次2单射，1次齐射
    // 对于某时刻，计算下二个行动时，即1激光和2激光蓄能完毕的时候，如果齐射和单射在
    // 不行，无法计算等待时间的贡献
    // 由于等待时间，状态不太好弄，要求必须以齐射结尾。。。
    // 齐射周期必须与L1或L2协调。。。
    //
    i64 minTime = mydfs(p1, p2, t1, t2, h, s);
    cout << minTime << '\n';
    return 0;
}