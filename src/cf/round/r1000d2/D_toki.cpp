#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Tokisaki(int _)
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    deque<int>  dqA(a.begin(), a.end()), dqB(b.begin(), b.end());
    stack<int>  al, ar, bl, br;
    int         sum = 0;
    vector<int> ans;
    int         res1 = 0, res2 = 0;
    int         sum1 = n, sum2 = m;
    while (1) {
        res1 = 0, res2 = 0;
        if (sum1 >= 2 && sum2) res1 = dqA.back() - dqA.front();
        if (sum2 >= 2 && sum1) res2 = dqB.back() - dqB.front();
        if (res1 == 0 && res2 == 0) {
            if (sum1 >= 3 && br.size() && bl.size()) {
                sum -= br.top() - bl.top();
                dqB.push_front(bl.top());
                dqB.push_back(br.top());
                bl.pop();
                br.pop();

                sum += dqA.back() - dqA.front();
                al.push(dqA.front());
                ar.push(dqA.back());
                dqA.pop_back();
                dqA.pop_front();

                sum += dqA.back() - dqA.front();
                al.push(dqA.front());
                ar.push(dqA.back());
                dqA.pop_back();
                dqA.pop_front();

                ans.push_back(sum);
                sum1 -= 3;
            } else if (sum2 >= 3 && ar.size() && al.size()) {
                sum -= ar.top() - al.top();
                dqA.push_front(al.top());
                dqA.push_back(ar.top());
                al.pop();
                ar.pop();

                sum += dqB.back() - dqB.front();
                bl.push(dqB.front());
                br.push(dqB.back());
                dqB.pop_back();
                dqB.pop_front();

                sum += dqB.back() - dqB.front();
                bl.push(dqB.front());
                br.push(dqB.back());
                dqB.pop_back();
                dqB.pop_front();

                ans.push_back(sum);
                sum2 -= 3;
            } else
                break;
        } else if (res1 > res2) {
            sum += res1;
            ans.push_back(sum);
            sum1 -= 2;
            sum2--;
            al.push(dqA.front());
            ar.push(dqA.back());
            dqA.pop_back();
            dqA.pop_front();
        } else {
            sum += res2;
            ans.push_back(sum);
            sum2 -= 2;
            sum1--;
            bl.push(dqB.front());
            br.push(dqB.back());
            dqB.pop_back();
            dqB.pop_front();
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans)
        cout << i << ' ';
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--)
        Tokisaki(_ + 1);
    return 0;
}