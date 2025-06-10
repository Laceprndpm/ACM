#include <algorithm>
#include <iostream>
#include <vector>
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
    int n;
    cin >> n;
    vector<int> toy(n);
    vector<int> box(n - 1);
    for (int i = 0; i < n; i++) {
        cin >> toy[i];
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> box[i];
    }
    ranges::sort(toy), ranges::sort(box);
    int l = n - 1, r = n - 2;
    int re = -1;
    while (l >= 0 && r >= 0) {
        if (toy[l] <= box[r]) {
            l--, r--;
        } else {
            if (re == -1)
                re = l;
            else {
                cout << -1 << '\n';
                return 0;
            }
            l--;
        }
    }
    if (re == -1) {
        re = 0;
    }
    cout << toy[re];
    return 0;
}