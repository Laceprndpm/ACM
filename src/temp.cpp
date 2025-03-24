// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char vector[10];
//     scanf("%s", vector);
//     for (int i = strlen(vector) - 1; i >= 0; i--) {
//         putchar(vector[i]);
//     }
//     return 0;
// }
#include <stdio.h>

int main()
{
    int a = 12, b = 10;
    // scanf("%d%d", &a, &b);
    a ^= b ^= a ^= b;
    printf("%d %d", a, b);
    return 0;
}