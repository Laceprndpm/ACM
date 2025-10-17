#include <iostream>
using namespace std;

int main()
{
    int t = 0;  // 测试用例数量
    cin >> t;
    int       n = 0;  // 字符串长度
    string    s;      // 测试用例
    long long arr[10000];
    for (int i = 0; i < t; i++) {
        cin >> n >> s;
        int a = 0, b = 0;  // a是-的数量 b是_的数量
        for (int j = 0; j < n; j++) {
            if (s[j] == '-') {
                a++;
            } else {
                b++;
            }  // 求出-和_的个数
        }
        if (a <= 1 || b == 0) {
            arr[i] = 0;
        } else {
            long long m = a / 2;
            int       n = a / 2 + a % 2;
            arr[i]      = m * n * b;
        }
    }
    for (int i = 0; i < t; i++) {
        cout << arr[i] << endl;
    }
    return 0;
}