#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int& i : arr) cin >> i;
    m %= n;
    for (int i = 0; i < n; i++) cout << arr[(i - m + n) % n] << ' ';
}