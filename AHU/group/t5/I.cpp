#include <bits/stdc++.h>

#include <vector>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
int         last = 0;

template <class T>
class PresidentTree {
    using NodeIndex = int;

    struct Node {
        int       val;
        NodeIndex l, r;

        Node(int val = 0) : val{val}, l{0}, r{0} {}
    };

    std::vector<Node>      t;
    std::vector<NodeIndex> root;
    const T                Start, Last;

    // 新增：记录每个位置的前一个相同元素出现的位置
    std::vector<int> prev;

    NodeIndex newNode(int val = 0)
    {
        t.push_back(val);
        return (int)t.size() - 1;
    }

    void up(NodeIndex i) { t[i].val = t[t[i].l].val + t[t[i].r].val; }

    NodeIndex clone(NodeIndex p)
    {
        if (p == 0) {
            p = newNode();
            return p;
        }
        NodeIndex np = newNode();
        t[np]        = t[p];
        return np;
    }

    void modify(NodeIndex &p, T l, T r, T x, int val)
    {
        p = clone(p);
        if (l == r) {
            t[p].val += val;
            return;
        }
        T mid = (l + r) >> 1;
        if (x <= mid)
            modify(t[p].l, l, mid, x, val);
        else
            modify(t[p].r, mid + 1, r, x, val);
        up(p);
    }

    constexpr int getRange(NodeIndex x, T l, T r, T tl, T tr)
    {
        if (tl > r || tr < l) return 0;
        if (tl <= l && r <= tr) {
            return t[x].val;
        }
        T mid = (l + r) >> 1;
        return getRange(t[x].l, l, mid, tl, tr) + getRange(t[x].r, mid + 1, r, tl, tr);
    }

public:
    PresidentTree(const std::vector<T> &a, T min, T max)
        : t(1), root(a.size() + 2), Start(min), Last(max), prev(a.size() + 1)
    {
        t.reserve(a.size() * std::__lg(a.size() * 2));

        // 初始化 prev 数组
        std::unordered_map<T, int> lastPos;
        for (int i = 1; i < (int)a.size(); i++) {
            if (lastPos.count(a[i])) {
                prev[i] = lastPos[a[i]];
            } else {
                prev[i] = 0;  // 第一次出现
            }
            lastPos[a[i]] = i;
        }

        // 构建主席树
        root[0] = newNode();
        for (int i = 1; i < (int)a.size(); i++) {
            if (t.capacity() <= t.size() + 64) {
                t.reserve(std::max(2 * t.capacity(), t.capacity() + 64));
            }

            // 先复制上一个版本
            root[i] = root[i - 1];

            // 在当前位置添加标记
            modify(root[i], Start, Last, i, 1);

            // 如果这个元素之前出现过，在之前出现的位置删除标记
            if (prev[i] != 0) {
                modify(root[i], Start, Last, prev[i], -1);
            }
        }
    }

    // 新增：查询区间[l, r]内不同元素的个数
    constexpr int getDistinctCount(int l, int r)
    {
        // 查询区间[l, r]内第一次出现（即标记为1）的元素个数
        return getRange(root[r], Start, Last, l, r);
    }
};

void Echo2()
{
    /*
    区间mex和区间元素种类做差
    */
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> mp;

    vector<int> cp(a.begin() + 1, a.end());
    sort(cp.begin(), cp.end());
    cp.erase(unique(cp.begin(), cp.end()), cp.end());
    last = 0;
    for (int i : cp) {
        if (i == last + 1) {
            last++;
        } else {
            break;
        }
    }
    mp.resize(last + 2);
    for (int i = 1; i <= n; i++) {
        if (a[i] <= last) mp[a[i]].push_back(i);
    }
    PresidentTree<int> tr(a, 1, n);
    int                ans    = -inf;
    int                edcost = 0;
    for (int i = 1; i <= min(n + 1, m + 1); i++) {
        if (!mp[i].empty()) {
            mp[i].push_back(n + 1);
            int k   = mp[i].size();
            int lst = 1;
            for (int j = 0; j < k; j++) {
                int l = lst;
                int r = mp[i][j] - 1;
                // cout << r << ' ';
                if (r - l + 1 - i > ans) {
                    ans = max(ans, tr.getDistinctCount(l, r) - i);
                }
                lst = mp[i][j] + 1;
            }
        } else {
            edcost = i;
            break;
        }
    }
    // cout << ans << ' ';
    ans = max(ans, tr.getDistinctCount(1, n) - edcost);
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--) Echo2();
}