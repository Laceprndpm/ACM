template <class Info>
struct SegmentTree {
    vector<i64>  leftSon, rightSon;
    vector<Info> info;
    i64          cnt = 0;
    i64          n;

    void pull(int p)
    {
        info[p] = info[leftSon[p]] + info[rightSon[p]];
    }

    int newnode()
    {
        leftSon.emplace_back(0);
        rightSon.emplace_back(0);
        info.emplace_back(Info());
        return ++cnt;
    }

    void modify(i64 p, i64 l, i64 r, i64 x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        i64 mid = (r - l) / 2 + l;
        if (x < mid) {
            if (leftSon[p] == 0) {
                leftSon[p] = newnode();
            }
            modify(leftSon[p], l, mid, x, v);
        } else {
            if (rightSon[p] == 0) {
                rightSon[p] = newnode();
            }
            modify(rightSon[p], mid, r, x, v);
        }
        pull(p);
    }

    Info rangeQuery(i64 p, i64 l, i64 r, i64 x, i64 y)
    {

        if (l >= y || r <= x || p == 0) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        i64 m = (r - l) / 2 + l;
        return rangeQuery(leftSon[p], l, m, x, y) + rangeQuery(rightSon[p], m, r, x, y);
    }

    SegmentTree(i64 n_) : n(n_)
    {
        leftSon.assign(2, 0);
        rightSon.assign(2, 0);
        info.assign(2, Info());
    }

    void modify(i64 x, const Info &value)
    {
        modify(1, 0, n, x, value);
    }

    Info rangeQuery(i64 l, i64 r)
    {
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Info {
    i64 num = 0;
};

Info operator+(const Info &a, const Info &b)
{
    return {a.num + b.num};
}
