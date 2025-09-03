void Or(ll *a, ll type)
{  // 迭代实现，常数更小
    for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
            for (ll j = 0; j < k; j++) {
                (a[i + j + k] += a[i + j] * type) %= P;
            }
        }
    }
}

void And(ll *a, ll type)
{
    for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
            for (ll j = 0; j < k; j++) {
                (a[i + j] += a[i + j + k] * type) %= P;
            }
        }
    }
}

void Xor(ll *a, ll type)
{
    for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
            for (ll j = 0; j < k; j++) {
                (a[i + j] += a[i + j + k]) %= P;
                (a[i + j + k] = a[i + j] - a[i + j + k] * 2) %= P;
                (a[i + j] *= type) %= P;
                (a[i + j + k] *= type) %= P;
            }
        }
    }
}
