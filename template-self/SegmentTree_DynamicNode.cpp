
class SegmentTree {
private:
    vector<i64> left, right;
    vector<i64> leftSon, rightSon;
    i64         cnt = 1;
    vector<i64> val;
    i64         __n;

    void update(i64 root, i64 idx, i64 value)
    {
        i64 l = left[root], r = right[root];
        if (l == r) {
            val[root] = value;
            return;
        }
        i64 mid = (l + r) >> 1;
        if (idx <= mid) {
            if (leftSon[root] == 0) {
                leftSon[root] = ++cnt;
                leftSon.emplace_back(0);
                rightSon.emplace_back(0);
                val.emplace_back(0);
                left.emplace_back(l);
                right.emplace_back(mid);
            }
            update(leftSon[root], idx, value);
        } else {
            if (rightSon[root] == 0) {
                rightSon[root] = ++cnt;
                rightSon.emplace_back(0);
                leftSon.emplace_back(0);
                val.emplace_back(0);
                left.emplace_back(mid + 1);
                right.emplace_back(r);
            }
            update(rightSon[root], idx, value);
        }
        val[root] = (val[leftSon[root]] + val[rightSon[root]]);
    }

    i64 quary(i64 root, i64 start, i64 end)
    {
        if (val[root] == 0) {
            return 0;
        }
        if (start > right[root] || end < left[root]) {
            return 0;
        }
        i64 l = left[root], r = right[root];
        if (start <= l && r <= end) {
            return val[root];
        }
        i64 sum = 0;
        if (leftSon[root] != 0) {
            sum += quary(leftSon[root], start, end);
        }

        if (rightSon[root] != 0) {
            sum += quary(rightSon[root], start, end);
        }
        return sum;
    }

public:
    SegmentTree(i64 n) : left(2), right(2), leftSon(2, 0), rightSon(2, 0), val(2, 0), __n(n)
    {
        left[cnt]  = 1;
        right[cnt] = n;
    }

    void update(i64 idx, i64 value)
    {
        if (idx > __n) {
            perror("Index out of bound.(SegmentTree->update)");
            throw exception();
        }
        update(1, idx, value);
    }

    i64 quary(i64 l, i64 r)
    {
        if (l > r) {
            perror("\"l\" could not larger than \"r\".(SegmentTree->quary)");
            throw exception();
        }
        if (l < 1 || r > __n) {
            perror("Index out of bound.(SegmentTree->quary)");
            throw exception();
        }
        return quary(1, l, r);
    }
};