#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
string        ans = "";

void query2(int l, int r)
{
    cout << '?' << ' ' << '2' << ' ' << l << ' ' << r << endl;
}

void query1(int x)
{
    cout << "? 1 " << x << endl;
}

struct node {
    int last;
    int chara;

    bool operator<(node& t)
    {
        return last > t.last;
    }
};

void binSearch(vector<int>& nearLast, int cur)
{
    if (cur == 1) {
        query1(cur);
        char inputc;
        cin >> inputc;
        int curC       = inputc - 'a';
        nearLast[curC] = cur;
        ans += curC + 'a';
        return;
    }
    vector<node> sortedLast;
    for (int i = 0; i < 26; i++) {
        if (nearLast[i]) {
            sortedLast.push_back({nearLast[i], i});
        }
    }
    int l = 0, r = sortedLast.size() - 1;
    query2(1, cur);
    int res;
    cin >> res;
    int curC;
    if (res > sortedLast.size()) {
        query1(cur);
        char inputc;
        cin >> inputc;
        curC = inputc - 'a';
    } else {
        sort(sortedLast.begin(), sortedLast.end());
        while (l < r) {
            int mid = (r + l) / 2;
            query2(sortedLast[mid].last, cur);
            int cur;
            cin >> cur;
            if (cur == mid + 1) {  // 在前mid字符里
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        curC = sortedLast[r].chara;
    }
    nearLast[curC] = cur;
    ans += curC + 'a';
}

void solve()
{
    int n;
    cin >> n;
    // log26 == 5，也就是说我可以在五次内确定一个字符
    vector<int> nearLast(26);
    // 每次sort，是100的常数，随后二分的忽略不计
    for (int i = 1; i <= n; i++) {
        binSearch(nearLast, i);
    }
    cout << "! " << ans << endl;
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
    solve();
    return 0;
}