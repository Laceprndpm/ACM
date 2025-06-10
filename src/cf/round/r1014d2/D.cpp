#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct node {
    char idx = 0;
    int  cnt = 0;

    bool operator<(node& t)
    {
        return cnt < t.cnt;
    }
};

void solve()
{
    int    n;
    string s;
    cin >> n >> s;
    node L{'L', 0}, T{'T', 0}, I{'I', 0};
    L.cnt = count(s.begin(), s.end(), 'L');
    T.cnt = count(s.begin(), s.end(), 'T');
    I.cnt = count(s.begin(), s.end(), 'I');
    vector<node> save{L, I, T};
    vector<int>  ans;
    while (save[0].cnt != save[1].cnt || save[1].cnt != save[2].cnt) {
        int l = s.length();
        sort(save.begin(), save.end());
        bool su = false;
        for (auto& i : save) {
            auto& [cha, cnt] = i;
            bool succ        = false;
            for (int j = 0; j < l - 1; j++) {
                if (s[j] != cha && s[j + 1] != cha && s[j] != s[j + 1]) {
                    succ = true;
                    cnt++;
                    ans.emplace_back(j + 1);
                    s.insert(j + 1, 1, cha);
                    break;
                }
            }
            if (succ) {
                su = true;
                break;
            }
        }
        if (!su) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << '\n';
    }
    return;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // L == T的情况，只需要LTLTLT...直到全部为I
    // L < T呢？
    // LTTTLILTIII
    // 需要插入I来救场
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}