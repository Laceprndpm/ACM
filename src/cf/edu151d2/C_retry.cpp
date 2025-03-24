#include <iostream>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int m;
    cin >> m;
    string l;
    string r;
    cin >> l >> r;
    vector<int>          arr(m);
    vector<vector<bool>> appear(m, vector<bool>(10));
    for (int i = 0; i < m; i++) {
        arr[i] = r[i] - l[i] + 1;
        for (int j = l[i] - '0'; j <= r[i] - '0'; j++) {
            appear[i][j] = true;
        }
    }
    int pointerArr = 0;
    for (const char& c : s) {
        if (appear[pointerArr][c - '0'] == true) {
            appear[pointerArr][c - '0'] = false;
            arr[pointerArr]--;
            if (arr[pointerArr] == 0) {
                pointerArr++;
                if (pointerArr == m) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
    return;
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