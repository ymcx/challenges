fn kth_remaining_integer(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> Vec<i32> {
    let nums: Vec<usize> = nums.into_iter().map(|i| i as usize).collect();

    queries
        .into_iter()
        .map(|query| {
            let (l, r, k) = (query[0] as usize, query[1] as usize, query[2] as usize);
            let mut count = 0;

            loop {
                let c = nums[l..=r]
                    .iter()
                    .filter(|&&i| i % 2 == 0 && i <= (k + count) * 2)
                    .count();

                if c == count {
                    break;
                }

                count = c;
            }

            ((k + count) * 2) as i32
        })
        .collect()
}

fn example1() {
    let nums = vec![1, 4, 7];
    let queries = vec![vec![0, 2, 1], vec![1, 1, 2], vec![0, 0, 3]];
    assert_eq!(kth_remaining_integer(nums, queries), vec![2, 6, 6]);
}

fn example2() {
    let nums = vec![2, 5, 8];
    let queries = vec![vec![0, 1, 2], vec![1, 2, 1], vec![0, 2, 4]];
    assert_eq!(kth_remaining_integer(nums, queries), vec![6, 2, 12]);
}

fn example3() {
    let nums = vec![3, 6];
    let queries = vec![vec![0, 1, 1], vec![1, 1, 3]];
    assert_eq!(kth_remaining_integer(nums, queries), vec![2, 8]);
}

fn example4() {
    let nums = vec![4, 6, 22, 24];
    let queries = vec![vec![0, 2, 10], vec![0, 3, 13]];
    assert_eq!(kth_remaining_integer(nums, queries), vec![26, 34]);
}

fn main() {
    example1();
    example2();
    example3();
    example4();
}
