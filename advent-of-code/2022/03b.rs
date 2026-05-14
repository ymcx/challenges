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

    for lines in io::stdin()
        .lines()
        .map(Result::unwrap)
        .collect::<Vec<_>>()
        .chunks(3)
    {
        for char in get_unique(&lines[0]) {
            if lines[1].contains(char) && lines[2].contains(char) {
                sum += get_priority(char);
            }
        }
    }

    println!("{}", sum);
}
