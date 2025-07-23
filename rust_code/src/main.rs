use std::io::{self, BufRead};
const MOD: i64 = 998244353;

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..t {
        solve(&mut lines);
    }
}

fn solve(lines: &mut impl Iterator<Item = Result<String, io::Error>>) {
    let first_line = lines.next().unwrap().unwrap();
    let mut iter = first_line.split_whitespace();
    let n: i64 = iter.next().unwrap().parse().unwrap();
    let x: i64 = iter.next().unwrap().parse().unwrap();

    // sum_ai - 1 <= x
    // sum_bi = sum_ai - (1 + n) * n / 2
    // sum_bi - 1 <= x - (1 + n) * n / 2
    let sum_bi_max = x - (1 + n) * n / 2 + 1; // <= x

    if sum_bi_max < 0 {
        println!("0");
        return;
    }

    if n == 1 {
        println!("{}", x);
        return;
    }

    let sum_bi_max_usize = sum_bi_max as usize;
    let mut dp = vec![0i64; sum_bi_max_usize + 1];
    dp[0] = 1;

    for i in 2..=n {
        for j in (n - i + 1)..=sum_bi_max {
            dp[j as usize] = (dp[j as usize] + dp[(j - (n - i + 1)) as usize]) % MOD;
        }
    }

    let mut ans = 0i64;
    for i in 0..=sum_bi_max_usize {
        let ways = dp[i];
        let contrib = (sum_bi_max - i as i64 + 1) * ways % MOD;
        ans = (ans + contrib) % MOD;
    }

    println!("{}", ans);
}
