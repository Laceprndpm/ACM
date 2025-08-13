template <typename T>
struct Fenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v)
    {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }

    int select(const T &k)
    {
        int x = 0;
        T   cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

template <class T>
struct RangeFenwick {
    int        n;
    Fenwick<T> d1, d2;

    RangeFenwick(int n_) : n(n_), d1(n_), d2(n_) {}

    void add(i64 k, T v)
    {
        T v1 = k * v;
        d1.add(k, v), d2.add(k, v1);
        // 在diff的k位置+v
    }

    void add(i64 l, i64 r, T v)
    {
        add(l, v), add(r, -v);  // 将区间加差分为两个前缀加
    }

    T getsum(i64 x)
    {
        return x * d1.sum(x) - d2.sum(x);
    }

    T getsum(i64 l, i64 r)
    {
        return getsum(r) - getsum(l);
    }
};
