#include <bits/stdc++.h>

using namespace std;

using li = long long;

const int N = 111;

int    n;
string s;
int    dp[2][N][N * N];

int main()
{
    cin >> s;
    n           = s.size();
    dp[0][0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i + 1; ++j) {
            for (int cnt = 0; cnt <= j * (i + 1 - j); ++cnt) {
                dp[1][j][cnt] = n;
            }
        }
        for (int j = 0; j <= i; ++j) {
            for (int cnt = 0; cnt <= j * (i - j); ++cnt) {
                dp[1][j + 1][cnt] = min(dp[1][j + 1][cnt], dp[0][j][cnt] + (s[i] != '0'));
                dp[1][j][cnt + j] = min(dp[1][j][cnt + j], dp[0][j][cnt] + (s[i] != '1'));
            }
        }
        swap(dp[0], dp[1]);
    }
    int cnt0 = count(s.begin(), s.end(), '0');
    cout << dp[0][cnt0][cnt0 * (n - cnt0) / 2] / 2 << '\n';
}