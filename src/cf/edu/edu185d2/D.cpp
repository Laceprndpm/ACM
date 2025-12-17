#include <cassert>
#include <iostream>
using namespace std;

void solve()
{
    // 一个字符串的所有'?'可以用什么描述？
    // 如果下个字符是'XV'，则可以描述为XV
    // 如果前一个字符是'I'，可以描述为IXV
    //
    // 如果下一个字符是‘V'，可以描述为IV
    // 如果下一个字符是'?'，可以描述为'?'
    // 是否要将所有连续'?'字符两两破坏？这样贪心看起来很对
    // 因为我一定优先让I变成-1
    // 随后再安排V?不，先让I尽可能多点
    // 即破坏双'?'，产生一个XVminas
    // 现在问题是
    // I??V
    // 怎么描述？
    // 一个double or 一个IXV+IV?
    // 很明显后面更灵活
    //
    // 或许可以更简单，前i_1个I是-1的贡献，这里绝对不会影响后续填VX。然后I再填到所有后面有'?'的位置，
    // 此时会增加vx_i，增加的上限取决于'??'，随后填入VX，这样应该不会错
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    s = '#' + s + "###";

    int  i_1     = 0;
    int  doubleq = 0;
    int  normq   = 0;
    int  xv_i    = 0;
    int  both    = 0;
    auto is_xv   = [](char c) { return c == 'X' || c == 'V'; };
    for (int i = 1; i <= n;) {
        if (s[i] == '?') {
            if (s[i - 1] == 'I' && is_xv(s[i + 1])) {
                normq++;
                // 算入normq
                both++;
                i++;
                continue;
            }
            if (is_xv(s[i + 1])) {
                i_1++;
                i++;
                continue;
            } else if (s[i - 1] == 'I') {
                xv_i++;
                i++;
                continue;
            } else if (s[i + 1] == '?') {
                if (!is_xv(s[i + 2])) {
                    {
                        doubleq++;
                        i += 2;
                        continue;
                    }
                } else {
                    normq++;
                    i++;
                    continue;
                }
            } else if (s[i + 1] == 'I' || s[i + 1] == '#') {
                normq++;
                i++;
                continue;
            } else {
            }
        } else {
            i++;
            continue;
        }
    }
    int baseval = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?') {
            continue;
        } else {
            if (s[i] == 'I') {
                if (is_xv(s[i + 1])) {
                    baseval--;
                }
                // else if (s[i + 1] == '?') {
                //     continue;
                // }
                else {
                    baseval++;
                }
            } else if (s[i] == 'X') {
                baseval += 10;
            } else if (s[i] == 'V') {
                baseval += 5;
            }
        }
    }
    baseval -= both * 2;
    // 这里both相当于把I由1变为-1
    while (q--) {
        int c1, c2, c3;
        cin >> c3 >> c2 >> c1;
        int n_i_1     = i_1;
        int n_doubleq = doubleq;
        int n_normq   = normq;
        int n_xv_i    = xv_i;
        int ans       = baseval;
        // try i_1
        int c1_i_1 = min(c1, n_i_1);
        n_i_1 -= c1_i_1;
        c1 -= c1_i_1;
        ans -= c1_i_1;

        // try doubleq
        int c1_doubleq = min(n_doubleq, c1);
        n_doubleq -= c1_doubleq;
        c1 -= c1_doubleq;
        ans += c1_doubleq;
        n_xv_i += c1_doubleq;

        // trynorm
        int c1_normq = min(c1, n_normq);
        n_normq -= c1_normq;
        c1 -= c1_normq;

        ans += c1_normq;

        // try xv_i
        int c1_xv_i = min(c1, n_xv_i);
        n_xv_i -= c1_xv_i;
        c1 -= c1_xv_i;
        ans += c1_xv_i;
        // IIIV?
        n_normq += n_doubleq * 2 + n_i_1 + n_xv_i;
        ans -= n_xv_i * 2;
        int c2_normq = min(n_normq, c2);
        n_normq -= c2_normq;
        c2 -= c2_normq;
        ans += c2_normq * 5;
        ans += n_normq * 10;
        cout << ans << '\n';
    }
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
