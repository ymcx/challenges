use std::{io, iter::zip};

fn split_line(line: &str) -> Vec<String> {
    let mut line: Vec<String> = line.split(',').map(String::from).collect();
    loop {
        let mut new = Vec::new();
        let mut i = 0;

        while i < line.len() {
            let j = if line[i].chars().last().unwrap().is_ascii_digit()
                && line[i + 1].chars().next().unwrap().is_ascii_digit()
            {
                2
            } else {
                1
            };

            let item = line[i..i + j].join(",");
            new.push(item);

            i += j;
        }

        if line == new {
            return line;
        }

        line = new;
    }
}

fn read_lines() -> Vec<(Vec<String>, Vec<String>)> {
    io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|i| !i.is_empty())
        .map(|i| split_line(&i))
        .collect::<Vec<Vec<String>>>()
        .chunks_exact(2)
        .map(|i| (i[0].clone(), i[1].clone()))
        .collect()
}

fn is_right_order(left: &Vec<String>, right: &Vec<String>) -> bool {
    for (left, right) in zip(left, right) {
        let left_brackets = left.chars().filter(|&i| i == '[').count();
        let right_brackets = right.chars().filter(|&i| i == '[').count();

        let left = left.replace('[', "").replace(']', "");
        let right = right.replace('[', "").replace(']', "");

        if left.is_empty() && right.is_empty() {
            if left_brackets == right_brackets {
                continue;
            }
            return left_brackets < right_brackets;
        }

        if left.is_empty() || right.is_empty() {
            return left.is_empty();
        }

        let left: Vec<u32> = left.split(',').map(|i| i.parse().unwrap()).collect();
        let right: Vec<u32> = right.split(',').map(|i| i.parse().unwrap()).collect();

        for (x, y) in zip(&left, &right) {
            if x == y {
                continue;
            }
            return x < y;
        }

        if left.len() == right.len() {
            continue;
        }

        return left.len() < right.len();
    }

    panic!();
}

fn get_result(lines: &Vec<(Vec<String>, Vec<String>)>) -> usize {
    lines
        .iter()
        .enumerate()
        .filter(|(_, (left, right))| is_right_order(left, right))
        .map(|(i, _)| i + 1)
        .sum()
}

fn main() {
    let lines = read_lines();
    let result = get_result(&lines);
    println!("{}", result);
}
