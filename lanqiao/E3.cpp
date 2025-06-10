#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// 标记数组
bool vis[30] = {false};  // 列的标记数组，初始为false
bool lr[30]  = {false};  // 左对角线的标记数组，初始为false
bool fr[30]  = {false};  // 右对角线的标记数组，初始为false

int       cnt = 0;  // 记录所有摆放方法的数量
const int n   = 6;

bool judge(int x, int y)  // 判断当前位置是否能摆放皇后，当前位置为（x,y）
{
    if (vis[y] || lr[y - x + n] || fr[x + y]) return false;
    return true;
}

void dfs(int x)
{
    if (x == n)  // 结束条件:摆放的个数达到n个，在这里即8个
    {
        cnt++;
        return;
    }

    for (int i = 1; i <= n; i++)  // 遍历所有情况，i表示列，即纵坐标
    {
        if (!judge(x, i))  // 判断条件，如果不能摆放就continue
            continue;
        // 标记已走过
        vis[i]        = true;
        lr[i - x + n] = true;
        fr[x + i]     = true;
        dfs(x + 1);  // 在i行已经有棋子后开始下一行
        // 撤回标记，不影响下一次的落棋
        vis[i]        = false;
        lr[i - x + n] = false;
        fr[x + i]     = false;
    }
    return;
}

int main()
{
    dfs(0);
    cout << cnt << endl;
    return 0;
}
