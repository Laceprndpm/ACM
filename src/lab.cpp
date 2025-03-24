#include <algorithm>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
int       ju[4][4];
const int N = (int)1e3 + 5;
int       X[N], Y[N];

int Rnd(int l, int r)
{
    return l + rand() % (r - l + 1);
}

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
    if (ju[1][1] + ju[2][2] + ju[3][3] == 2) {
        if (ju[1][1] == 0) x = 1, y = 1;
        if (ju[2][2] == 0) x = 2, y = 2;
        if (ju[3][3] == 0) x = 3, y = 3;
    } else if (ju[1][3] + ju[2][2] + ju[3][1] == 2) {
        if (ju[1][3] == 0) x = 1, y = 3;
        if (ju[2][2] == 0) x = 2, y = 2;
        if (ju[3][1] == 0) x = 3, y = 1;
    } else {
        for (int i = 1; i <= 3; ++i) {
            int sum = 0, who = 0;
            for (int j = 1; j <= 3; ++j)
                if (ju[i][j] == 0)
                    who = j;
                else
                    sum += ju[i][j];
            if (sum == 2) {
                x = i, y = who;
                return;
            }
        }
        for (int j = 1; j <= 3; ++j) {
            int sum = 0, who = 0;
            for (int i = 1; i <= 3; ++i)
                if (ju[i][j] == 0)
                    who = i;
                else
                    sum += ju[i][j];
            if (sum == 2) {
                x = who, y = j;
                return;
            }
        }
        x = Rnd(1, 3), y = Rnd(1, 3);
        while (ju[x][y])
            x = Rnd(1, 3), y = Rnd(1, 3);
    }
}

signed main(signed argc, char** argv)
{
    srand(time(NULL));
    while (true) {
        std::string op;
        std::cin >> op;
        if (op == "Over") break;
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 3; ++j)
                ju[i][j] = 0;
        std::cout << 2 << ' ' << 2 << std::endl;
        ju[2][2] = +1;
        int x, y;
        std::cin >> x >> y;
        ju[x][y] = -1;
        X[1] = 2, Y[1] = 2;
        X[2] = x, Y[2] = y;
        if (x == 2 || y == 2) {
            // 第一步落在中间位，必有制胜策略
            if (x <= 2 && y <= 2) {
                std::cout << 1 << ' ' << 1 << std::endl;
                ju[1][1] = +1;
            } else {
                std::cout << 3 << ' ' << 3 << std::endl;
                ju[3][3] = +1;
            }
            // 接下来一步走拐角
            std::cin >> x >> y;
            ju[x][y] = -1;
            if (ju[1][1] + ju[2][2] + ju[3][3] == 2)
                // 第二步对方没有堵自己
                if (ju[1][1] == 0)
                    std::cout << 1 << ' ' << 1 << std::endl;
                else
                    std::cout << 3 << ' ' << 3 << std::endl;
            else
                // 第二步对方堵自己
                if (ju[1][1] == 1)
                    if (ju[2][1] == -1) {
                        std::cout << 1 << ' ' << 3 << std::endl;
                        std::cin >> x >> y;
                        if (x != 3 || y != 1)
                            std::cout << 3 << ' ' << 1 << std::endl;
                        else
                            std::cout << 1 << ' ' << 2 << std::endl;
                    } else {
                        std::cout << 3 << ' ' << 1 << std::endl;
                        std::cin >> x >> y;
                        if (x != 1 || y != 3)
                            std::cout << 1 << ' ' << 3 << std::endl;
                        else
                            std::cout << 2 << ' ' << 1 << std::endl;
                    }
                else if (ju[2][3] == -1) {
                    std::cout << 3 << ' ' << 1 << std::endl;
                    std::cin >> x >> y;
                    if (x != 1 || y != 3)
                        std::cout << 1 << ' ' << 3 << std::endl;
                    else
                        std::cout << 3 << ' ' << 2 << std::endl;
                } else {
                    std::cout << 1 << ' ' << 3 << std::endl;
                    std::cin >> x >> y;
                    if (x != 3 || y != 1)
                        std::cout << 3 << ' ' << 1 << std::endl;
                    else
                        std::cout << 2 << ' ' << 3 << std::endl;
                }
        } else {
            bool flag = true;
            for (int i = 3; flag; ++i)
                if (i & 1) {
                    playChess(X[i], Y[i]);
                    if (i >= 7) ju[X[i - 6]][Y[i - 6]] = 0;
                    std::cout << X[i] << ' ' << Y[i] << std::endl;
                    if (check(ju[X[i]][Y[i]] = +1)) flag = false;
                } else {
                    std::cin >> X[i] >> Y[i];
                    if (i >= 8) ju[X[i - 6]][Y[i - 6]] = 0;
                    if (check(ju[X[i]][Y[i]] = -1)) flag = false;
                }
        }
        std::cin >> op;  // 输入胜负字符串
    }
}
