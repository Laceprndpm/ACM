#include <iterator>
#include <map>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

bool check(int x)
{
    return (x) % 4 == 0;
}

void Tokisaki()
{
    string s;
    cin >> s;
    int n = s.size();
    char res = s[0];
    int  ans = 0;
    int  len = 1;
    bool flag = 0;
    map<char,int>mp;
    for (int i = 1; i < n; i++) {
        mp[s[i]]++;
        while (s[i] == res&&i<n) {
            i++;
            len++;
        }
        if (len % 2 == 0) flag = 1;
        ans += len / 2;
        if (i < n) res = s[i] ,len=1;
    }
    bool have_cut = 1;
    if (s[0] != s[n - 1]) have_cut = 0;
    else {
        int p = 0;
        char res = s[0];
        int cnt1=0,cnt2=0;
        while (s[p] == s[0]&&p<n) {
            cnt1++;
            p++;
        }
        p = n - 1;
        while (s[p] == s[n - 1] && p >= 0) {
            cnt2++;
            p--;
        }
        if(!(cnt1%2==1&&cnt2%2==1))have_cut=0;
    }
    if (flag && mp.size() > 1&&have_cut==0) ans--;
    cout<<ans<<'\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int _;
    cin >> _;
    while (_--) {
        Tokisaki();
    }
    return 0;
}