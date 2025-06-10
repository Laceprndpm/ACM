#include <bits/stdc++.h>
using namespace std;

void Tokisaki()
{
    string s;
    cin >> s;
    int n = s.size();
    int ans = 0;
    int l = 0, r = n - 1;
    while (s[l] != s[r]) {
        ans++;
        l = (l + 1) % n;
        r = (r + 1) % n;
        if (l == 0) {
            cout << "-1\n";
            return;
        }
    }
    cout<<ans<<'\n';
}
int main()
{
    int _;
    cin >> _;
    while(_--)Tokisaki();
    return 0;
}