template <typename RandomIt, typename Compare = std::less<>>
i64 mergesort(RandomIt first, RandomIt last, Compare cmp = Compare())
{
    using T        = typename std::iterator_traits<RandomIt>::value_type;
    const auto len = std::distance(first, last);
    if (len <= 1) return 0;

    std::vector<T> buffer(len);
    auto           mid = first + len / 2;
    i64            ans = 0;
    // 递归排序左右两半
    ans += mergesort(first, mid, cmp);
    ans += mergesort(mid, last, cmp);

    // 归并阶段
    auto it   = buffer.begin();
    auto left = first, right = mid;
    while (left != mid && right != last) {
        if (cmp(*right, *left)) {
            ans += mid - left;
            *it++ = std::move(*right++);
        } else {
            *it++ = std::move(*left++);
        }
    }
    it = std::move(left, mid, it);
    it = std::move(right, last, it);
    std::move(buffer.begin(), buffer.begin() + len, first);
    return ans;
}