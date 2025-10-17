#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> left(n, 1);
    vector<int> right(n, 1);

    // Compute left[i] - length of increasing sequence ending at i
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i - 1]) {
            left[i] = left[i - 1] + 1;
        }
    }

    // Compute right[i] - length of increasing sequence starting at i
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            right[i] = right[i + 1] + 1;
        }
    }

    int ans = *max_element(left.begin(), left.end());  // without removing any

    // Check removing middle elements
    for (int i = 1; i < n - 1; i++) {
        if (a[i - 1] < a[i + 1]) {
            ans = max(ans, left[i - 1] + right[i + 1]);
        }
    }

    // Check removing first or last element
    if (n > 1) {
        ans = max(ans, right[1]);     // remove first element
        ans = max(ans, left[n - 2]);  // remove last element
    }

    cout << ans << endl;

    return 0;
}