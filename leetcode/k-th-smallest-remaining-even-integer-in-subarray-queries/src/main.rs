fn kth_remaining_integer_query(nums: &Vec<i32>, l: usize, r: usize, k: i32) -> i32 {
    let mut count = 0;
    for &num in &nums[l..=r] {
        if num > (k + count) * 2 {
            break;
        }

        if num % 2 == 0 {
            count += 1;
        }
    }

    (k + count) * 2
}

fn kth_remaining_integer(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> Vec<i32> {
    let mut answers = Vec::with_capacity(queries.len());
    for query in &queries {
        let (l, r, k) = (query[0], query[1], query[2]);
        let answer = kth_remaining_integer_query(&nums, l as usize, r as usize, k);
        answers.push(answer);
    }

    answers
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
    for _ in 0..200000 {
        example1();
        example2();
        example3();
        example4();
    }
}
