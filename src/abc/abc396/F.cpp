#include <iostream>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class TreeArr {
private:
    vector<int> bitArr;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    TreeArr(int n) : bitArr(n + 1) {}

    void update(int place, int value)
    {
        for (int i = place; i < bitArr.size(); i += lowbit(i)) {
            bitArr[i] += value;
        }
    }

    int query(int place)
    {
        int res = 0;
        for (int i = place; i; i -= lowbit(i)) {
            res += bitArr[i];
        }
        return res;
    }
};

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> inputA(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> inputA[i];
    }
    TreeArr             treearr2(m);
    i64                 sum = 0;
    vector<vector<int>> idx(m + 1);
    for (int i = n; i >= 1; i--) {
        idx[inputA[i]].emplace_back(i);
        treearr2.update(inputA[i] + 1, 1);
        sum += treearr2.query(inputA[i]);
    }
    cout << sum << '\n';
    for (int i = 1; i <= m - 1; i++) {
        // 对于M - i，将由M-1变成0，那么所有的原逆序对将变为顺序对，所有的顺序对将变为逆序对
        // 因为M-1已经最大，所以所有索引小于它的数（除本身）都构成顺序对，所有索引大于它的
        i64 addnum     = 0;
        i64 decressnum = 0;
        for (int j = 0; j < idx[m - i].size(); j++) {
            addnum += idx[m - i][j] - 1;
            decressnum += n - idx[m - i][j];
        }
        sum += addnum - decressnum;
        cout << sum << '\n';
    }
    return 0;
}