#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class PrimeSieve {
public:
    PrimeSieve(int n) : n(n), is_prime(n + 1, true)
    {
        sieve();
    }

    bool query(int num) const
    {
        if (num <= n) {
            return is_prime[num];
        }
        return false;
    }

private:
    int          n;
    vector<bool> is_prime;

    void sieve()
    {
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    PrimeSieve prime(1e6 + 5);
    while (t--) {
        int n, e;
        cin >> n >> e;
        vector<int> input(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> input[i];
        }
        LL ans = 0;
        for (LL i = 1; i <= e; i++) {
            LL          j = 0;
            map<LL, LL> l;
            LL          cnt = 0;
            for (; j * e + i <= n; j++) {
                if (input[j * e + i] == 1) {
                    cnt++;
                } else {
                    l[j] = cnt;
                    cnt  = 0;
                }
            }
            cnt = 0;
            j--;
            for (; j * e + i >= 1; j--) {
                if (input[j * e + i] == 1) {
                    cnt++;
                } else {
                    if (prime.query(input[j * e + i])) {
                        ans += cnt + l[j] + cnt * l[j];
                    }
                    cnt = 0;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}