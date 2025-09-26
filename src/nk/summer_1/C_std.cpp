#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long  LL;
typedef __int128_t LLL;  // 用 __int128 做分数比较，避免溢出

// 常量定义
#define N 1000 + 5
#define Q 1000000 + 5
#define M 2097152 + 5  // 线段树大小 (2^21)

// 宏：左右儿子
#define ls(x) x << 1
#define rs(x) x << 1 | 1

// 输入数据
int                  n, q, A[N], T[N], L[N], R[N], OrdL[N], OrdR[N], W[N], D[Q], Ord[Q];
LL                   SumL[N], SumR[N], Ans[Q];
vector<pair<LL, LL>> Tree[M];  // 每个线段树节点存一堆直线 (k, b)

// 表示线性函数 y = kx + b 在 [lhs, rhs] 区间有效
struct Line {
    int lhs, rhs;  // 区间范围（查询的下标范围）
    LL  k, b;      // 斜率、截距

    Line() {}

    Line(int lhs, int rhs, LL k, LL b) : lhs(lhs), rhs(rhs), k(k), b(b) {}

    bool operator<(const Line& obj) const
    {
        // 按斜率升序，如果斜率相同则截距大的优先
        return make_pair(k, -b) < make_pair(obj.k, -obj.b);
    }
};

vector<Line> lines;

// 有理数 fz/fm，保证严格比较 (用于求直线交点)
struct Frac {
    LL fz, fm;

    Frac() : Frac(0, 1) {}

    Frac(LL fz, LL fm) : fz(fz), fm(fm) {}

    bool operator<(const Frac& obj) const
    {
        // cross multiply 比较，防止精度问题
        return LLL(fz) * obj.fm < LLL(fm) * obj.fz;
    }
};

// 查询离散化：在 D[1..q] 中找到 >= d 的最小位置
int Rank(int d)
{
    int l = 1, r = q + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (D[Ord[mid]] < d)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

// 往线段树区间 [s,t] 插入一条直线
void Add(int x, int l, int r, int s, int t, LL k, LL b)
{
    if (l == s && r == t) {
        Tree[x].emplace_back(make_pair(k, b));
        return;
    }
    int mid = (l + r) >> 1;
    if (t <= mid)
        Add(ls(x), l, mid, s, t, k, b);
    else if (s > mid)
        Add(rs(x), mid + 1, r, s, t, k, b);
    else {
        Add(ls(x), l, mid, s, mid, k, b);
        Add(rs(x), mid + 1, r, mid + 1, t, k, b);
    }
}

// 求两条直线交点横坐标 (x = (b2 - b1)/(k1 - k2))
inline Frac GetX(const pair<LL, LL>& lhs, const pair<LL, LL>& rhs)
{
    return Frac(lhs.second - rhs.second, rhs.first - lhs.first);
}

// 线段树查询：在 [l,r] 区间处理节点的所有直线，并下推
void Query(int x, int l, int r)
{
    vector<Frac>         X;  // 交点横坐标
    vector<pair<LL, LL>> S;  // 维护凸壳上的直线集合

    // 构造上凸壳，类似斜率优化 DP 的套路
    for (const pair<LL, LL>& p : Tree[x]) {
        if (S.empty()) {
            S.emplace_back(p);
        } else {
            if (S.back().first == p.first)  // 相同斜率，保留较优
                continue;
            for (; S.size() > 1 && GetX(S.back(), p) < X.back();) {
                S.pop_back();
                X.pop_back();
            }
            X.emplace_back(GetX(S.back(), p));
            S.emplace_back(p);
        }
    }

    // 扫描每个查询点，找到对应区间的最优直线
    if (!S.empty()) {
        for (int i = l, j = 0; i <= r; i++) {
            for (; j < (int)X.size() && X[j] < Frac(D[Ord[i]], 1); j++);
            Ans[Ord[i]] = max(Ans[Ord[i]], S[j].first * D[Ord[i]] + S[j].second);
        }
    }

    if (l == r) return;
    int mid = (l + r) >> 1;
    Query(ls(x), l, mid);
    Query(rs(x), mid + 1, r);
}

int main()
{
    // 输入 n,q
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        T[i] = A[i];  // T 用于排序离散化
    }
    for (int i = 1; i < n; i++) {
        scanf("%d", W + i);     // 边权
        OrdL[i] = OrdR[i] = i;  // 预处理排序序列
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d", D + i);  // 查询的 d
        Ord[i] = i;          // 保留查询原序
    }

    // 排序与预处理
    sort(T + 1, T + n + 1);
    sort(Ord + 1, Ord + q + 1, [](int u, int v) { return D[u] < D[v]; });
    sort(OrdL + 1, OrdL + n, [](int u, int v) { return min(A[u], A[u + 1]) < min(A[v], A[v + 1]); });
    sort(OrdR + 1, OrdR + n, [](int u, int v) { return max(A[u], A[u + 1]) < max(A[v], A[v + 1]); });

    // 前缀和
    for (int i = 1; i < n; i++) {
        SumL[i] = SumL[i - 1] + W[OrdL[i]];
        SumR[i] = SumR[i - 1] + W[OrdR[i]];
        L[i]    = min(A[OrdL[i]], A[OrdL[i] + 1]);
        R[i]    = max(A[OrdR[i]], A[OrdR[i] + 1]);
    }

    // 枚举左端点，生成直线集合
    for (int i = 1; i <= n; i++) {
        LL base_ans = 0;
        for (int u = 0, v = 0, ptr = i; ptr <= n; ptr++) {
            for (; u < n - 1 && L[u + 1] <= T[ptr]; u++);
            for (; v < n - 1 && R[v + 1] <= T[ptr]; v++);
            int mn_d = T[ptr] - T[i] + 1;
            int mx_d = ptr < n ? T[ptr + 1] - T[i] : D[Ord[q]];
            if (mn_d > mx_d) continue;

            LL k     = SumL[u] - SumR[v];          // 直线斜率
            LL b     = base_ans - k * (mn_d - 1);  // 截距
            base_ans = k * mx_d + b;

            if (k < 0) {  // 保证非负
                b += k * (mn_d - 1), k = 0;
            }
            int lhs = Rank(mn_d), rhs = (k == 0 ? q : Rank(mx_d + 1) - 1);
            if (lhs <= rhs) lines.emplace_back(lhs, rhs, k, b);
        }
    }

    // 枚举右端点，生成直线集合（对称处理）
    for (int j = n; j; j--) {
        LL base_ans = 0;
        for (int u = n - 1, v = n - 1, ptr = j; ptr >= 1; ptr--) {
            for (; u > 0 && L[u] >= T[ptr]; u--);
            for (; v > 0 && R[v] >= T[ptr]; v--);
            int mn_d = T[j] - T[ptr] + 1;
            int mx_d = ptr > 1 ? T[j] - T[ptr - 1] : D[Ord[q]];
            if (mn_d > mx_d) continue;

            LL k     = SumL[u] - SumR[v];
            LL b     = base_ans - k * (mn_d - 1);
            base_ans = k * mx_d + b;

            if (k < 0) b += k * (mn_d - 1), k = 0;
            int lhs = Rank(mn_d), rhs = (k == 0 ? q : Rank(mx_d + 1) - 1);
            if (lhs <= rhs) lines.emplace_back(lhs, rhs, k, b);
        }
    }

    // 直线按斜率排序，插入到线段树
    sort(lines.begin(), lines.end());
    for (const Line& line : lines) Add(1, 1, q, line.lhs, line.rhs, line.k, line.b);

    // 在线段树上查询，处理所有 D[i]
    Query(1, 1, q);

    // 输出答案
    for (int i = 1; i <= q; i++) printf("%lld\n", Ans[i]);
    return 0;
}
