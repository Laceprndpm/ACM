#include <bits/stdc++.h>

#include <cassert>
using namespace std;

#define endl '\n'
#define ll   long long
#define int  long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == b && a == 0 && c != 0) {  // ab都是0，c不是0肯定错
            cout << -1 << endl;
            continue;
        }
        if (a == b && b == c) {  // 如果都一样0次操作
            cout << 0 << endl;
            cout << endl;
            continue;
        }
        vector<int> ans;                       // 记录答案序列
        int         z1 = 0, z2 = -1, z3 = -1;  // 记录我们当前高位
        for (int i = 0; i <= 30; i++) {
            if ((a >> i) % 2 == 1) {
                z1 = i;
            }
            if ((b >> i) % 2 == 1) {
                z2 = i;
            }
            if ((c >> i) % 2 == 1) {
                z3 = i;
            }
        }
        if (z1 > z2) {  // b不是高位，那么我们要b^=a，这样b就和a一个位置
            ans.push_back(4);
            b ^= a;
            z1 = 0, z2 = 0;
            for (int i = 0; i <= 30; i++) {
                if ((a >> i) % 2 == 1) {
                    z1 = i;
                }
                if ((b >> i) % 2 == 1) {
                    z2 = i;
                }
            }
        }

        if (z3 > z2) {  // c的高位比a高，所以是你添加b，a*=2,达成z3=z2,初始b高度前面c和a一样;
            while (z3 > z2) {
                if (((c >> z3) % 2) != ((a >> z2) % 2)) {
                    ans.push_back(3);
                    a ^= b;
                }
                ans.push_back(1);
                a *= 2;
                z3--;
            }
        }
        while (z2 > z1 && z2 > z3) {
            ans.push_back(2);
            z2--;
            b /= 2;
        }

        while (z1 > z3) {  // 如果现在的初始情况是a的高位，大于c的高位，那么我的b需要判断这个位置要不要异或，然后右移
            if (((c >> z1) % 2) != ((a >> z1) % 2)) {
                ans.push_back(3);
                a ^= b;
            }
            z1--;
            ans.push_back(2);
            z2--;
            b /= 2;
        }
        while (z3 > z1) {  // c=16 a=4 这种情况，我们需要正常操作b，让a异或b，满足b能够直接影响的位置异或掉，然后b右移动
            if (((c >> z3) % 2) != ((a >> z3) % 2)) {
                ans.push_back(3);
                a ^= b;
            }
            z3--;
            ans.push_back(2);
            z2--;
            b /= 2;
        }
        while (z3 >= 0) {  // 最后就是把全部所有位置都操作一遍，b也是右移 z1=z2=z3
            if (((c >> z3) % 2) != ((a >> z1) % 2)) {
                ans.push_back(3);
                a ^= b;
            }
            z3--;
            z1--;
            ans.push_back(2);
            z2--;
            b /= 2;
        }
        // b要等于0
        while (b != 0) {
            ans.push_back(2);
            z2--;
            b /= 2;
        }
        ans.push_back(4);
        b ^= a;  // a=c再把a给b
        cout << ans.size() << endl;
        for (auto x : ans) {
            cout << x << ' ';
        }
        cout << endl;
    }
    return 0;
}