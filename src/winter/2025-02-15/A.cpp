#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;
vector<int> radius(1e5 + 5);
vector<int> sticks(1e5 + 5);

int n, m;

bool check(map<int, int> cntStick, int mid)
{
    list<int> chosen;
    int       count = 0;
    for (int j = m; j >= 1 && count < mid; --j) {
        if (cntStick.count(2 * radius[j]) && cntStick[2 * radius[j]] > 0) {
            ++count;
            cntStick[2 * radius[j]]--;
            chosen.push_back(radius[j]);
        }
    }
    if (count != mid) {
        return false;
    }
    for (int j = n; j >= 1; j--) {
        if (chosen.empty()) {
            break;
        }
        if (sticks[j] < chosen.front() && cntStick[sticks[j]] > 0) {
            cntStick[sticks[j]]--;
            chosen.pop_front();
        }
    }
    return chosen.empty();
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    map<int, int> cntStick;
    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        sticks[i] = tmp;
        cntStick[tmp]++;
    }
    map<int, int> cntRadius;
    int           totalcntRadius = 0;
    for (int i = 1; i <= m; i++) {
        int tmp;
        cin >> tmp;
        radius[i] = tmp;
        cntRadius[tmp]++;
        totalcntRadius++;
    }
    stable_sort(sticks.begin() + 1, sticks.begin() + 1 + n);
    stable_sort(radius.begin() + 1, radius.begin() + 1 + m);
    int L = 0, R = totalcntRadius;
    while (L < R) {
        int mid = (R - L + 1) / 2 + L;
        if (check(cntStick, mid)) {
            L = mid;
        } else {
            R = mid - 1;
        }
    }
    cout << L;
    return 0;
}