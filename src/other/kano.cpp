#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<pair<size_t, size_t>> mp;

inline void init(const string& input)
{
    size_t j = 0;
    for (size_t i = 0; i <= input.size(); ++i) {
        if (i == input.size() || input[i] == '+') {
            size_t mask = 0, val = 0;
            for (size_t k = j; k < i; ++k) {
                const char   c     = input[k];
                const size_t shift = toupper(c) - 'A';
                mask |= 1u << shift;
                if (isupper(c)) val |= 1u << shift;
            }
            mp.emplace_back(mask, val);
            j = i + 1;
        }
    }
}

inline char check(size_t x)
{
    for (const auto& [mask, val] : mp) {
        if ((x & mask) == val) return '1';
    }
    return '0';
}

size_t gene(size_t seed, size_t n)
{
    size_t ans = 0;
    for (size_t i = 1; i <= n; ++i) {
        const size_t mod    = 1u << (i + 1);
        const size_t inseed = seed % mod;
        ans <<= 1;
        ans |= (inseed > (1u << (i - 1))) && (inseed <= (3u << (i - 1)));
    }
    return ans;
}

int main()
{
    string input;
    cin >> input;

    char maxC = 'A';
    for (char c : input) {
        if (isalpha(c)) maxC = max(maxC, (char)toupper(c));
    }
    const size_t n          = maxC - 'A' + 1;
    const size_t upper_bits = (n + 1) / 2;
    const size_t lower_bits = n / 2;

    init(input);

    const size_t lower_limit = 1u << lower_bits;
    const size_t upper_limit = 1u << upper_bits;
    vector<char> buffer(upper_limit + 1);  // +1 for '\n'

    for (size_t j = 1; j <= lower_limit; ++j) {
        const size_t key2 = gene(j, lower_bits);
        char*        ptr  = buffer.data();
        for (size_t i = 1; i <= upper_limit; ++i) {
            const size_t key1 = gene(i, upper_bits);
            *ptr++            = check((key2 << upper_bits) | key1);
        }
        *ptr++ = '\n';
        fwrite(buffer.data(), 1, ptr - buffer.data(), stdout);
    }
}