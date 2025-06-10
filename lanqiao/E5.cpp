#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

int n, ans;
int a[10][10];
int black_location[10], white_location[10];  // 不喜欢用全局变量的大?可以写在main（）函数中指针调用

int vaild_white(int row, int conlumn)
{
    for (int i = 1; i < row; i++)
        if (conlumn == white_location[i] || abs(row - i) == abs(conlumn - white_location[i])) return 0;
    return 1;
}

int vaild_black(int row, int conlumn)
{
    for (int i = 1; i < row; i++) {
        if (conlumn == black_location[i] || abs(row - i) == abs(conlumn - black_location[i])) return 0;
    }
    return 1;
}

void Queen_black(int row)
{
    if (row == n + 1) {
        ans++;
        // return ;
    } else {
        for (int i = 1; i <= n; i++)
            if (a[row][i] == 0 || i == white_location[row])
                continue;
            else if (vaild_black(row, i)) {
                black_location[row] = i;
                Queen_black(row + 1);
            }
    }
}

void Queen_white(int row)
{
    if (row == n + 1) {
        Queen_black(1);
        return;

    } else {
        for (int i = 1; i <= n; i++)
            if (a[row][i] == 0)
                continue;
            else if (vaild_white(row, i)) {
                white_location[row] = i;
                Queen_white(row + 1);
            }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    Queen_white(1);
    printf("%d", ans);
    return 0;
}
