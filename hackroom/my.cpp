#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    string ans;
    for (int i = 0; i < K; i++) {
        if (i <= 10) {
            sort(S.begin(), S.end(), [&](string s, string t) {
                return s + ans < t + ans;
            });
            ans = S[0] + ans;
        } else {
            string ans2;
            for (int j = i; j < K; j++) {
                ans2 += S[0];
            }
            ans2 += ans;
            ans = ans2;
            break;
        }
    }
    cout << ans << endl;
}