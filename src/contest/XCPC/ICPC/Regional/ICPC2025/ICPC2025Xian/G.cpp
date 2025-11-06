#include <bits/stdc++.h>

#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
using i64 = long long;
#define all(x) (x).begin(), (x).end()

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    auto check = [&]() -> i64 {
        i64 s = 0;
        for (int i : arr) {
            if (s >= i) {
                s++;
            } else {
                s--;
            }
        }
        return s;
    };
    sort(all(arr));
    int mx = check();
    sort(all(arr), greater<>());
    int mn = check();
    cout << mx << ' ' << mn << '\n';
    return 0;
}