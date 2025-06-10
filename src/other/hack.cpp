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
    // freopen(argv[1], "r", stdin);
    freopen("hack.in", "w", stdout);
    cout << "200000 200000\n";
    for (int i = 1; i <= 200000; i++) {
        cout << 536870913 << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= 200000; i++) {
        cout << 2 << ' ' << 1 << ' ' << 536870913ll * 27 - 1 << '\n';
    }
    return 0;
}