#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
i64 n, k, S;
int midstone;

class mathclass {
private:
    vector<i64> _fac;

public:
    mathclass(int n) : _fac(n)
    {
        _fac[0] = 1;
        for (i64 i = 1; i < n; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
    };

    i64 fac(int i)
    {
        return _fac[i];
    }

} fa(20);

map<pair<int, i64>, i64> middle;

vector<int> aiInput;

void halfDFS(int idx, i64 ans, int labels)
{
    if (idx == midstone) {
        middle[{labels, ans}]++;
        return;
    }
    if (ans > S) {
        return;
    }
    if (labels < k && aiInput[idx] < 19 && ans + fa.fac(aiInput[idx]) <= S) {
        halfDFS(idx + 1, ans + fa.fac(aiInput[idx]), labels + 1);
    }
    if (ans + aiInput[idx] <= S) {
        halfDFS(idx + 1, ans + aiInput[idx], labels);
    }
    halfDFS(idx + 1, ans, labels);
}

void speed()
{
    map<pair<int, i64>, i64> tmp;
    for (auto i : middle) {
        auto key = i.first;
        for (int j = key.first; j <= k; j++) {
            tmp[{j, key.second}] += i.second;
        }
    }
    swap(tmp, middle);
}

i64 anotherDFS(int idx, i64 ans, int labels)
{
    if (idx == n) {
        i64 res = 0;
        res += (middle[{k - labels, S - ans}]);
        return res;
    }
    if (ans > S) {
        return 0;
    }
    i64 res = 0;
    if (labels < k && aiInput[idx] < 19 && ans + fa.fac(aiInput[idx]) <= S) {
        res += anotherDFS(idx + 1, ans + fa.fac(aiInput[idx]), labels + 1);
    }
    if (ans + aiInput[idx] <= S) {
        res += anotherDFS(idx + 1, ans + aiInput[idx], labels);
    }
    res += anotherDFS(idx + 1, ans, labels);
    return res;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k >> S;
    midstone = n / 2;
    aiInput.resize(n);
    for (int& i : aiInput) {
        cin >> i;
    }
    if (n > 1) {
        halfDFS(0, 0, 0);
        speed();
        cout << anotherDFS(midstone, 0, 0);
    } else {
        int ans = 0;
        if (aiInput[0] < 18 && fa.fac(aiInput[0]) == S && k >= 1) {
            ans++;
        }
        if (aiInput[0] == S) {
            ans++;
        }
        if (S == 0) {
            ans++;
        }
        cout << ans;
    }
    return 0;
}