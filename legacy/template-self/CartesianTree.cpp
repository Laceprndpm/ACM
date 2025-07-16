/**
 *@brief 笛卡尔树
 */

template <class T>
struct CartesianTree {
    int                        n;
    vector<int>                stk;
    vector<std::array<int, 2>> child;
    vector<T>                  data;
    int                        treeRoot;

public:
    // 1-idx
    CartesianTree(vector<T>&& _init) : n(_init.size() - 1), stk(n + 1), child(n + 1), data(std::move(_init))
    {
        init();
    }

    CartesianTree(const vector<T>& _init) : n(_init.size() - 1), stk(n + 1), child(n + 1), data(_init)
    {
        init();
    }

    void init() noexcept
    {
        // stk 维护笛卡尔树中节点对应到序列中的下标
        int top = 0;
        for (int i = 1; i <= n; i++) {
            int k = top;  // top 表示操作前的栈顶，k 表示当前栈顶
            while (k > 0 && data[stk[k]] > data[i])
                k--;                                // 维护右链上的节点
            if (k) child[stk[k]][1] = i;            // 栈顶元素.右儿子 := 当前元素
            if (k < top) child[i][0] = stk[k + 1];  // 当前元素.左儿子 := 上一个被弹出的元素
            stk[++k] = i;                           // 当前元素入栈
            top      = k;
        }
        treeRoot = stk[1];
    }
};