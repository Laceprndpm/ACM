#include <cmath>
#include <iostream>
using namespace std;
// 标记数组
bool vis1[30]      = {false};  // 列的标记数组，初始为false
bool lr1[30]       = {false};  // 左对角线的标记数组，初始为false
bool fr1[30]       = {false};  // 右对角线的标记数组，初始为false
bool vis2[30]      = {false};  // 列的标记数组，初始为false
bool lr2[30]       = {false};  // 左对角线的标记数组，初始为false
bool fr2[30]       = {false};  // 右对角线的标记数组，初始为false
bool board[30][30] = {false};

int           cnt = 0;  // 记录所有摆放方法的数量
constexpr int n   = 2;

bool judge1(int x, int y)  // 判断当前位置是否能摆放皇后，当前位置为（x,y）
{
    if (vis1[y] || lr1[y - x + n] || fr1[x + y] || board[x][y]) return false;
    return true;
}

bool judge2(int x, int y)  // 判断当前位置是否能摆放皇后，当前位置为（x,y）
{
    if (vis2[y] || lr2[y - x + n] || fr2[x + y] || board[x][y]) return false;
    return true;
}

void dfs(int x)
{
    if (x == n + 1)  // 结束条件:摆放的个数达到n个，在这里即8个
    {
        cnt++;
        return;
    }
    for (int w = 1; w <= n; w++) {
        if (judge1(x, w)) {
            vis1[w]        = true;
            lr1[w - x + n] = true;
            fr1[x + w]     = true;
            board[x][w]    = true;
            for (int b = 1; b <= n; b++) {
                if (b == w) continue;
                if (judge2(x, b)) {
                    vis2[b]        = true;
                    lr2[b - x + n] = true;
                    fr2[x + b]     = true;
                    board[x][b]    = true;
                    dfs(x + 1);
                    vis2[b]        = false;
                    lr2[b - x + n] = false;
                    fr2[x + b]     = false;
                    board[x][b]    = false;
                }
            }
            vis1[w]        = false;
            lr1[w - x + n] = false;
            fr1[x + w]     = false;
            board[x][w]    = false;
        }
    }
    return;
}

int main()
{
    dfs(1);
    cout << cnt << endl;
    return 0;
}

// 2 0
// 3 0
// 4 2
// 5 40
// 6 12
// 7 496
// 8 3252
// 9 48328
// 10 205188
// 11 2732488