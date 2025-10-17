#include <cxxabi.h>

#include <iostream>
using namespace std;

template <typename T>
void print_type(const T& x)
{
    int         status;
    const char* name     = typeid(x).name();
    char*       realname = abi::__cxa_demangle(name, 0, 0, &status);
    cout << realname << endl;
    free(realname);  // 记得释放
}

signed main(signed argc, char** argv)
{
    print_type(2147483647);
    cout << 2147483647 << '\n';
    print_type(2147483647 + 1);
    cout << (2147483647 + 1) << '\n';
    print_type(2147483647 + 1ll);
    cout << (2147483647 + 1ll) << '\n';
    print_type(2147483647 + (long long)(1));
    cout << 2147483647 + (long long)(1);
}
