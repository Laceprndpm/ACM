#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, r;
int b_num[] = {1,     10,    11,    100,   101,   110,   111,   1000,  1001,  1010,  1011,
               1100,  1101,  1110,  1111,  10000, 10001, 10010, 10011, 10100, 10101, 10110,
               10111, 11000, 11001, 11010, 11011, 11100, 11101, 11110, 11111, 100000};

void R(int cur, int th, int depth)  // 从 start(包含) 开始，深度为 depth，还剩 r 个数
{
    if (cur > 1e5) {
        return;
    }
    if (th / 5 >= 31) {
        return;
    }
    if (depth == 6) {
        cout << cur << '\n';
        return;
    }
    int cur_num = b_num[th / 5];
    R(cur * cur_num, th + 1, depth + 1);
    // 选择这个数
    R(cur, th + 1, depth);
    // 不选择这个数
}

int main() {
    freopen("pre_ans", "w", stdout);
    R(1, 0, 0);
    // cout << sizeof(b_num); // <-bug源头
    return 0;

    // freopen("pre_ans", "r", stdin);
    // freopen("true_ans", "w", stdout);
    // set<int> s;
    // while (1) {
    //     int num;
    //     cin >> num;
    //     if (num == -1) {
    //         break;
    //     }
    //     s.insert(num);
    // }
    // for (auto iter : s) {
    //     cout << iter << ',';
    // }
    // return 0;
}
