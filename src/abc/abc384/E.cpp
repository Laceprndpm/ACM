#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

istream& operator>>(istream& in, i64& num)
{
    string s;
    in >> s;
    num      = 0;
    bool neg = (s[0] == '-');
    for (size_t i = neg; i < s.size(); ++i) {
        num = num * 10 + (s[i] - '0');
    }
    if (neg) num = -num;
    return in;
}

ostream& operator<<(ostream& out, const i64& num)
{
    if (num == 0) {
        return out << '0';
    }
    i64 temp = num;
    if (temp < 0) {
        out << '-';
        temp = -temp;
    }
    string result;
    while (temp > 0) {
        result += char('0' + temp % 10);
        temp /= 10;
    }
    reverse(result.begin(), result.end());
    return out << result;
}

struct node {
    int x, y;
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
    int h, w;
    i64 X;
    cin >> h >> w >> X;
    int p, q;
    cin >> p >> q;
    p--, q--;
    vector<vector<bool>>                     vis(h, vector<bool>(w));
    vector<vector<i64>>                      board(h, vector<i64>(w));
    function<bool(const node&, const node&)> cmp = [&](const node& a, const node& b) -> bool {
        const auto& [x1, y1] = a;
        const auto& [x2, y2] = b;
        return board[x1][y1] > board[x2][y2];
    };
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> board[i][j];
        }
    }
    i64                                               cur = 0;
    priority_queue<node, vector<node>, decltype(cmp)> pq(cmp);
    pq.push({p, q});
    vis[p][q] = true;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    do {
        const auto [x, y] = pq.top();
        pq.pop();
        cur += board[x][y];
        for (int i = 0; i < 4; i++) {
            int nx = dx[i] + x;
            int ny = dy[i] + y;
            if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
                if (!vis[nx][ny]) {
                    vis[nx][ny] = true;
                    pq.push({nx, ny});
                }
            }
        }
    } while (!pq.empty() && board[pq.top().x][pq.top().y] * X < cur);
    cout << cur << '\n';
    return 0;
}