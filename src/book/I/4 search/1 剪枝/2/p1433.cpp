#ifdef DFSVERSION
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
int                          n;
vector<pair<double, double>> arr;
vector<vector<double>>       distarr;
double                       ans = 1e9;
int                          cnt;

constexpr double dist(const pair<double, double> a, const pair<double, double> b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

double mydfs(vector<int>& unvis, double curdist, const int& last)
{
    cnt++;
    if (cnt >= 40000000) {
        printf("%.2lf", ans);
        exit(0);
    }
    if (curdist >= ans) {
        return ans;
    }
    if (count(unvis.begin(), unvis.end(), 0) == n + 1) {
        return curdist;
    }
    for (int i = 1; i <= n; i++) {
        if (unvis[i] == 1) {
            unvis[i] = 0;
            ans      = min(mydfs(unvis, curdist + distarr[last][i], i), ans);
            unvis[i] = 1;
        }
    }
    return ans;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    arr.resize(n + 1);
    distarr.resize(n + 1, vector<double>(n + 1));
    arr[0].first  = 0;
    arr[0].second = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].first;
        cin >> arr[i].second;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            distarr[i][j] = dist(arr[i], arr[j]);
        }
    }
    vector<int> unvis(n + 1, true);
    unvis[0] = false;
    mydfs(unvis, 0, 0);
    printf("%.2lf", ans);
    return 0;
}
#endif

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
int                          m;
vector<pair<double, double>> arr;
vector<vector<double>>       distarr;
double                       ans = 1e9;
int                          cnt;
double                       dp[1 << 16][16];

constexpr double dist(const pair<double, double> a, const pair<double, double> b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void mydfs(int unvis, const int& last)
{
    cnt++;
    if (cnt >= 40000000) {
        printf("%.2lf", ans);
        exit(0);
    }
    if (unvis == 0) {
        dp[unvis][last] = 0;
        return;
    }
    double minkidans = 1e9;
    for (int i = 1; i <= m; i++) {
        double kidans = 1e9;
        if (unvis >> i & 1) {
            if (!dp[unvis ^ (1 << i)][i]) {
                mydfs(unvis ^ (1 << i), i);
            }
            kidans = dp[unvis ^ (1 << i)][i];
        }
        minkidans = min(minkidans, kidans + distarr[i][last]);
    }
    dp[unvis][last] = minkidans;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> m;
    arr.resize(m + 1);
    distarr.resize(m + 1, vector<double>(m + 1));
    arr[0].first  = 0;
    arr[0].second = 0;
    for (int i = 1; i <= m; i++) {
        cin >> arr[i].first;
        cin >> arr[i].second;
    }
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            distarr[i][j] = dist(arr[i], arr[j]);
        }
    }
    int unvis = 0;
    for (int i = 1; i <= m; i++) {
        unvis += 1 << i;
    }
    mydfs(unvis, 0);
    ans = dp[unvis][0];
    printf("%.2lf", ans);
    return 0;
}