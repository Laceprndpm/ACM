#include <bits/stdc++.h>
using namespace std;
inline int generateRandomInt(int min, int max)
{
    int tmp;
    tmp = rand() % (max - min);
    tmp += min;
    return tmp;
}
int main(int argc, char *argv[])
{
    unsigned seed = static_cast<unsigned>(time(0)) * 1000 + (clock() % 1000);
    srand(seed);
    int n = generateRandomInt(1, 10);
    int H = generateRandomInt(1, 10);
    cout << n << ' ' << H << '\n';
    for (int i = 0; i < n; i++)
    {
        cout << generateRandomInt(1, 10) << " ";
    }
    cout << '\n';
    cout << endl;
    return 0;
}
