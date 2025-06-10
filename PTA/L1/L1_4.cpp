#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

int main()
{
    int n;
    cin >> n;
    for (int i = 30; i >= 0; i--) {
        if (n >> i & 1) {
            cout << (1 << i);
            return 0;
        }
    }
    cout << 0;
    return 0;
}