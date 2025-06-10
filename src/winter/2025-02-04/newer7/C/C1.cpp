// T568803 数根
// TODO
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void print(int x)
{
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

vector<int> sieveOfEratosthenes(int n)
{
    vector<int>  primes;
    vector<bool> prime(n + 1, true);

    prime[0] = prime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int p = 2; p <= n; p++) {
        if (prime[p])
            primes.emplace_back(p);
    }

    return primes;
}

list<int> primeFactorization(int n, vector<int>& prime)
{
    list<int> factors;
    for (int iter : prime) {
        if (n % iter == 0) {
            factors.emplace_back(iter);
        }
        if (iter > sqrt(n) + 2)
            break;
    }
    return factors;
}

signed main(signed argc, char** argv)
{
    // #ifndef ONLINE_JUDGE
    //     freopen(argv[1], "r", stdin);
    //     freopen(argv[2], "w", stdout);
    // #endif
    vector<int>   prime = std::move(sieveOfEratosthenes(1e6 + 5));
    map<int, int> rank2prime;
    int           rank = 0;
    for (int iter : prime) {
        rank2prime[iter] = ++rank;
    }
    vector<int> cntUnperfect(rank + 1, 0);
    int         K, B;
    K = init();
    B = init();
    vector<int> k(K + 1);
    for (int i = 1; i <= K; i++) {
        k[i] = init();
    }
    for (int i = 1; i <= B; i++) {
        int curB;
        curB = init();
        for (int iter : prime) {
            if (iter > curB) {
                break;
            }
            if (curB % iter == 1) {
                cntUnperfect[rank2prime[iter]]++;
            }
        }
    }
    LL ans = K * B;
    for (int i = 1; i <= K; i++) {
        list<int> facotr = std::move(primeFactorization(k[i], prime));
        for (int iter : facotr) {
            ans -= cntUnperfect[rank2prime[iter]];
        }
    }
    print(ans);
    return 0;
}