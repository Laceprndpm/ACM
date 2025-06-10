#include <cctype>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

char sw(char x)
{
    if (islower(x)) {
        return toupper(x);
    } else {
        return tolower(x);
    }
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
    string s;
    cin >> s;
    string               ans = "";
    int                  cnt = 0;
    vector<list<string>> buff(1000, list<string>{""});
    for (char i : s) {
        if (i == '(') {
            cnt++;
            if (buff.size() < cnt + 1) {
                buff.resize(cnt + 1, list<string>{""});
            }
        } else if (i == ')') {
            cnt--;
            if (cnt % 2 == 0) {
                buff[cnt].splice(buff[cnt].end(), buff[cnt + 1]);
            } else {
                buff[cnt].splice(buff[cnt].begin(), buff[cnt + 1]);
            }
            buff[cnt + 1] = list<string>{""};
        } else {
            if (cnt % 2)
                buff[cnt].front() = sw(i) + buff[cnt].front();
            else
                buff[cnt].back() += i;
        }
    }
    for (auto i : buff[0])
        cout << i;
    return 0;
}