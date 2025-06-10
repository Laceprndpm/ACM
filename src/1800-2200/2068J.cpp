#include <iostream>
#include <string>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class Fenwick {
private:
    vector<int> bitArr;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    Fenwick(int n) : bitArr(n) {}

    void update(int place, int value)
    {
        place++;
        for (int i = place; i < bitArr.size(); i += lowbit(i)) {
            bitArr[i] += value;
        }
    }

    int query(int place)
    {
        place++;
        int res = 0;
        for (int i = place; i; i -= lowbit(i)) {
            res += bitArr[i];
        }
        return res;
    }
};

void solve()
{
    int    n;
    string s;
    cin >> n >> s;
    // int i = 0, j = n - 1;
    // while (i < n && s[i] == 'W' && s[i + 1] == 'W') {
    //     i += 2;
    // }
    // while (j >= 0 && s[j] == 'W' && s[j - 1] == 'W') {
    //     j -= 2;
    // }
    // bool ok = true;
    // for (int k = i + 1; k < j - 1; k++) {
    //     if (s[k] == 'W') {
    //         ok = false;
    //     }
    // }
    // i = n, j = 2 * n - 1;
    // while (i < 2 * n && s[i] == 'R' && s[i + 1] == 'R') {
    //     i += 2;
    // }
    // while (j >= n && s[j] == 'R' && s[j - 1] == 'R') {
    //     j -= 2;
    // }
    // for (int k = i + 1; k < j - 1; k++) {
    //     if (s[k] == 'R') {
    //         ok = false;
    //     }
    // }
    // if (ok) {
    //     cout << "Yes\n";
    // } else {
    //     cout << "No\n";
    // }
    // (WWWW)RR(W)RRRRR(W)RRWRW(RR)|WRRWWWWWWWRWWRWWRRRR
    //
    //  int i = 0, j = 2 * n - 1;
    //  while (i < j) {
    //      if (s[i] == s[i + 1]) {
    //          i += 2;
    //          continue;
    //      }
    //      if (s[j] == s[j - 1]) {
    //          j -= 2;
    //          continue;
    //      }
    //      if (s[i] == 'R' && s[j] == 'W') {
    //          continue;
    //      }
    //      break;
    //  }
    //  if (i >= j) {
    //      cout << "Yes\n";
    //  }
    //  WRRW|WWRR
    //   00  11
    //  WWRR|WWRR
    //  0100 1101
    //  WWR|WRR
    //  010 101
    //  RWWR|WRRW
    //  0  0 1  1
    //  此时前后错位的全部被打上标记
    //  0001 1101
    //
    //  TreeArr     cnt1(2 * n + 1), cnt0(2 * n + 1);
    //  vector<int> let(2 * n, -1);
    //  for (int i = 0; i < n; i++) {
    //      if (s[i] == 'R') {
    //          let[i] = 0;
    //          cnt0.update(i, 1);
    //      }
    //  }
    //  for (int i = n; i < 2 * n; i++) {
    //      if (s[i] == 'W') {
    //          let[i] = 1;
    //          cnt1.update(i, 1);
    //      }
    //  }
    //  while (true) {
    //      map<int, int> cnt0mp;
    //      int           update = 0;
    //      for (int i = 0; i < n; i++) {
    //          if (let[i] == -1) {
    //              int cnt = cnt1.query(i);
    //              if (cnt0mp.count(cnt)) {
    //                  cnt0.update(cnt0mp[cnt], 1);
    //                  cnt1.update(i, 1);
    //                  let[cnt0mp[cnt]] = 0;
    //                  let[i]           = 1;
    //                  update           = 1;
    //                  break;
    //              }
    //              if (cnt0mp.count(cnt0.query(i)) == 0) cnt0mp[cnt0.query(i)] = i;
    //          }
    //      }
    //      cnt0mp.clear();
    //      for (int i = n; i < 2 * n; i++) {
    //          if (let[i] == -1) {
    //              int cnt = cnt1.query(i);
    //              if (cnt0mp.count(cnt)) {
    //                  cnt0.update(cnt0mp[cnt], 1);
    //                  cnt1.update(i, 1);
    //                  let[cnt0mp[cnt]] = 0;
    //                  let[i]           = 1;
    //                  update           = 1;
    //                  break;
    //              }
    //              if (cnt0mp.count(cnt0.query(i)) == 0) cnt0mp[cnt0.query(i)] = i;
    //          }
    //      }
    //      if (!update) {
    //          break;
    //      }
    //  }
    //  for (int i = 0; i < 2 * n; i++) {
    //      if (let[i] == -1) {
    //          cout << "No\n";
    //          return;
    //      }
    //  }
    //  cout << "Yes\n";
    int  cntSame = 0;
    bool ok      = true;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') {
            cntSame++;
        }
    }
    if (cntSame % 2) ok = false;
    for (int i = 0; i < cntSame / 2; i++) {
        if (s[i] != 'W') {
            ok = false;
        }
    }
    cntSame = 0;
    for (int i = n; i < n * 2; i++) {
        if (s[i] == 'R') {
            cntSame++;
        }
    }
    if (cntSame % 2) ok = false;
    for (int i = 0; i < cntSame / 2; i++) {
        if (s[2 * n - i - 1] != 'R') {
            ok = false;
        }
    }
    if (ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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