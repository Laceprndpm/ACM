#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N   = 8e5 + 5;
constexpr int MOD = 1e9 + 7;

int input[N];
int nxt[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> input[i];
    }
    stack<int> monotoneStack;
    LL         ans = 0;
    for (int i = n; i >= 1; i--) {
        while (!monotoneStack.empty() && input[monotoneStack.top()] < input[i]) {
            monotoneStack.pop();
        }
        if (!monotoneStack.empty()) {
            ans += monotoneStack.top() - i - 1;
        } else {
            ans += n - i;
        }
        monotoneStack.push(i);
    }
    cout << ans;
    return 0;
}
