def solve(n: int, H: int) -> int:
    def check(x: int) -> bool:
        if x <= H:
            su = x * (x + 1) // 2
            return su >= n
        else:
            mid = (x - H) // 2 + 1
            su1 = (2 * H + mid - 1) * mid // 2
            length2 = x - mid
            if length2 >= 1:
                su2 = (1 + length2) * length2 // 2
            else:
                exit(1)

            su = su1 + su2
            return su >= n

    lo = 1
    hi = n
    ans = lo

    while lo <= hi:
        mid = lo + (hi - lo) // 2
        if check(mid):
            ans = mid
            hi = mid - 1
        else:
            lo = mid + 1
    return ans


n, m = map(int, input().split())
print(solve(n, m))
