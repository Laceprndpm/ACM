#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

class SegmentTree {
private:
    vector<LL> left, right;
    vector<LL> leftSon, rightSon;
    LL         cnt = 1;
    vector<LL> val;
    LL         __n;

    void update(LL root, LL idx, LL value)
    {
        LL l = left[root], r = right[root];
        if (l == r) {
            val[root] = value;
            return;
        }
        LL mid = (l + r) >> 1;
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

    LL quary(LL root, LL start, LL end)
    {
        if (val[root] == 0) {
            return 0;
        }
        if (start > right[root] || end < left[root]) {
            return 0;
        }
        LL l = left[root], r = right[root];
        if (start <= l && r <= end) {
            return val[root];
        }
        LL sum = 0;
        if (leftSon[root] != 0) {
            sum += quary(leftSon[root], start, end);
        }

        if (rightSon[root] != 0) {
            sum += quary(rightSon[root], start, end);
        }
        return sum;
    }

public:
    SegmentTree(LL n) : left(2), right(2), leftSon(2, 0), rightSon(2, 0), val(2, 0), __n(n)
    {
        left[cnt]  = 1;
        right[cnt] = n;
    }

    void update(LL idx, LL value)
    {
        if (idx > __n) {
            perror("Index out of bound.(SegmentTree->update)");
            throw exception();
        }
        update(1, idx, value);
    }

    LL quary(LL l, LL r)
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

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    SegmentTree  A(1e9), C(1e9), G(1e9), I(1e9), K(1e9);
    vector<char> who(n + 1);
    vector<int>  x(n + 1);
    vector<int>  t(n + 1);
    set<int>     timeOperation;
    for (int i = 1; i <= n; i++) {
        cin >> who[i] >> x[i] >> t[i];
        timeOperation.insert(t[i]);
        switch (who[i]) {
            case 'A': {
                A.update(t[i], x[i]);
                break;
            }
            case 'C': {
                C.update(t[i], x[i]);
                break;
            }
            case 'G': {
                G.update(t[i], x[i]);
                break;
            }
            case 'I': {
                I.update(t[i], x[i]);
                break;
            }
            case 'K': {
                K.update(t[i], x[i]);
                break;
            }
            default: {
                cerr << "Invalid character: " << who[i] << endl;
                break;
            }
        }
    }
    // SegmentTree   Aadd(1e9);
    // map<int, int> time_add;
    // for (int curT : timeOperation) {
    //     LL atLeast = max(max(C.quary(1, curT), G.quary(1, curT)), max(I.quary(1, curT), K.quary(1, curT)));
    //     LL has     = A.quary(1, curT) + Aadd.quary(1, curT);
    //     if (atLeast > has) {
    //         Aadd.update(curT, atLeast - has);
    //     }
    //     time_add[curT] = Aadd.quary(1, curT);
    // }
    // for (int i = 1; i <= n; i++) {
    //     cout << time_add[t[i]] << '\n';
    // }
    for (int i = 1; i <= n; i++) {
        int curT    = t[i];
        LL  atLeast = max(max(C.quary(1, curT), G.quary(1, curT)), max(I.quary(1, curT), K.quary(1, curT)));
        cout << atLeast << '\n';
    }
    return 0;
}