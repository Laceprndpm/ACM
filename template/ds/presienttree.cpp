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

    void modify(NodeIndex &p, T l, T r, T x)
    {
        p = clone(p);
        if (l == r) {
            t[p].val++;
            return;
        }
        T mid = (l + r) >> 1;
        if (x <= mid)
            modify(t[p].l, l, mid, x);
        else
            modify(t[p].r, mid + 1, r, x);
        up(p);
    }

    NodeIndex merge(NodeIndex x, NodeIndex y, T l, T r)
    {
        if (!x || !y) return x ? x : y;
        if (l == r) {
            t[x].val += t[y].val;
            return x;
        }
        T mid  = (l + r) >> 1;
        t[x].l = merge(t[x].l, t[y].l, l, mid);
        t[x].r = merge(t[x].r, t[y].r, mid + 1, r);
        return up(x), x;
    }

    constexpr int getRange(NodeIndex x, NodeIndex y, T l, T r, T tl, T tr)
    {
        if (tl > r || tr < l) return 0;
        if (tl <= l && r <= tr) {
            return t[y].val - t[x].val;
        }
        T mid = (l + r) >> 1;
        return getRange(t[x].l, t[y].l, l, mid, tl, tr) + getRange(t[x].r, t[y].r, mid + 1, r, tl, tr);
    }

    constexpr T getKth(NodeIndex x, NodeIndex y, T l, T r, int k)
    {
        if (l == r) return l;
        T   mid = (l + r) >> 1;
        int L   = t[t[y].l].val - t[t[x].l].val;
        return (L >= k ? getKth(t[x].l, t[y].l, l, mid, k) : getKth(t[x].r, t[y].r, mid + 1, r, k - L));
    }

public:
    PresidentTree(const std::vector<T> &a, T min, T max) : t(1), root(a.size() + 2), Start(min), Last(max)
    {
        t.reserve(a.size() * std::__lg(a.size() * 2));
        root[0] = newNode();
        for (auto i = 1U; i < a.size(); i++) {
            if (t.capacity() <= t.size() + 64) {
                t.reserve(std::max(2 * t.capacity(), t.capacity() + 64));
            }
            root[i] = root[i - 1];
            modify(root[i], Start, Last, a[i]);
        }
    }

    // 查询区间[l, r] (闭区间)
    constexpr int getRange(int l, int r, T tl, T tr) { return getRange(root[l - 1], root[r], Start, Last, tl, tr); }

    // 查询区间[l, r] (闭区间)
    constexpr T getKth(int l, int r, int k) { return getKth(root[l - 1], root[r], Start, Last, k); }
};