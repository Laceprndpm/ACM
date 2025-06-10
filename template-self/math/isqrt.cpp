#include <cassert>
#include <type_traits>

// See:
// [1]: Richard P. Brent and Paul Zimmermann. Modern Computer Arithmetic.
// Returns floor(sqrt(m))
template <typename Int>
std::enable_if_t<std::is_integral_v<Int>, Int> sqrt_int(Int m)
{
    assert(m >= 0);
    if (m == 0) return 0;

    Int u = m;
    for (;;) {
        Int s = u;
        u     = (s + m / s) / 2;
        if (u >= s) return s;
    }
}