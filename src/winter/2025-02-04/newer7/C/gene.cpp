#include <bits/stdc++.h>
using namespace std;
using LL = long long;
mt19937 rd;

int rdInt(int l = 0, int r = UINT32_MAX)
{
    return rd() % (r - l) + l;
}

void rdInit(void)
{
    {
        FILE* seedFile = fopen("seed.txt", "r");
        int   s;
        fscanf(seedFile, "%d", &s);
        rd.seed(s);
        fclose(seedFile);
    }
    {
        FILE* seedFile = fopen("seed.txt", "w");
        fprintf(seedFile, "%ld", rd());
        fclose(seedFile);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("test.in", "w", stdout);
    rdInit();
    int K = rdInt(1, 50);
    int B = rdInt(1, 50);
    cout << K << ' ' << B << '\n';
    for (int i = 1; i <= K; i++) {
        cout << rdInt(2, 50) << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= B; i++) {
        cout << rdInt(2, 50) << ' ';
    }
    cout << '\n';
    return 0;
}