#include <math.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

constexpr auto gcd_multi(auto x, auto... args)
{
    if constexpr (sizeof...(args) == 0) {
        return x;
    } else {
        if (x == 1) return 1;
        return std::gcd(x, gcd_multi(args...));
    }
}

template <class T>
class CartesianTree {
public:
    const int   n;
    vector<int> rs;
    vector<int> ls;
    vector<T>   data;
    int         treeRoot;
    vector<int> nodeGcd;

    // 1-idx
    CartesianTree(vector<T>&& _init) : n(_init.size() - 1), rs(n + 1), ls(n + 1), data(std::move(_init))
    {
        init();
    }

    CartesianTree(const vector<T>& _init) : n(_init.size() - 1), rs(n + 1), ls(n + 1), data(_init)
    {
        init();
    }

    void init() noexcept
    {
        // stk 维护笛卡尔树中节点对应到序列中的下标
        int         top = 0;
        vector<int> stk(n + 1);
        for (int i = 1; i <= n; i++) {
            int k = top;  // top 表示操作前的栈顶，k 表示当前栈顶
            while (k > 0 && data[stk[k]] > data[i])
                k--;                          // 维护右链上的节点
            if (k) rs[stk[k]] = i;            // 栈顶元素.右儿子 := 当前元素
            if (k < top) ls[i] = stk[k + 1];  // 当前元素.左儿子 := 上一个被弹出的元素
            stk[++k] = i;                     // 当前元素入栈
            top      = k;
        }
        treeRoot = stk[1];
        nodeGcd.assign(n + 1, 0);
        DFS1(treeRoot);
    }

    void DFS1(int root) noexcept
    {
        int curGcd = 0;
        if (ls[root] != 0) {
            DFS1(ls[root]);
            curGcd = gcd_multi(curGcd, nodeGcd[ls[root]], data[ls[root]] - data[root]);
        }
        if (rs[root] != 0) {
            DFS1(rs[root]);
            curGcd = gcd_multi(curGcd, nodeGcd[rs[root]], data[rs[root]] - data[root]);
        }
        nodeGcd[root] = curGcd;
    }

    bool check(int x) noexcept
    {
        for (int i = 1; i <= n; i++) {
            if (nodeGcd[i] % (data[i] + x) != 0) {
                return false;
            }
        }
        return true;
    }
};

vector<int> initarr(int n)
{
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    return arr;
}

void solve()
{
    i64 n, k;
    cin >> n >> k;

    CartesianTree<int> cartree(initarr(n));
    i64                totalans = 0;
    i64                cnt      = 0;
    i64                gcdans   = cartree.nodeGcd[cartree.treeRoot];
    i64                minVal   = cartree.data[cartree.treeRoot];

    if (gcdans == 0) {
        cout << k << ' ' << k * (k + 1) / 2 << '\n';
        return;
    }

    for (i64 i = 1; i <= (i64)sqrtl(gcdans) + 50; i++) {
        if (gcdans % i == 0) {
            if (i * i > gcdans) {
                break;
            }
            int x = i - minVal;
            if (x <= k && x > 0) {
                if (cartree.check(x)) {
                    cnt++;
                    totalans += x;
                }
            }
            if (i * i >= gcdans) {
                break;
            }
            x = (gcdans / i) - minVal;
            if (x <= k && x > 0) {
                if (cartree.check(x)) {
                    cnt++;
                    totalans += x;
                }
            }
        }
    }
    cout << cnt << ' ' << totalans << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// 88888888888888888888888888888888888888888888888888888888888888888888888
// 88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ -  .'|   |.'|     |  _..88
// 88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_-  .'  |.;'   |   _.!-'|  88
// 88      | `-!._  |  `;!  ;. _______________ ,'| .-' |   _!.i'     |  88
// 88..__  |     |`-!._ | `.| |_______________||."'|  _!.;'   |     _|..88
// 88   |``"..__ |    |`";.| i|_|MMMMMMMMMMM|_|'| _!-|   |   _|..-|'    88
// 88   |      |``--..|_ | `;!|l|MMoMMMMoMMM|1|.'j   |_..!-'|     |     88
// 88   |      |    |   |`-,!_|_|MMMMP'YMMMM|_||.!-;'  |    |     |     88
// 88___|______|____!.,.!,.!,!|d|MMMo * loMM|p|,!,.!.,.!..__|_____|_____88
// 88      |     |    |  |  | |_|MMMMb,dMMMM|_|| |   |   |    |      |  88
// 88      |     |    |..!-;'i|r|MPYMoMMMMoM|r| |`-..|   |    |      |  88
// 88      |    _!.-j'  | _!,"|_|M<>MMMMoMMM|_||!._|  `i-!.._ |      |  88
// 88     _!.-'|    | _."|  !;|1|MbdMMoMMMMM|l|`.| `-._|    |``-.._  |  88
// 88..-i'     |  _.''|  !-| !|_|MMMoMMMMoMM|_|.|`-. | ``._ |     |``"..88
// 88   |      |.|    |.|  !| |u|MoMMMMoMMMM|n||`. |`!   | `".    |     88
// 88   |  _.-'  |  .'  |.' |/|_|MMMMoMMMMoM|_|! |`!  `,.|    |-._|     88
// 88  _!"'|     !.'|  .'| .'|[@]MMMMMMMMMMM[@] \|  `. | `._  |   `-._  88
// 88-'    |   .'   |.|  |/| /                 \|`.  |`!    |.|      |`-88
// 88      |_.'|   .' | .' |/                   \  \ |  `.  | `._-Lee|  88
// 88     .'   | .'   |/|  /                     \ |`!   |`.|    `.  |  88
// 88  _.'     !'|   .' | /                       \|  `  |  `.    |`.|  88
// 88888888888888888888888888888888888888888888888888888888888888888888888

//                                    -
//                                   ::#
//                                    #.##
//                                 %:#+#####
//                                 ---#######
//                                  %=########%                        *@
//                                -:%*%%%%###### ***** %##############::
//                                =-%%%%%%%%%%##%#@################.# ==
//                                 :%#************%%%%%%%%%########:*.#
//                                #*****************#%%%%%%%%%%%##.%-:=
//                              **************##********%%%%%%%%%=%=*
//                            *@**************************%##%%###++
//                         @  #*#******************#******#=%%%% ::
//        +                  #*******##*******@*%**********::=*#+%
//          %               @*#**#%%%:.%%%%%%%#+*%***%*****@% +:#*#
//      .     #@            %%%%%%%%:..:%-:%%%%%=%*********#%###%***
//       @@%    #@          %%@%#%:=:....%:.=%%%:%%%%%%%***####-=  **
//       .  .     %#        %%##%:.@@.........=+#@-%%%%%%%%#:#-.%@****
//    @.  .@        @#     @%##%%..@@........-@..%#-*%.%%%%+ * .%*****@
//   .  @@  %          #@  @%##%%..@@........@@..-##%%%%%%%+  %%%*****@
// %.    - .             ##%%.===............@@.:##%%%%%%%%% %%******@
// +%    % #              @%%*%%:..............:.=%%%%%%%%% %#***@
//      %  @               . ***%%.....*::::..+*%%%%%%%%%%@ @*%@
//                         -    #%.* .+:.+..--#*#%%%@%%%%    %%
//                          #:::::::::#+. -:  .%#%@# .=@
//                          -::::-@       #=% %#%@:+:    #
//                                      @##-%###%%@@=:::
//                                      ##%---###%%%::::
//                                      ###=-###%%####=:
//                                     %%%%%%#############@
//                                   %%%%####################
//                                 %%%%%*###################@
//                                %%%%%%###################@
//                               %%%%%%*##################
//                                 %%%%################@
//                                  ..-@##########@
//                                 ..:@      ..:
//                               @..:@      ==:@
//                                #*@       @-+

