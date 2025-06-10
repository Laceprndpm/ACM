#include <iostream>
using namespace std;
using i64 = long long;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 2) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}