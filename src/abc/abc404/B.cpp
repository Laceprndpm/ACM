#include <cstdio>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    getchar();
    vector<vector<char>> s(n, vector<char>(n)), t(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s[i][j] = getchar();
        }
        getchar();
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = getchar();
        }
        getchar();
    }
    function<i64(void)> countDiff = [&](void) -> i64 {
        i64 ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i][j] != t[i][j]) {
                    ans++;
                }
            }
        }
        return ans;
    };
    function<void(void)> rotate = [&](void) -> void {
        vector<vector<char>> temp(n, vector<char>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[j][n - i - 1] = s[i][j];
            }
        }
        s = temp;
    };
    i64 ans = INF;
    for (int i = 0; i < 4; i++) {
        ans = min(ans, countDiff() + i);
        rotate();
    }
    cout << ans << '\n';
    return 0;
}