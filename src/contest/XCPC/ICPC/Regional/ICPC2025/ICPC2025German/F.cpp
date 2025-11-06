#include <bits/stdc++.h>

#include <vector>
using namespace std;
int            h, w;
vector<string> board;

bool check(int e)
{
    auto tmp = board;  // 深拷贝，防止修改原始board
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (tmp[i][j] == '#') {
                for (int di = 0; di < e; ++di) {
                    for (int dj = 0; dj < e; ++dj) {
                        if (i + di < h && j + dj < w) {
                            if (tmp[i + di][j + dj] != '#') {
                                return 0;
                            } else {
                                tmp[i + di][j + dj] = '.';
                            }
                        } else {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> h >> w;
    board.resize(h);
    for (int i = 0; i < h; ++i) {
        cin >> board[i];
    }
    int         bound = min(h, w);
    vector<int> nok(bound + 1);
    int         ans = 1;
    for (int i = 2; i <= bound; i++) {
        if (nok[i]) continue;
        int res = check(i);
        if (!res) {
            for (int j = 1; i * j <= bound; j++) {
                nok[i * j] = 1;
            }
        } else {
            ans = i;
        }
    }
    cout << ans << '\n';
    return 0;
}
