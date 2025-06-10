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

int       cnt = 0;  // 记录所有摆放方法的数量
const int n   = 5;

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

void dfs(int x, int y)
{
    if (x == n + 1 && y == n + 1)  // 结束条件:摆放的个数达到n个，在这里即8个
    {
        cnt++;
        return;
    }
    if (x > n + 1 || y > n + 1) {
        return;
    }
    for (int i = 1; i <= n; i++)  // 遍历所有情况，i表示列，即纵坐标
    {
        if (x <= n && judge1(x, i))  // 判断
        {                            // 标记已走过
            vis1[i]        = true;
            lr1[i - x + n] = true;
            fr1[x + i]     = true;
            board[x][i]    = true;
            dfs(x + 1, y);  // 在i行已经有棋子后开始下一行
                            // 撤回标记，不影响下一次的落棋
            board[x][i]    = false;
            vis1[i]        = false;
            lr1[i - x + n] = false;
            fr1[x + i]     = false;
        }
        if (y <= n && judge2(y, i)) {
            vis2[i]        = true;
            lr2[i - y + n] = true;
            fr2[y + i]     = true;
            board[y][i]    = true;
            dfs(x, y + 1);  // 在i行已经有棋子后开始下一行
                            // 撤回标记，不影响下一次的落棋
            board[y][i]    = false;
            vis2[i]        = false;
            lr2[i - y + n] = false;
            fr2[y + i]     = false;
        }
    }
    return;
}

int main()
{
    dfs(1, 1);
    cout << cnt << endl;
    return 0;
}
