#include <bits/stdc++.h>

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

void print(int x)
{
    if (x < 0)
        x = -x, putchar('-');
    if (x / 10)
        print(x / 10);
    putchar(x % 10 + '0');
}

const int M    = (int)1e2 + 5;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};

struct Node {
    int x = 0, y = 0, z = 0;
} lower[26], upper[26];

std::vector<std::pair<int, int>> G[M * M * M];

int node(int i, int j, int k)
{
    return (i - 1) * M * M + (j - 1) * M + k;
}

void debug(int node)
{
    int k = node % M;
    node /= M;
    int j = node % M + 1;
    node /= M;
    int i = node % M + 1;
    printf("(%d %d %d) node!\n", i, j, k);
}

void add(int u, int v, int w)
{
    G[u].push_back(std::make_pair(v, w));
}

int  dis[M * M * M];
bool inq[M * M * M];

signed main(signed argc, char** argv)
{
    // #ifndef ONLINE_JUDGE
    //     freopen(argv[1], "r", stdin);
    //     freopen(argv[2], "w", stdout);
    // #endif
    int n     = init();
    int Start = 0, End = M * M * M - 1;
    for (int i = 1; i <= n; ++i) {
        int r = init(), c = init();
        for (int j = 1; j <= r; ++j)
            for (int k = 1; k <= c; ++k) {
                if (i == 1)
                    add(Start, node(i, j, k), 0);
                if (i == n)
                    add(node(i, j, k), End, 0);
                char ch = getchar();
                while (isspace(ch))
                    ch = getchar();
                if (ch == '.')
                    for (int d = 0; d < 4; ++d) {
                        int nj = j + dx[d], nk = k + dy[d];
                        if (nj < 1 || nj > r || nk < 1 || nk > c)
                            continue;
                        add(node(i, j, k), node(i, nj, nk), 0);
                    }
                else if (ch == '#')
                    for (int d = 0; d < 4; ++d) {
                        int nj = j + dx[d], nk = k + dy[d];
                        if (nj < 1 || nj > r || nk < 1 || nk > c)
                            continue;
                        add(node(i, j, k), node(i, nj, nk), 1);
                    }
                else {
                    for (int d = 0; d < 4; ++d) {
                        int nj = j + dx[d], nk = k + dy[d];
                        if (nj < 1 || nj > r || nk < 1 || nk > c)
                            continue;
                        add(node(i, j, k), node(i, nj, nk), 0);
                    }
                    if ('a' <= ch && ch <= 'z') {
                        if (lower[ch - 'a'].x)
                            add(node(i, j, k), node(lower[ch - 'a'].x, lower[ch - 'a'].y, lower[ch - 'a'].z), 0),
                                add(node(lower[ch - 'a'].x, lower[ch - 'a'].y, lower[ch - 'a'].z), node(i, j, k), 0);
                        else
                            lower[ch - 'a'].x = i, lower[ch - 'a'].y = j, lower[ch - 'a'].z = k;
                    } else {
                        if (upper[ch - 'A'].x)
                            add(node(i, j, k), node(upper[ch - 'A'].x, upper[ch - 'A'].y, upper[ch - 'A'].z), 0),
                                add(node(upper[ch - 'A'].x, upper[ch - 'A'].y, upper[ch - 'A'].z), node(i, j, k), 0);
                        else
                            upper[ch - 'A'].x = i, upper[ch - 'A'].y = j, upper[ch - 'A'].z = k;
                    }
                }
            }
    }
    std::deque<int> Q;
    memset(dis, 0x3f, sizeof(dis));
    dis[Start] = 0;
    Q.push_front(Start);
    inq[Start] = true;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        inq[u] = false;
        for (std::vector<std::pair<int, int>>::iterator it = G[u].begin(); it != G[u].end(); ++it) {
            int v = (*it).first;
            // debug(v);
            if (dis[v] > dis[u] + (*it).second) {
                // printf("enter successful\n");
                dis[v] = dis[u] + (*it).second;
                if (v == End) {
                    print(dis[v]), putchar('\n');
                    // debug(v);
                    // for (int ii = 1; ii <= 3; ii++) {
                    //     for (int jj = 1; jj <= 10; jj++) {
                    //         printf("%d ", dis[node(1, ii, jj)]);
                    //     }
                    //     putchar('\n');
                    // }
                    return 0;
                }
                // if (inq[v])
                //     continue;
                if ((*it).second)
                    Q.push_back(v), inq[v] = true;
                else
                    Q.push_front(v), inq[v] = true;
            }
        }
    }
    // for (int ii = 1; ii <= 3; ii++) {
    //     for (int jj = 1; jj <= 10; jj++) {
    //         printf("%d ", dis[node(1, ii, jj)]);
    //     }
    //     putchar('\n');
    // }
    puts("No Solution");
}