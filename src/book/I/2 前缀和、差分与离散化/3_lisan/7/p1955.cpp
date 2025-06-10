#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;  // 记录每个树的秩（深度）
    int              count;
    int const        N;

public:
    UnionFind(int n) : parent(n), rank(n, 0), count(n), N(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 验证
    void validate(int x) {
        if (x < 0 || x >= N) {
            throw out_of_range("Expected X : 0~" + to_string(N) + " But get " + to_string(x));
        }
    }

    // 查找根节点，并进行路径压缩
    int find(int x) {
        validate(x);
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    // 合并两个集合
    void unionSets(int x, int y) {
        validate(x);
        validate(y);
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            --count;
            // 按秩合并：将秩小的树合并到秩大的树上
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;  // 增加合并后的根的秩
            }
        }
    }

    // 判断两个元素是否属于同一集合
    bool connected(int x, int y) {
        validate(x);
        validate(y);
        return find(x) == find(y);
    }

    // 联通体的数量
    int getCount(void) {
        return count;
    }

    // 打印父节点数组和秩数组（调试用）
    void print() {
        std::cout << "Parent array: ";
        for (int i = 0; i < (int)parent.size(); ++i) {
            std::cout << parent[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Rank array: ";
        for (int i = 0; i < (int)rank.size(); ++i) {
            std::cout << rank[i] << " ";
        }
        std::cout << std::endl;
    }
};

void solve(void) {
    int n;
    cin >> n;
    int         idxE  = 0;
    int         idxNE = 0;
    vector<int> iValE(n + 1), jValE(n + 1);
    vector<int> iValNE(n + 1), jValNE(n + 1);
    set<int>    uniqueVal;
    for (int i = 1; i <= n; i++) {
        int _i, _j, _k;
        cin >> _i >> _j >> _k;
        uniqueVal.insert(_i);
        uniqueVal.insert(_j);
        if (_k == 1) {
            idxE++;
            iValE[idxE] = _i;
            jValE[idxE] = _j;
        } else {
            idxNE++;
            iValNE[idxNE] = _i;
            jValNE[idxNE] = _j;
        }
    }
    int           idxVal = 0;
    map<int, int> Val2Rank;
    for (int iter : uniqueVal) {
        idxVal++;
        Val2Rank[iter] = idxVal;
    }
    UnionFind uf(idxVal + 1);
    for (int i = 1; i <= idxE; i++) {
        uf.unionSets(Val2Rank[iValE[i]], Val2Rank[jValE[i]]);
    }
    for (int i = 1; i <= idxNE; i++) {
        if (uf.connected(Val2Rank[iValNE[i]], Val2Rank[jValNE[i]])) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}