#include <bits/stdc++.h>
using namespace std;
using LL = long long;
void solve(void)
{
    int n, l, r;
    cin >> n >> l >> r;
    priority_queue<int, vector<int>, greater<int>> l_heap;
    priority_queue<int, vector<int>, greater<int>> r_heap;
    priority_queue<int, vector<int>, less<int>> ml_heap;
    priority_queue<int, vector<int>, less<int>> mr_heap;
    LL l_sum = 0;
    LL r_sum = 0;
    for (int i = 1; i < l; i++)
    {
        int temp;
        cin >> temp;
        l_heap.push(temp);
    }
    for (int i = l; i <= r; i++)
    {
        int temp;
        cin >> temp;
        ml_heap.push(temp);
        mr_heap.push(temp);
        l_sum += temp;
    }
    r_sum = l_sum;
    for (int i = r + 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        r_heap.push(temp);
    }
    while (!ml_heap.empty() && !l_heap.empty() && ml_heap.top() > l_heap.top())
    {
        l_sum -= ml_heap.top();
        l_sum += l_heap.top();
        ml_heap.pop();
        l_heap.pop();
    }
    while (!mr_heap.empty() && !r_heap.empty() && mr_heap.top() > r_heap.top())
    {
        r_sum -= mr_heap.top();
        r_sum += r_heap.top();
        mr_heap.pop();
        r_heap.pop();
    }
    cout << min(r_sum, l_sum) << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}