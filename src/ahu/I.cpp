#include <cstdio>
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
    TreeArr(int n) : bitArr(n) {}

    void update(int place, int value)
    {
        for (int i = place; i < (int)bitArr.size(); i += lowbit(i)) {
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

int cnt(const string& x)
{
    TreeArr arr(28);
    i64     ans = 0;
    for (char i = x.length() - 1; i >= 0; i--) {
        arr.update(x[i] - 'a' + 1, 1);
        ans += arr.query(x[i] - 'a');
    }
    return ans;
}

string gene(int idx)
{
    if (idx == 0) {
        return "";
    }
    idx--;  // 转换为0-based索引
    int cur = idx % 26;
    return gene(idx / 26) + string(1, 'a' + cur);
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
    int v;
    cin >> v;
    vector<string> dp(10005);
    dp[1]    = "ba";
    dp[1300] = "zzyyxxwwvvuuttssrrqqppoonnmmllkkjjiihhggffeeddccbbaa";
    dp[2925] = "zzzyyyxxxwwwvvvuuutttsssrrrqqqpppooonnnmmmlllkkkjjjiiihhhgggfffeeedddcccbbbaaa";
    dp[5200] =
        "zzzzyyyyxxxxwwwwvvvvuuuuttttssssrrrrqqqqppppoooonnnnmmmmllllkkkkjjjjiiiihhhhggggffffeeeeddddccccbbbbaaaa";
    int i = 1;
    if (v >= 1300) {
        i = 1;
    } else if (v >= 2925) {
        i = 1300;
    } else {
        i = 2925;
    }
    vector<string>* obj = new vector<string>(2);
    for (i = 1; i <= v; i++) {
        string now = dp[i];
        for (char i = 'a'; i <= 'z'; i++) {
            string nextp1 = i + now;
            if (dp[cnt(nextp1)] == "" || dp[cnt(nextp1)].length() > nextp1.length()
                || (dp[cnt(nextp1)].length() == nextp1.length() && dp[cnt(nextp1)] > nextp1)) {
                dp[cnt(nextp1)] = nextp1;
            }
            string nextp2 = now + i;
            if (dp[cnt(nextp2)] == "" || dp[cnt(nextp2)].length() > nextp2.length()
                || (dp[cnt(nextp2)].length() == nextp2.length() && dp[cnt(nextp2)] > nextp2)) {
                dp[cnt(nextp2)] = nextp2;
            }
        }
    }
    cout << dp[v];
    return 0;
}