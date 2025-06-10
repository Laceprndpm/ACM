#include <iostream>
using namespace std;

int main()
{
    int outtemp, sta, temp;
    cin >> outtemp >> sta >> temp;
    if (sta == 1) {
        if (outtemp > 35 && temp >= 33) {
            cout << "Bu Tie\n";
            cout << outtemp << '\n';
        } else {
            cout << "Bu Re\n";
            cout << temp << '\n';
        }
    } else {
        if (outtemp > 35 && temp >= 33) {
            cout << "Shi Nei\n";
            cout << outtemp << '\n';
        } else {
            cout << "Shu Shi\n";
            cout << temp << '\n';
        }
    }
    return 0;
}