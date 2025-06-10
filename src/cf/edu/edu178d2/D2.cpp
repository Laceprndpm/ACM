#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

vector<bool> seive(i64 n)
{
    vector<bool> primes((n + 1) / 2, 0);
    for (i64 i = 3; i < n; i += 2) {
        if (primes[i / 2] == false)
            for (i64 j = i * i; j < n; j += i * 2) {
                primes[j / 2] = 1;
            }
    }
    return primes;
}

vector<bool> primes;
vector<i64>  p;

void solve()
{
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr.begin(), arr.end());
    vector<i64> left;
    int         m    = p.size();
    int         j    = 0;
    i64         coin = 0;
    int         i    = 0;
    for (; i < n; i++) {
        coin += arr[i] - p[i];
    }
    for (i = n - 1; i >= 0 && coin < 0; i--) {
        coin -= (arr[i] - p[i]);
        coin += arr[i] - 2;
    }

    cout << n - i - 1 << endl;
}

int main()
{
    primes = seive(1e6 * 7);
    p.push_back(2);
    for (i64 i = 3; i <= 1e6 * 7; i += 2) {
        if (primes[i / 2] == false) p.push_back(i);
    }
    int T;
    cin >> T;

    while (T--)
        solve();
}