#include <iostream>
#include <vector>
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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int         cntB = 0;
    i64         cnt  = 0;
    vector<int> Pcntarr(2);
    vector<int> Bcntarr(2);
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'B') {
            cntB++;
            Bcntarr[i % 2]++;
        } else {
            cnt += cntB;
            Pcntarr[i % 2]++;
        }
    }
    int add = 0;
    add     = abs(Bcntarr[1] - (Bcntarr[0] + Bcntarr[1]) / 2);

    cout << (cnt + add) / 2 << '\n';
    // BPBPBBBBBPBBBBB
    // BPBPBBBBBBBBBPB
    // BPBBBBBBBBBPBPB
    // BBBBBBBBBPBPBPB
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}