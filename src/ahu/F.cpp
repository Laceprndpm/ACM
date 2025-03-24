#include <functional>
#include <queue>
#include <set>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int         cnt = 0;
    vector<int> arr(2e8);
    arr[1] = 1;
    arr[2] = 1;
    arr[3] = 1;
    arr[5] = 1;
    arr[8] = 1;
    for (int i = 1; i <= 2e8; i++) {
        if (arr[i]) {
            arr[3 * i + 2] = 1;
            arr[5 * i + 3] = 1;
            arr[8 * i + 5] = 1;
            cnt++;
            if (cnt == 2020) {
                cout << i;
                break;
            }
        }
    }
    return 0;
}