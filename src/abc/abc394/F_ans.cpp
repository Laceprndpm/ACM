#include <bits/stdc++.h>
#define ll long long  // 定义长整型别名为ll
#define N  200010     // 定义常量N，可能表示图中节点的最大数量

using namespace std;  // 使用标准命名空间

int m, f[N], finalAns = 0;  // 定义节点数量n，f数组存储每个节点的某种状态，ans用于存储最终答案
vector<int> vt[N];          // vt是一个数组，其中每个元素是一个整数向量，表示图的邻接表

// 深度优先搜索函数
void dfs(int x, int lst)
{
    f[x] = 1;             // 初始化节点x的状态为1
    vector<int> seq;      // 创建一个向量seq，用于存储子节点的状态
    for (auto y : vt[x])  // 遍历节点x的所有邻接节点y
    {
        if (y != lst) {           // 如果y不是x的父节点（lst表示父节点，避免回到父节点）
            dfs(y, x);            // 递归调用dfs
            seq.push_back(f[y]);  // 将子节点y的状态添加到seq中
        }
    }
    sort(seq.begin(), seq.end());     // 对seq进行排序
    reverse(seq.begin(), seq.end());  // 将seq反转，使其成为降序

    // 根据seq中的值更新答案ans
    if (!seq.empty()) finalAns = max(finalAns, seq[0] + 1);  // 如果seq不为空，更新ans
    if (seq.size() >= 4)
        finalAns = max(finalAns, seq[0] + seq[1] + seq[2] + seq[3] + 1);  // 如果seq至少有4个元素，更新ans
    if (seq.size() >= 3) f[x] = max(f[x], seq[0] + seq[1] + seq[2] + 1);  // 如果seq至少有3个元素，更新节点x的状态
    return;                                                               // 结束函数
}

int main()
{
    scanf("%d", &m);               // 读取节点数量
    for (int i = 1; i < m; i++) {  // 读取边的信息，构建图
        int x, y;
        scanf("%d%d", &x, &y);  // 读取一对整数x和y
        x--, y--;               // 将节点编号减1，因为数组索引从0开始
        vt[x].push_back(y);     // 添加边x->y
        vt[y].push_back(x);     // 添加边y->x，因为是无向图
    }
    dfs(0, -1);         // 从节点0开始进行深度优先搜索，-1表示没有父节点
    if (finalAns <= 4)  // 如果最终答案小于等于4，输出-1
        puts("-1");
    else
        printf("%d\n", finalAns);  // 否则输出答案
    return 0;                      // 程序结束
}
