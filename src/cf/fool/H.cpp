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
    int x;
    cin >> x;
    if (x == 1) {
        cout << "CODEFORCES" << '\n';
    } else if (x == 2) {
        cout << "EYE" << '\n';
    } else if (x == 3) {
        cout << "TESTING" << '\n';
    } else if (x == 4) {
        cout << "SYSTEM" << '\n';
    } else if (x == 5) {
        cout << "APRIL" << '\n';
    } else if (x == 6) {
        cout << "FOOLS" << '\n';
    } else if (x == 7) {
        cout << "YOU" << '\n';
    } else if (x == 8) {
        cout << "READ" << '\n';
    } else if (x == 9) {
        cout << "POORLY" << '\n';
    } else if (x == 10) {
        cout << "GET" << '\n';
    } else {
        cout << "EYEGLASSES" << '\n';
    }
    return 0;
}