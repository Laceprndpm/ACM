#include <iostream>
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()
#define mt      make_tuple
#define fi      first
#define se      second

void encode()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int found1 = -1;
    int i;
    for (i = 0; i < n; i++) {
        if (s[i] == '1') {
            found1 = i;
            break;
        }
    }
    if (found1 != -1) {
        for (int j = 0; j <= found1; j++) {
            s[j] = '2';
        }
    }
    cout << s << '\n';
}

void decode()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    string ns = s + s;
    int    i;
    for (i = 0; i < n; i++) {
        if (ns[i] != '2' && ns[i + 1] == '2') {
            i++;
            break;
        }
    }
    for (int j = 0; j < n; j++) {
        if (ns[i + j] == '2' && ns[i + j + 1] != '2') {
            cout << 1;
        } else if (ns[i + j] == '2') {
            cout << 0;
        } else {
            cout << ns[i + j];
        }
    }
}

void solve()
{
    string cmd;
    cin >> cmd;
    if (cmd == "Encode") {
        encode();
    } else {
        decode();
    }
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
