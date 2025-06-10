use std::io::{self, BufRead};

#[derive(Clone)]
struct Info {
    x: i64,
}

#[derive(Clone)]
struct Tag {
    x: i64,
}

impl Info {
    fn apply(&mut self, tag: &Tag) {
        self.x &= tag.x;
    }
}

impl Tag {
    fn apply(&mut self, other: &Tag) {
        self.x &= other.x;
    }
}

struct LazySegmentTree {
    n: usize,
    info: Vec<Info>,
    tag: Vec<Tag>,
}

impl LazySegmentTree {
    fn new(arr: &[Info]) -> Self {
        let n = arr.len() - 1; // 1-based input
        let mut tree = Self {
            n,
            info: vec![Info { x: i64::MAX }; 4 * (n + 1)],
            tag: vec![Tag { x: i64::MAX }; 4 * (n + 1)],
        };
        tree.build(1, 1, n, arr);
        tree
    }

    fn build(&mut self, p: usize, l: usize, r: usize, arr: &[Info]) {
        if l == r {
            self.info[p] = arr[l].clone();
            return;
        }
        let m = (l + r) / 2;
        self.build(2 * p, l, m, arr);
        self.build(2 * p + 1, m + 1, r, arr);
        self.pull(p);
    }

    fn pull(&mut self, p: usize) {
        self.info[p].x = self.info[2 * p].x & self.info[2 * p + 1].x;
    }

    fn apply(&mut self, p: usize, tag: &Tag) {
        self.info[p].apply(tag);
        self.tag[p].apply(tag);
    }

    fn push(&mut self, p: usize) {
        let tag = self.tag[p].clone();
        if tag.x == i64::MAX {
            return;
        }
        self.apply(2 * p, &tag);
        self.apply(2 * p + 1, &tag);
        self.tag[p].x = i64::MAX;
    }

    pub fn modify_point(&mut self, pos: usize, v: &Info) {
        self.modify(1, 1, self.n, pos, v);
    }

    fn modify(&mut self, p: usize, l: usize, r: usize, pos: usize, v: &Info) {
        if l == r {
            self.info[p] = v.clone();
            return;
        }
        self.push(p);
        let m = (l + r) / 2;
        if pos <= m {
            self.modify(2 * p, l, m, pos, v);
        } else {
            self.modify(2 * p + 1, m + 1, r, pos, v);
        }
        self.pull(p);
    }

    pub fn range_apply(&mut self, l: usize, r: usize, tag: &Tag) {
        self.range_apply_internal(1, 1, self.n, l, r, tag);
    }

    fn range_apply_internal(&mut self, p: usize, cl: usize, cr: usize, l: usize, r: usize, tag: &Tag) {
        if cl > r || cr < l {
            return;
        }
        if cl >= l && cr <= r {
            self.apply(p, tag);
            return;
        }
        self.push(p);
        let m = (cl + cr) / 2;
        self.range_apply_internal(2 * p, cl, m, l, r, tag);
        self.range_apply_internal(2 * p + 1, m + 1, cr, l, r, tag);
        self.pull(p);
    }

    pub fn range_query(&mut self, l: usize, r: usize) -> Info {
        self.query(1, 1, self.n, l, r)
    }

    fn query(&mut self, p: usize, cl: usize, cr: usize, l: usize, r: usize) -> Info {
        if cl > r || cr < l {
            return Info { x: i64::MAX };
        }
        if cl >= l && cr <= r {
            return self.info[p].clone();
        }
        self.push(p);
        let m = (cl + cr) / 2;
        let left = self.query(2 * p, cl, m, l, r);
        let right = self.query(2 * p + 1, m + 1, cr, l, r);
        Info {
            x: left.x & right.x,
        }
    }

    fn range_query2(&mut self, l: usize, r: usize, bit: usize) -> i64 {
        if l > r {
            return -1;
        }
        let val = self.range_query(l, r).x;
        if (val >> bit) & 1 == 0 {
            return -1;
        }
        if l == r {
            return l as i64;
        }
        let mid = (l + r) / 2;
        let left_val = self.range_query(l, mid).x;
        let right_val = self.range_query(mid + 1, r).x;
        let left_has = (left_val >> bit) & 1 != 0;
        let right_has = (right_val >> bit) & 1 != 0;

        if left_has && right_has {
            -1
        } else if left_has {
            self.range_query2(l, mid, bit)
        } else {
            self.range_query2(mid + 1, r, bit)
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    // Read n and q
    let first_line = lines.next().unwrap().unwrap();
    let mut parts = first_line.split_whitespace();
    let n: usize = parts.next().unwrap().parse().unwrap();
    let q: usize = parts.next().unwrap().parse().unwrap();

    // Read the array
    let mut arr = vec![Info { x: i64::MAX }; n + 1];
    for i in 1..=n {
        let line = lines.next().unwrap().unwrap();
        arr[i].x = line.trim().parse().unwrap();
    }

    // Initialize the segment tree
    let mut lzt = LazySegmentTree::new(&arr);

    // Process queries
    for _ in 0..q {
        let line = lines.next().unwrap().unwrap();
        let mut parts = line.split_whitespace();
        let op: u8 = parts.next().unwrap().parse().unwrap();

        match op {
            1 => {
                let l: usize = parts.next().unwrap().parse().unwrap();
                let r: usize = parts.next().unwrap().parse().unwrap();
                let x: i64 = parts.next().unwrap().parse().unwrap();
                lzt.range_apply(l, r, &Tag { x });
            }
            2 => {
                let p: usize = parts.next().unwrap().parse().unwrap();
                let x: i64 = parts.next().unwrap().parse().unwrap();
                lzt.modify_point(p, &Info { x });
            }
            3 => {
                let l: usize = parts.next().unwrap().parse().unwrap();
                let r: usize = parts.next().unwrap().parse().unwrap();
                if l == r {
                    println!("0");
                    continue;
                }
                let m = (l + r) / 2;
                let m1 = (l + m) / 2;
                let m2 = (m + r) / 2;

                let val1 = lzt.range_query(l, m1).x;
                let val2 = lzt.range_query(m1 + 1, m).x;
                let var1 = lzt.range_query(m + 1, m2).x;
                let var2 = lzt.range_query(m2 + 1, r).x;

                let mut flag = true;
                for i in (0..=62).rev() {
                    let cnt = ((val1 >> i) & 1) as u8
                        + ((val2 >> i) & 1) as u8
                        + ((var1 >> i) & 1) as u8
                        + ((var2 >> i) & 1) as u8;
                    if cnt == 3 {
                        let p = lzt.range_query2(l, r, i);
                        if p != -1 {
                            let p = p as usize;
                            let left = if p > l {
                                lzt.range_query(l, p - 1)
                            } else {
                                Info { x: i64::MAX }
                            };
                            let right = if p < r {
                                lzt.range_query(p + 1, r)
                            } else {
                                Info { x: i64::MAX }
                            };
                            println!("{}", left.x & right.x);
                            flag = false;
                            break;
                        }
                    }
                }
                if flag {
                    println!("{}", val1 & val2 & var1 & var2);
                }
            }
            _ => panic!("Invalid operation"),
        }
    }
}