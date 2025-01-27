#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
signed main(signed argc, char *argv[])
{
    // 默认输入文件名
    string inputFile = "..\\G\\input.txt";

    // 检查命令行参数是否指定了输入文件
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-n" && i + 1 < argc) // 检查 -n 参数及其后续的文件名
        {
            inputFile = argv[i + 1];
            break;
        }
    }
    // freopen(inputFile.c_str(), "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        pq.push(temp);
    }
    cin >> k;
    while (k--)
    {
        pq.pop();
        int cnt2 = pq.top();
        pq.push(cnt2 + 1);
    }
    cout << pq.top();
    return 0;
}

// 轮数 1   2   3
// 0 	1 	2 	3
// 1 	2 	3 	3
// 2 	3 	3 	4
// 3 	3 	4 	4
// 4 	4 	4 	5

// 轮数 1   2   3
// 0    1   3   11
// 1    3   4   11
// 2    4   5   11
// 3    5   6   11
// 观察发现，当前两个数为n-1,n时，每次两个数同时+1，直到加入第三个数
//

// 轮数 1   2   3
// 0 	1 	2 	3
// 1 	2 	3 	3
// 2 	3 	3 	4
// 3 	3 	4 	4
// 4 	4 	4 	5
// 观察发现，[1,3]区间，从2,3,3到3,4,4
// 推测，当有四个数为n-1,n,n,n时，要[1,4]才能到n,n+1,n+1,n+1
// 0
// 1    3   4   4   4
// 2    4   4   4   5
// 3    4   4   5   5
// 4    4   5   5   5
// 当有n个数，符合n-1,n,n,n...n时，需要n轮才能全部加一