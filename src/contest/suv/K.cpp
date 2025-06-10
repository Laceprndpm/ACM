#include <bits/stdc++.h>
#include <vector>
using namespace std;
int a[60][60];
void Tokisaki()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j]=j;
        }
    }
    a[2][1] = a[1][1] + n;
    a[2][2] = a[1][2] + n;
    for (int i = 3; i <= n; i++) {
        a[i][1]=a[i][2]=i+n;
    }
    cout<<"Yes\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout<<a[i][j]<<' ';
        }
        cout<<'\n';
    }
}

int main()
{
    int _=1;
    //cin >> _;
    while (_--)
        Tokisaki();
    return 0;
}