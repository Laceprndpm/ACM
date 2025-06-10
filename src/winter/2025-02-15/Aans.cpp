#include <algorithm>
#include <cstdio>
#include <map>
#include <stack>
#define int long long

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

const int          N = (int)1e5 + 5;
int                n, m, stick[N], radius[N];
std::map<int, int> cnt;

// cnt[i] 表示长度为 i 的棍子个数
bool check(int mid)
{
    int             count = 0;
    std::stack<int> chosen;
    for (int j = m; j >= 1 && count < mid; --j) {
        if (cnt.count(2 * radius[j]) && cnt[2 * radius[j]] > 0) {
            ++count;
            cnt[2 * radius[j]]--;
            chosen.push(2 * radius[j]);
        }
    }
    if (count < mid) {
        while (!chosen.empty()) {
            cnt[chosen.top()]++;
            chosen.pop();
        }
        return false;
    }
    std::stack<int> putaside;
    for (int i = 1; i <= n; ++i) {
        if (cnt[stick[i]] > 0 && !chosen.empty() && stick[i] < chosen.top() / 2) {
            putaside.push(chosen.top());
            chosen.pop();
            putaside.push(stick[i]);
            cnt[stick[i]]--;
        }
    }
    bool op = chosen.empty();
    while (!putaside.empty()) {
        cnt[putaside.top()]++;
        putaside.pop();
    }
    while (!chosen.empty()) {
        cnt[chosen.top()]++;
        chosen.pop();
    }
    return op;
}

signed main(signed argc, char** argv)
{
// #ifndef ONLINE_JUDGE
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
    n = init(), m = init();
    for (int i = 1; i <= n; ++i)
        ++cnt[stick[i] = init()];
    std::stable_sort(stick + 1, stick + 1 + n);
    for (int j = 1; j <= m; ++j)
        radius[j] = init();
    std::stable_sort(radius + 1, radius + 1 + m);
    int l = 0, r = m;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    print(l), putchar('\n');
}