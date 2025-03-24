#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

// 010
// 0x1
//
//
// 010
// x01
//
// 0010
// x001
//
// x1
// 10
//
signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    string upper;
    string lower;
    cin >> upper;
    cin >> lower;
    int cnt1   = count(upper.begin(), upper.end(), '1') + count(lower.begin(), lower.end(), '1');
    int i      = -1;
    int status = 1;
    int cnt    = 0;
    while (++i < n) {
        if (status == 1) {
            if (upper[i] == '1' && lower[i - 1] == '1') {
                status       = 3;
                upper[i]     = '0';
                lower[i - 1] = '0';
                cnt++;
                continue;
            }
            if (lower[i - 1] == '1') {
                status       = 2;
                lower[i - 1] = '0';
                i--;
                continue;
            }
            upper[i] = '0';
            continue;
        }
        if (status == 2) {
            if (upper[i - 1] == '1' && lower[i] == '1') {
                status       = 4;
                upper[i - 1] = '0';
                lower[i]     = '0';
                cnt++;
                continue;
            }
            if (upper[i - 1] == '1') {
                status       = 1;
                upper[i - 1] = '0';
                i--;
                continue;
            }
            lower[i] = '0';
            continue;
        }
        if (status == 3) {
            if (upper[i] == '1' && lower[i - 1] == '1') {
                lower[i - 1] = '0';
                status       = 2;
                i--;
                continue;
            }
            if (upper[i] == '1') {
                upper[i] = '0';
                status   = 1;
            }
            if (lower[i - 1] == '1') {
                lower[i - 1] = '0';
                status       = 2;
                i--;
            }
            continue;
        }
        if (status == 4) {
            if (upper[i - 1] == '1' && lower[i] == '1') {
                upper[i - 1] = '0';
                status       = 1;
                i--;
                continue;
            }
            if (upper[i - 1] == '1') {
                upper[i - 1] = '0';
                status       = 1;
                i--;
            }
            if (lower[i] == '1') {
                lower[i] = '0';
                status   = 2;
            }
            continue;
        }
    }
    cout << cnt1 - cnt << '\n';
    return 0;
}