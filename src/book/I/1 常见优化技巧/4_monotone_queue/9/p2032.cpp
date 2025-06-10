#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 2e6 + 5;
int           input[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> input[i];
    }
    deque<int> monoQueIdx;
    for (int i = 1; i <= n; i++) {
        while (!monoQueIdx.empty() && i - monoQueIdx.front() >= k) {
            monoQueIdx.pop_front();
        }
        while (!monoQueIdx.empty() && input[monoQueIdx.back()] <= input[i]) {
            monoQueIdx.pop_back();
        }
        monoQueIdx.push_back(i);
        if (i >= k) {
            cout << input[monoQueIdx.front()] << '\n';
        }
    }
    return 0;
}