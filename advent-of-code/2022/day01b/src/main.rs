use std::io;

fn main() {
    let numbers: Vec<u32> = io::stdin()
        .lines()
        .map(|i| i.unwrap().parse().unwrap_or_default())
        .collect();

    let length = numbers.iter().filter(|&&i| i == 0).count() + 1;
    let mut sum = vec![0; length];
    let mut i = 0;

    for number in numbers {
        if number == 0 {
            i += 1;
        }

        sum[i] += number;
    }

    sum.sort();
    let sum: u32 = sum[length - 3..].iter().sum();

    println!("{}", sum);
}
