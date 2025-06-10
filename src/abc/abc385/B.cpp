#include <iostream>
#include <set>
#include <utility>
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
    int h, w;
    int x, y;
    cin >> h >> w;
    cin >> x >> y;
    x--, y--;
    vector<string> bd(h);
    for (string& i : bd) {
        cin >> i;
    }
    string cmd;
    cin >> cmd;
    set<pair<int, int>> vis;
    for (char i : cmd) {
        switch (i) {
            case 'L':
                if (y - 1 >= 0 && bd[x][y - 1] != '#') {
                    y--;
                    if (bd[x][y] == '@') {
                        vis.insert({x, y});
                    }
                }
                break;
            case 'R':
                if (y + 1 < w && bd[x][y + 1] != '#') {
                    y++;
                    if (bd[x][y] == '@') {
                        vis.insert({x, y});
                    }
                }
                break;
            case 'U':
                if (x - 1 >= 0 && bd[x - 1][y] != '#') {
                    x--;
                    if (bd[x][y] == '@') {
                        vis.insert({x, y});
                    }
                }
                break;
            case 'D':
                if (x + 1 < h && bd[x + 1][y] != '#') {
                    x++;
                    if (bd[x][y] == '@') {
                        vis.insert({x, y});
                    }
                }
                break;
        }
    }
    cout << x + 1 << ' ' << y + 1 << ' ' << vis.size();
    return 0;
}