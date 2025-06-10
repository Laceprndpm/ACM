#include <functional>
#include <string>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

// 越到前面，字符越重要。。。
// 我是不是可以控制对方拿到的字符串？
// 后手大于等于前面拿的更重要，还是保证对方拿的不优重要？
// cbaabc
// bc
//
// aa
// bb
// 假如最中间两个不一样
// ccbacc
// 首先，后手必须保证最后剩两个时是一样的，否则后手必败
// 假如还剩4个
// aabb 平局
// abba 平局
// baab 平局
// aaaa 平局
// aabc Alice
// aacb Alice
// baac Alice
// caabbc
// bca
// bca
void solve()
{
    string input;
    cin >> input;
    int  sLength = input.length();
    int  i = 0, j = sLength - 1;
    bool ok = true;
    while (i < j && ok) {
        ok = false;
        while (i < j && input[i] == input[j]) {
            i++;
            j--;
            ok = true;
        }

        while (i + 2 < sLength && input[i] == input[i + 1] && input[i] == input[i + 2]) {
            i += 2;
        }
        while (j - 2 >= 0 && input[j] == input[j - 1] && input[j] == input[j - 2]) {
            j -= 2;
        }
    }
    while (i + 2 < sLength && input[i] == input[i + 1]) {
        i += 2;
    }
    while (j - 2 >= 0 && input[j] == input[j - 1]) {
        j -= 2;
    }
    if (i < j) {
        cout << "Alice" << '\n';
    } else {
        cout << "Draw" << '\n';
    }
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