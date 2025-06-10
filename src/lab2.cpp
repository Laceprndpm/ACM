#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "testlib.h"

int Rnd(int l, int r)
{
    return rnd.next(l, r);
}

int       ju[4][4];
const int N = (int)1e6 + 5;
int       x[N], y[N];

bool check(int tp)
{
    // 验证 tp 方是否胜利
    bool flag = true;
    for (int i = 1; i <= 3; ++i)
        flag &= (ju[i][i] == tp);
    if (flag) return true;  // 主对角线
    flag = true;
    for (int i = 1; i <= 3; ++i)
        flag &= (ju[i][4 - i] == tp);  // 副对角线
    if (flag) return true;
    for (int i = 1; i <= 3; ++i) {
        flag = true;
        for (int j = 1; j <= 3; ++j)
            flag &= (ju[i][j] == tp);
        if (flag) return true;  // 同一行
    }
    for (int j = 1; j <= 3; ++j) {
        flag = true;
        for (int i = 1; i <= 3; ++i)
            flag &= (ju[i][j] == tp);
        if (flag) return true;  // 同一列
    }
    return false;
}

void playChess(int& x, int& y)
{
    x = Rnd(1, 3), y = Rnd(1, 3);
    while (ju[x][y] != 0)
        x = Rnd(1, 3), y = Rnd(1, 3);
}

signed main(signed argc, char** argv)
{
    registerGen(argc, argv, 1);
    registerTestlibCmd(argc, argv);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int T = inf.readLong(), c1 = inf.readLong(), c2 = inf.readLong();
    int t = 0, s = 0, S = (100 + c2) * T;
    for (int _ = 1; _ <= T; ++_) {
        std::cout << "Start" << std::endl;
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 3; ++j)
                ju[i][j] = 0;
        for (int i = 1;; ++i)
            if (i & 1) {
                if (++s > S) quitf(_wa, "too many steps");
                std::cin >> x[i] >> y[i];
                if (x[i] < 1 || y[i] < 1 || x[i] > 3 || y[i] > 3)
                    quitf(_wa, "visit a wrong place (%lld, %lld)", x[i], y[i]);
                if (ju[x[i]][y[i]] != 0) quitf(_wa, "visit a existed place (%lld, %lld)", x[i], y[i]);
                if (i >= 7) ju[x[i - 6]][y[i - 6]] = 0;
                if (check(ju[x[i]][y[i]] = +1)) {
                    std::cout << "Win" << std::endl;
                    ++t;
                    break;
                }
            } else {
                playChess(x[i], y[i]);
                if (i >= 8) ju[x[i - 6]][y[i - 6]] = 0;
                std::cout << x[i] << ' ' << y[i] << std::endl;
                if (check(ju[x[i]][y[i]] = -1)) {
                    std::cout << "Lose" << std::endl;
                    break;
                }
            }
    }
    std::cout << "Over" << std::endl;
    if (t <= c1)
        quitf(_wa, "you're a loser");
    else {
        double pc = (double)(S - s) / T;
        if (pc >= 1.0)
            quitf(_ok, "AC!");
        else
            quitp(pc, "PC!");
    }
}
