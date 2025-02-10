#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void quary(int a, int b)
{
    if (a > b)
        swap(a, b);
    cout << '?' << ' ' << a << ' ' << b << endl;
}

void confirm(int x)
{
    cout << '!' << ' ' << x;
}

void binarySearchL(int secondIdx, int bound)
{
    int l = bound;
    int r = secondIdx;
    {
        quary(secondIdx - 1, secondIdx);
        int temp;
        cin >> temp;
        if (temp == secondIdx) {
            confirm(secondIdx - 1);
            return;
        }
    }
    while (l < r) {
        int mid = ((l + r - 1) >> 1) + 1;
        quary(secondIdx, mid);
        int input;
        cin >> input;
        if (input == secondIdx) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    confirm(r);
    return;
}

void binarySearchR(int secondIdx, int bound)
{
    int l = secondIdx;
    int r = bound;
    {
        quary(secondIdx + 1, secondIdx);
        int temp;
        cin >> temp;
        if (temp == secondIdx) {
            confirm(secondIdx + 1);
            return;
        }
    }
    while (l < r) {
        int mid = (l + r) >> 1;
        quary(secondIdx, mid);
        int input;
        cin >> input;
        if (input == secondIdx) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    confirm(r);
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    if (n == 2) {
        quary(1, 2);
        int temp;
        cin >> temp;
        if (temp == 1)
            confirm(2);
        else
            confirm(1);
        return 0;
    }
    quary(1, n);
    int secondInx;
    cin >> secondInx;
    if (secondInx == 1) {
        binarySearchR(1, n);
        return 0;
    }
    if (secondInx == n) {
        binarySearchL(n, 1);
        return 0;
    }
    quary(1, secondInx);
    int temp;
    cin >> temp;
    if (temp == secondInx) {
        binarySearchL(secondInx, 1);
    } else {
        binarySearchR(secondInx, n);
    }
    return 0;
}