#include <deque>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣶⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⢀⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⣿⣿⣟⡿⣿⣿⣿⣿⡿⡁⣿⣿⣿⠀⠀⠀⠀⣀⣤⡾⣦⣄⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣀⣴⣾⠋⠉⣻⡷⢦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠃⢽⣿⣿⠿⢻⠏⠑⢀⣿⣿⣿⣀⣠⡶⠋⢹⣷⣄⢠⣿⣿⡶⣤⡀⠀⠀⠀
// ⠀⠀⣀⣴⣾⢫⣿⡿⠀⣾⣿⠇⠀⣼⡟⠛⠛⣻⣿⣧⣀⣴⣶⣾⣿⣿⣷⣶⣄⣰⡟⣻⣿⡟⠉⣿⣷⡀⠘⣿⣿⠀⠙⢿⣇⢼⣿⣷⢦⣄
// ⣴⡞⢹⣿⡿⣸⠟⠀⠀⣿⠏⠀⢸⣿⡟⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣿⣿⡇⠀⠻⣿⡇⠀⠈⢻⠀⠀⠀⠛⠌⠻⣿⡠⣿
// ⣿⡏⡿⠏⠀⠁⠀⠀⠀⠃⠀⠀⠸⡿⠀⠀⢸⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣙⣿⠁⠀⠀⠹⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⠙
// ⠋⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⢘⠃⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠸⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⠛⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⣰⡀⢀⡀⣻⣄⡀⢀⣠⣴⣿⣿⣿⠃⢠⣿⣿⣿⣿⣿⣿⣿⣿⡆⠹⣿⣿⣿⣶⣄⡀⢀⣰⣏⣀⣀⣠⣇⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠈⠉⠛⠋⠁⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠈⠙⠛⠛⠉⠉⠛⠀⠀⠀⠀⠀⠀⠀⠀
void solve()
{
    i64 n, k;
    cin >> n >> k;
    vector<i64> arr(n + 1);
    for (int i = n; i >= 1; i--) {
        cin >> arr[i];
    }
    deque<pair<i64, i64>> q_idx_size;
    i64                   curVal = 0;
    i64                   cnt    = 0;
    i64                   num    = 0;
    for (int i = 1; i <= n; i++) {
        while (!q_idx_size.empty() && i - q_idx_size.front().first >= k) {
            num -= q_idx_size.front().second;
            q_idx_size.pop_front();
        }
        if (curVal < arr[i]) {
            pair<i64, i64> cur;
            i64            nowK = min(k, n - i + 1);
            cur.first           = i;
            i64 curNum          = (arr[i] - curVal + nowK - 1) / nowK;
            cur.second          = curNum;
            q_idx_size.push_back(cur);
            curVal += curNum * min(k, n - i + 1);
            cnt += curNum;
            num += curNum;
        }
        curVal -= num;
    }
    cout << cnt << '\n';
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

    solve();
    return 0;
}