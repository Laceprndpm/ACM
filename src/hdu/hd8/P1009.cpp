#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n, w;
    cin >> n >> w;
    vector<int> person;
    person.push_back(0);
    int tmp   = n;
    int round = 0;
    while (tmp >= w) {
        int cut = tmp / w;
        person.push_back(cut);
        tmp -= cut;
        round++;
    }
    round++;
    person.push_back(tmp);
    int now = n;
    int ans = 0;
    for (int i = round; i >= 1; i--) {
        ans += i * (person[i] * now - (person[i] * (person[i] - 1)) / 2);
        now -= person[i];
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        Echo2();
}