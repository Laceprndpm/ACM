#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll ;
void Tokisaki()
{
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    priority_queue<ll> pq;
    ll                 sum = 0;
    for (int i = n; i >= 1; i--) {
        sum += a[i];
        if(i>1)pq.push(sum);
    }
    ll ans=sum;
    for (int i = 1; i <= n-1; i++) {
        cout << ans << ' ';
        ans += pq.top();
        pq.pop();
    }
    cout<<ans<<'\n';
}

int main()
{
    int _;
    cin >> _;
    while (_--)
        Tokisaki();
    return 0;
}