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
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    cin >> k;
    int cnt = arr[0] + 1;
    // // n-1,n-1,n,n,n,n+1,n+1,m1 化为 n-1,n,n...n,m2
    // auto lb = lower_bound(arr.begin(), arr.end(), cnt); // 获得第一个n的位置,此次为3
    // k -= lb - arr.begin();                              // 此处为1
    int num_n_1 = upper_bound(arr.begin(), arr.end(), cnt - 1) - arr.begin();
    if (k >= num_n_1)
        k -= num_n_1 - 1;
    else
    {
        cout << cnt - 1;
        return 0;
    }
    while (true)
    {
        // n-1, n, n, n... n, m
        int group_num = upper_bound(arr.begin(), arr.end(), cnt) - arr.begin(); // m的位置
        auto target_position = upper_bound(arr.begin(), arr.end(), cnt);        // m的位置
        int target = target_position != arr.end() ? *target_position : cnt + 1;
        int step = target - cnt;
        if ((group_num - 1) * step > k) // 不足以扩大group
        {
            cnt += k / (group_num - 1) - 1 + (k % (group_num - 1) != 0 ? 1 : 0);
            break;
        }
        else // 将target也加入group，
        {
            cnt = target;
            k -= (group_num - 1) * step;
        }
    }
    cout << cnt;
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