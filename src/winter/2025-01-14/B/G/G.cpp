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
    int seed = time(0);
    if (argc > 1)
    {
        seed += stoi(argv[1]);
    }
    srand(seed);
    int n = generateRandomInt(2, 10);
    int m = generateRandomInt(8, 13);
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++)
    {
        cout << generateRandomInt(1, 10) << ' ';
    }
    cout << '\n';
    for (int i = 0; i < m; i++)
    {
        int c, a, b, temp;
        c = generateRandomInt(1, 5);
        a = generateRandomInt(1, n + 1);
        b = generateRandomInt(1, n + 1);
        if (a > b)
        {
            temp = a;
            a = b;
            b = temp;
        }
        cout << c << ' ' << a << ' ' << b << '\n';
    }
    cout << '\n';
    cout << endl;
    return 0;
}
