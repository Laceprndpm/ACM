#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define int  long long
#define endl '\n'
#define ll   long long

struct bi {
    int a;
    int b;
};

bool cmp(bi x, bi y)
{
    if (x.a != y.a) {
        return x.a > y.a;
    } else {
        return x.b < y.b;
    }
}

const int N = 5e5;
int       f[N], siz[N], j1[N], j2[N];  // 开并查集维护，记录siz和两个信息点

int find(int x)
{
    if (x == f[x])
        return x;
    else
        return f[x] = find(f[x]);
}

void merge(int x, int y)
{
    siz[find(y)] += siz[find(x)];
    f[find(x)] = find(y);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n + 2);
        vector<bi>  brr(n + 1);
        vector<int> lst(n + 2, 0);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            brr[i] = {arr[i], i};
        }
        arr[0] = 0, arr[n + 1] = 0;
        for (int i = 0; i <= n; i++) {
            f[i]   = i;
            siz[i] = 1;
            j1[i]  = 1;
            j2[i]  = 0;
        }
        sort(brr.begin() + 1, brr.end(), cmp);  // 先排序，按照从大到小
        int z1 = brr[1].a;
        int mx = z1, mi = z1, len = 0;
        int ans = 0;
        int t1 = 0, t2 = 0, tmp = 0;  // t1是奇数区间多少个，t2偶数区间多少个，tmp记录有无最大值可以选用的情况
        for (int i = 1; i <= n; i++) {
            if (z1 == brr[i].a) {  // 枚举当前点
                int wei  = brr[i].b;
                lst[wei] = 1;                // 加进来这个点，标志为可用
                t1++;                        // 多出一个奇数区间
                if (brr[i].a == brr[1].a) {  // 如果最大值更新一下
                    j2[wei] = 1;
                    tmp++;
                }
                if (arr[wei - 1] >= mi && lst[wei - 1] != 0) {  // 和左边合并
                    if (find(wei - 1) != find(wei)) {
                        if (j2[find(wei - 1)] == 3) {  // 首先把左边部分对于tmp贡献计算
                            tmp--;
                        } else if (j2[find(wei - 1)] == 2) {
                            if (j1[find(wei - 1)] == 2) {
                                tmp--;
                            }
                        } else if (j2[find(wei - 1)] == 1) {
                            tmp--;
                        }
                        if (j2[find(wei)] == 3) {  // 右边部分分类讨论更新tmp
                            tmp--;
                        } else if (j2[find(wei)] == 2) {
                            if (j1[find(wei)] == 2) {
                                tmp--;
                            }
                        } else if (j2[find(wei)] == 1) {
                            tmp--;
                        }
                        if (j1[find(wei - 1)] == 1) {  // 区间合并
                            t1--;                      // 区间奇偶个数减去
                            if (j2[find(wei)] == 1) {  // 奇数位置变偶数位置
                                j2[find(wei)] = 2;
                            } else if (j2[find(wei)] == 2) {
                                j2[find(wei)] = 1;
                            }
                            j2[find(wei)] |= j2[find(wei - 1)];        // 左右合并最大值位置情况
                            if (j1[find(wei - 1)] == j1[find(wei)]) {  // 右边区间也要改变
                                t1--;
                                j1[find(wei)] = 2;
                                t2++;
                            } else {
                                t2--;
                                j1[find(wei)] = 1;
                                t1++;
                            }
                        } else {
                            t2--;
                            j2[find(wei)] |= j2[find(wei - 1)];
                            if (j1[find(wei - 1)] == j1[find(wei)]) {
                                t2--;
                                j1[find(wei)] = 2;
                                t2++;
                            } else {
                                t1--;
                                j1[find(wei)] = 1;
                                t1++;
                            }
                        }
                        if (j1[find(wei)] == 1) {
                            if (j2[find(wei)] == 1 || j2[find(wei)] == 3) {
                                tmp++;
                            }
                        } else {
                            if (j2[find(wei)] != 0) {
                                tmp++;
                            }
                        }
                        merge(wei - 1, wei);
                    }
                }
                if (arr[wei + 1] >= mi && lst[wei + 1] != 0) {  // 需要注意wei变成左区间了
                    if (find(wei + 1) != find(wei)) {
                        if (j2[find(wei)] == 3) {
                            tmp--;
                        } else if (j2[find(wei)] == 2) {
                            if (j1[find(wei)] == 2) {
                                tmp--;
                            }
                        } else if (j2[find(wei)] == 1) {
                            tmp--;
                        }
                        if (j2[find(wei + 1)] == 3) {
                            tmp--;
                        } else if (j2[find(wei + 1)] == 2) {
                            if (j1[find(wei + 1)] == 2) {
                                tmp--;
                            }
                        } else if (j2[find(wei + 1)] == 1) {
                            tmp--;
                        }
                        if (j1[find(wei)] == 1) {
                            t1--;
                            if (j2[find(wei + 1)] == 1) {
                                j2[find(wei + 1)] = 2;
                            } else if (j2[find(wei + 1)] == 2) {
                                j2[find(wei + 1)] = 1;
                            }
                            j2[find(wei + 1)] |= j2[find(wei)];
                            if (j1[find(wei)] == j1[find(wei + 1)]) {
                                t1--;
                                j1[find(wei + 1)] = 2;
                                t2++;
                            } else {
                                t2--;
                                j1[find(wei + 1)] = 1;
                                t1++;
                            }
                        } else {
                            t2--;
                            j2[find(wei + 1)] |= j2[find(wei)];
                            if (j1[find(wei)] == j1[find(wei + 1)]) {
                                t2--;
                                j1[find(wei + 1)] = 2;
                                t2++;
                            } else {
                                t1--;
                                j1[find(wei + 1)] = 1;
                                t1++;
                            }
                        }
                        if (j1[find(wei + 1)] == 1) {
                            if (j2[find(wei + 1)] == 1 || j2[find(wei + 1)] == 3) {
                                tmp++;
                            }
                        } else {
                            if (j2[find(wei + 1)] != 0) {
                                tmp++;
                            }
                        }
                        merge(wei, wei + 1);
                    }
                }
            } else {          // 遇到了不同元素
                len = i - 1;  // 能用的元素数量你是知道的
                if (tmp != 0)
                    ans = max(ans, mx + mi + (len + t1) / 2);  // 如果存在选最大值，且siz最大最大的情况
                else
                    ans = max(ans, mx + mi + (len + t1) / 2 - 1);  // 选不到最大值要让一个位置给最大值
                z1 = brr[i].a;                                     // 更新信息
                mi = z1;                                           // 更新最小值
                i--;
            }
        }
        len = n;
        if (tmp != 0)
            ans = max(ans, mx + mi + (len + t1) / 2);
        else
            ans = max(ans, mx + mi + (len + t1) / 2 - 1);
        cout << ans << endl;
    }
    return 0;
}