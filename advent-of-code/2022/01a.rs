use std::{cmp, io};

fn main() {
    let numbers: Vec<u32> = io::stdin()
        .lines()
        .map(|i| i.unwrap().parse().unwrap_or_default())
        .collect();

    let mut max = 0;
    let mut cur = 0;

    for number in numbers {
        if number == 0 {
            max = cmp::max(cur, max);
            cur = 0;
        }

        cur += number;
    }

    println!("{}", max)
}
