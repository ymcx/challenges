use std::{collections::HashSet, io};

fn get_priority(char: char) -> u32 {
    let priority = if char.is_lowercase() {
        char as u8 - 'a' as u8 + 1
    } else {
        char as u8 - 'A' as u8 + 27
    };

    priority as u32
}

fn get_unique(string: &str) -> HashSet<char> {
    let mut unique = HashSet::new();
    for char in string.chars() {
        unique.insert(char);
    }

    unique
}

fn main() {
    let mut sum = 0;

    for line in io::stdin().lines().map(Result::unwrap) {
        let mid = line.len() / 2;
        let (first, second) = line.split_at(mid);

        for f in get_unique(first) {
            for s in get_unique(second) {
                if f == s {
                    sum += get_priority(f);
                }
            }
        }
    }

    println!("{}", sum);
}
