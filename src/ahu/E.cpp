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
    string s;
    cin >> s;
    string mon(s.begin(), s.begin() + 3);
    int    month;
    if (mon == "Jan")
        month = 1;
    else if (mon == "Feb")
        month = 2;
    else if (mon == "Mar")
        month = 3;
    else if (mon == "Apr")
        month = 4;
    else if (mon == "May")
        month = 5;
    else if (mon == "Jun")
        month = 6;
    else if (mon == "Jul")
        month = 7;
    else if (mon == "Aug")
        month = 8;
    else if (mon == "Sep")
        month = 9;
    else if (mon == "Oct")
        month = 10;
    else if (mon == "Nov")
        month = 11;
    else if (mon == "Dec")
        month = 12;
    else
        month = -1;  // Invalid month
    cout << month << ' ';
    if (s[3] == '0') {
        cout << s[4];
    } else {
        cout << s[3] << s[4];
    }
    return 0;
}