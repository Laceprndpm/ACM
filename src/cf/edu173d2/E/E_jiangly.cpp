#include <bits/stdc++.h>

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

void solve()
{

    int n, m;
    std::cin >> n >> m;

    std::vector A(n, std::vector<int>(m));
    std::vector B(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> B[i][j];
        }
    }

    for (int d = 0; d < 30; d++) {
        std::vector      x(n, std::vector<std::array<int, 2>>(m));
        std::vector<int> R(n), C(m);
        std::queue<int>  q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int c      = B[i][j] >> d & 1;
                x[i][j][c] = 1;
                if (c == 0 && ++R[i] == m) {
                    q.push(i);
                }
                if (c == 1 && ++C[j] == n) {
                    q.push(n + j);
                }
            }
        }
        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (i < n) {
                for (int j = 0; j < m; j++) {
                    if (!x[i][j][1]) {
                        x[i][j][1] = 1;
                        if (++C[j] == n) {
                            q.push(n + j);
                        }
                    }
                }
            } else {
                i -= n;
                for (int j = 0; j < n; j++) {
                    if (!x[j][i][0]) {
                        x[j][i][0] = 1;
                        if (++R[j] == m) {
                            q.push(j);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!x[i][j][A[i][j] >> d & 1]) {
                    std::cout << "No\n";
                    return;
                }
            }
        }
    }

    std::cout << "Yes\n";
}

int main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}