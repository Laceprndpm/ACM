#include <algorithm>
#include <format>
#include <iostream>
#include <map>
#include <set>
#include <string>
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"
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
    map<string, int> st;
    int              ans  = 0;
    int              last = 0;
    for (int i = 1; i <= 110000; i++) {

        string s = to_string(i) + to_string(i + 1);
        sort(s.begin(), s.end());
        if (st.count(s) != 0) {
            cout << i << '\n';
        } else {
            ans++;
        }
        st.insert({s, i});

        // if (i % 100 == 0) {
        //     cout << format("{}:", i);
        //     if (ans - last == 90) {
        //         cout << RED;
        //         cout << ans - last << '\n';
        //         cout << RESET;
        //     } else if (ans - last == 99) {
        //         cout << GREEN;
        //         cout << ans - last << '\n';
        //         cout << RESET;
        //     } else {
        //         cout << ans - last << '\n';
        //     }
        //     last = ans;
        // }
    }
    return 0;
}