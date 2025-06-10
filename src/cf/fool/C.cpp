#include <iostream>
#include <string>
#include <thread>
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
    string t("");
    getline(cin, s);
    int    count = 0;
    size_t pos   = s.find("tests");
    while (pos != string::npos) {
        count++;
        pos = s.find("tests", pos + 1);
    }
    cout << count << endl;
    return 0;
}