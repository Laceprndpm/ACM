/**
 *@brief 笛卡尔树
 */
template <class T>
class CartesianTree {
    const int   n;
    vector<int> rs;
    vector<int> ls;
    vector<T>   data;
    int         treeRoot;
    vector<int> nodeGcd;

public:
    // 1-idx
    CartesianTree(vector<T>&& _init) : n(_init.size() - 1), rs(n + 1), ls(n + 1), data(std::move(_init))
    {
        init();
    }

    CartesianTree(const vector<T>& _init) : n(_init.size() - 1), rs(n + 1), ls(n + 1), data(_init)
    {
        init();
    }

    void init() noexcept
    {
        // stk 维护笛卡尔树中节点对应到序列中的下标
        int         top = 0;
        vector<int> stk(n + 1);
        for (int i = 1; i <= n; i++) {
            int k = top;  // top 表示操作前的栈顶，k 表示当前栈顶
            while (k > 0 && data[stk[k]] > data[i])
                k--;                          // 维护右链上的节点
            if (k) rs[stk[k]] = i;            // 栈顶元素.右儿子 := 当前元素
            if (k < top) ls[i] = stk[k + 1];  // 当前元素.左儿子 := 上一个被弹出的元素
            stk[++k] = i;                     // 当前元素入栈
            top      = k;
        }
        treeRoot = stk[1];
        nodeGcd.assign(n + 1, 0);
        DFS1(treeRoot);
    }

    void DFS1(int root) noexcept
    {
        int curGcd = 0;
        if (ls[root] != 0) {
            DFS1(ls[root]);
            curGcd = gcd_multi(curGcd, nodeGcd[ls[root]], data[ls[root]] - data[root]);
        }
        if (rs[root] != 0) {
            DFS1(rs[root]);
            curGcd = gcd_multi(curGcd, nodeGcd[rs[root]], data[rs[root]] - data[root]);
        }
        nodeGcd[root] = curGcd;
    }

    bool check(int x) noexcept
    {
        for (int i = 1; i <= n; i++) {
            if (nodeGcd[i] % (data[i] + x) != 0) {
                return false;
            }
        }
        return true;
    }
};
