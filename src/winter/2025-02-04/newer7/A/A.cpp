#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr int MAXN = 5e5 + 50;

int MODPOOL[] = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097,
                 1000000103, 1000000123, 1000000181, 1000000207, 1000000223, 1000000241, 1000000271,
                 1000000289, 1000000297, 1000000321, 1000000349, 1000000363, 1000000403, 1000000409,
                 1000000411, 1000000427, 1000000433, 1000000439, 1000000447, 1000000453, 1000000459,
                 1000000483, 1000000513, 1000000531, 1000000579, 1000000607, 1000000613, 1000000637,
                 1000000663, 1000000711, 1000000753, 1000000787, 1000000801, 1000000829, 1000000861,
                 1000000871, 1000000891, 1000000901, 1000000919, 1000000931, 1000000933, 1000000993};
int MOD[3];
int hash_mod[MAXN][3];

void init_hash(string& input)
{
    {
        set<int> chosen_mods;
        for (int i = 0; i < 3; i++) {
            int mod;
            do {
                mod = MODPOOL[rand() % 49];
            } while (chosen_mods.count(mod));
            chosen_mods.insert(mod);
            MOD[i] = mod;
        }
    }

    for (int i = 1; i < input.size(); i++) {
        for (int j = 0; j < 3; j++) {
            hash_mod[i][j] = (hash_mod[i - 1][j] * 2 + input[i]) % MOD[j];
        }
    }
}

int find_rightest_1(string& input)
{
    for (int i = input.size(); i >= 1; i--) {
        if (input[i] == 1) {
            return i;
        }
    }
    return -1;
}

int hash_x(int l, int r, int x, int j)
{
    if (x <= r - l + 1)
        return (hash_mod[l + x - 1][j] + MOD[j] - hash_mod[l - 1][j]) % MOD[j];
    int ans = (pre[r][j] + Mod[j] - pre[l - 1][j] * pow2[r - l + 1][j] % Mod[j]) % Mod[j];
    return (ans + suf[r - x + 1][j] + Mod[j] - pow2[x - (r - l + 1)][j] * suf[l][j] % Mod[j]) % Mod[j];
}

void solve()
{
    string input;
    cin >> input;
    int length = input.size();
    for (auto iter : input) {
        if (iter == 'O') {
            iter = 1;
        } else {
            iter = 0;
        }
    }
    input          = '\0' + input;
    int rightest_1 = find_rightest_1(input);
    if (rightest_1 == -1) {
        cout << length << '\n';
        return;
    }

    init_hash(input);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    srand(time(0));
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}