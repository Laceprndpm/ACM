#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

// Definition for a binary tree node.
struct TreeNode {
    int       val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rob(TreeNode *root)
    {
        function<pair<int, int>(TreeNode *)> dfs = [&](TreeNode *node) {
            if (!node) {
                return make_pair(0, 0);
            }
            pair<int, int> left  = dfs(node->left);
            pair<int, int> right = dfs(node->right);
            int            l_rob = left.first, l_not = left.second;
            int            r_rob = right.first, r_not = right.second;
            int            rob     = node->val + l_not + r_not;
            int            not_rob = max(l_rob, l_not) + max(r_rob, r_not);
            return make_pair(rob, not_rob);
        };
        pair<int, int> res = dfs(root);
        return max(res.first, res.second);
    }
};

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif

    return 0;
}