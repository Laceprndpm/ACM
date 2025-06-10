#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct Phi {
    vector<int> phi;
    vector<int> p;

    void init(int n)
    {
        int total = 0;
        phi[1]    = 1;
        for (int i = 2; i <= n; i++) {
            if (!phi[i]) {
                p[total++] = i;
                phi[i]     = i - 1;
            }
            for (int j = 0; j < total && i * p[j] <= n; j++) {
                if (i % p[j] == 0) {
                    phi[i * p[j]] = phi[i] * p[j];
                    break;
                } else {
                    phi[i * p[j]] = phi[i] * (p[j] - 1);
                }
            }
        }
    }
};

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif

    return 0;
}