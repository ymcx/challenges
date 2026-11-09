use std::collections::HashMap;

fn find_target_sum_ways(nums: Vec<i32>, target: i32) -> i32 {
    let mut freqs = HashMap::from([(0, 1)]);

    for n in nums {
        let mut next = HashMap::new();

        for (k, v) in freqs {
            *next.entry(k + n).or_insert(0) += v;
            *next.entry(k - n).or_insert(0) += v;
        }

        freqs = next;
    }

    freqs.get(&target).cloned().unwrap_or_default()
}

fn example1() {
    let nums = vec![1, 1, 1, 1, 1];
    let target = 3;
    assert_eq!(find_target_sum_ways(nums, target), 5);
}

fn example2() {
    let nums = vec![1];
    let target = 1;
    assert_eq!(find_target_sum_ways(nums, target), 1);
}

fn example3() {
    let nums = vec![1, 1];
    let target = 0;
    assert_eq!(find_target_sum_ways(nums, target), 2);
}

fn main() {
    example1();
    example2();
    example3();
}
