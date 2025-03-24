#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> real2virtual(n + 1);
    vector<int> virtual2real(n + 1);
    vector<int> virtual2pigeon(n + 1);
    for (int i = 1; i <= n; i++) {
        virtual2pigeon[i] = i;
        real2virtual[i]   = i;
        virtual2real[i]   = i;
    }
    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        int a, b;
        switch (op) {
            case 1: {
                cin >> a >> b;
                virtual2pigeon[a] = virtual2real[b];
                break;
            }
            case 2: {
                cin >> a >> b;
                a = virtual2real[a], b = virtual2real[b];
                swap(real2virtual[a], real2virtual[b]);
                swap(virtual2real[real2virtual[a]], virtual2real[real2virtual[b]]);
                break;
            }
            case 3: {
                cin >> a;
                cout << real2virtual[virtual2pigeon[a]] << '\n';
                break;
            }
            default:
                throw runtime_error("what???");
        }
    }
    return 0;
}