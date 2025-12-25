use std::io;

fn outcome(char1: u32, char2: u32) -> u32 {
    let num1 = char1 - 'A' as u32;
    let num2 = char2 - 'X' as u32;
    (4 + num2 - num1) % 3 * 3
}

fn shape(char2: u32) -> u32 {
    char2 - 'W' as u32
}

fn main() {
    let lines: Vec<String> = io::stdin().lines().map(|i| i.unwrap()).collect();
    let lines: Vec<(&str, &str)> = lines.iter().map(|i| i.split_once(' ').unwrap()).collect();
    let mut sum = 0;

    for line in lines {
        let char1 = line.0.chars().next().unwrap() as u32;
        let char2 = line.1.chars().next().unwrap() as u32;
        sum += outcome(char1, char2) + shape(char2);
    }

    println!("{}", sum);
}
