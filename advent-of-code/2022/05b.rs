use std::io::{self, Read};

fn parse_instruction(instruction: &str) -> (usize, usize, usize) {
    let instruction: Vec<&str> = instruction.split(' ').collect();

    (
        instruction[1].parse().unwrap(),
        instruction[3].parse().unwrap(),
        instruction[5].parse().unwrap(),
    )
}

fn parse_input() -> (Vec<Vec<char>>, Vec<(usize, usize, usize)>) {
    let mut text = String::default();
    io::stdin().read_to_string(&mut text).ok();
    let (boxes_raw, instructions_raw) = text.split_once("\n\n").unwrap();

    let boxes_raw: Vec<&str> = boxes_raw.split('\n').collect();
    let amount = boxes_raw
        .last()
        .unwrap()
        .chars()
        .nth_back(1)
        .unwrap()
        .to_digit(10)
        .unwrap() as usize;

    let mut boxes = vec![vec![]; amount];
    for line in boxes_raw.iter().rev().skip(1) {
        for i in 0..amount {
            let index = 1 + 4 * i;
            let char = line.chars().nth(index).unwrap();
            if char == ' ' {
                continue;
            }

            boxes[i].push(char);
        }
    }

    let instructions = instructions_raw
        .split('\n')
        .filter(|i| !i.is_empty())
        .map(|i| parse_instruction(i))
        .collect();

    (boxes, instructions)
}

fn main() {
    let (mut boxes, instructions) = parse_input();
    for (amount, from, to) in instructions {
        let len = boxes[from - 1].len();
        for _ in 0..amount {
            let value = boxes[from - 1].remove(len - amount);
            boxes[to - 1].push(value);
        }
    }

    let string: String = boxes.iter().map(|i| i.last().unwrap()).collect();
    println!("{}", string);
}
