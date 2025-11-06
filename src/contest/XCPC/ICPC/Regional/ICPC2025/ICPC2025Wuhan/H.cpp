#include <iostream>
#include <set>
using namespace std;
using u32 = uint32_t;

u32 query(u32 c)
{
    cout << "? " << c << endl;
    u32 res;
    cin >> res;
    return res ^ c;
}

void solve()
{
    int n;
    cin >> n;
    u32      chi = query(0);
    u32      clo = query((1 << 30) - 1);
    set<u32> st;
    auto     dfs = [&](auto&& self, u32 lo, u32 hi) -> void {
        if (hi - lo <= 1 || st.size() == n) return;
        // cerr << "lo hi : " << lo << ' ' << hi << endl;
        u32 xo    = lo ^ hi;
        u32 lca_t = 0;
        int i;
        for (i = 29; i >= 0; i--) {
            if (!(xo >> i & 1)) {
                lca_t |= (lo & (1 << i)) ^ (1 << i);
            } else {
                break;
            }
        }
        u32 lft = query(lca_t | (1 << i));
        if (lft != lo) {
            st.insert(lft);
            self(self, lo, lft);
        }
        u32 rgt = query(lca_t | ((1 << i) - 1));
        if (rgt != hi) {
            st.insert(rgt);
            self(self, rgt, hi);
        }
    };
    st.insert(clo);
    st.insert(chi);
    dfs(dfs, clo, chi);
    cout << "! ";
    for (int i : st) {
        cout << i << ' ';
    }
    cout << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
