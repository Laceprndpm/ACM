#include <iostream>
#include <string>
using namespace std;
string s;
int    t, n, l, r, a[200010];  // a[i]:0到i最多容纳多少个)

int main()
{
    cin >> t;
    while (t--) {
        cin >> n >> s;
        l    = 0;
        r    = 0;
        s[0] = '(';
        for (int i = 1; i < n; i++) {
            if (s[i] == '(')
                l++;
            else
                r++;
            a[i] = l;
        }
        for (int i = n - 2; i > 0; i--)
            if (a[i] > a[i + 1]) a[i] = a[i + 1];
        //        for(int i=0;i<n;i++)cout<<a[i]<<" ";
        int x = 0;
        for (int i = 2; i < n; i += 2) {
            if (a[i] > x) {
                s[i] = ')';
                x++;
            } else
                s[i] = '(';
        }
        //        cout<<s;
        x = l = 0;
        for (int i = 0; i < n; i++) {
            l += x;
            if (s[i] == '(')
                x++;
            else
                x--;
        }
        cout << l << endl;
    }
}