#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 maxn(int n)
{
    char c;
    i64  num1 = 0;
    for (int i = 0; i < n; i++) {
        scanf("%c", &c);
        if (c == '-') {
            num1++;
        }
    }
    if (num1 == 1 || num1 == 0 || num1 == n) {
        return 0;
    } else {
        i64 num = num1 / 2;
        i64 mul = (n - num1) * num * (num1 - num);
        return mul;
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        int rel = maxn(x);
        printf("%d\n", rel);
    }
    return 0;
}