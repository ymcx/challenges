use std::io::{self, Read};

fn iterate(monkeys: &mut Vec<(Vec<u64>, bool, u64, u64, u64, u64, u64, u64)>) {
    let product: u64 = monkeys.iter().map(|i| i.4).product();

    for i in 0..monkeys.len() {
        while !monkeys[i].0.is_empty() {
            monkeys[i].7 += 1;

            let item = monkeys[i].0.remove(0);
            let operand_left = if monkeys[i].2 == 0 {
                item
            } else {
                monkeys[i].2
            };
            let operand_right = if monkeys[i].3 == 0 {
                item
            } else {
                monkeys[i].3
            };
            let item = if monkeys[i].1 {
                operand_left + operand_right
            } else {
                operand_left * operand_right
            } % product;
            let test = item % monkeys[i].4 == 0;
            let destination = if test { monkeys[i].5 } else { monkeys[i].6 } as usize;

            monkeys[destination].0.push(item);
        }
    }
}

fn get_last_number(string: &str) -> u64 {
    string.split(' ').last().unwrap().parse().unwrap()
}

fn main() {
    let mut text = String::new();
    io::stdin().read_to_string(&mut text).unwrap();
    let mut monkeys = Vec::new();

    for lines in text.split("\n\n") {
        let lines: Vec<&str> = lines.split('\n').collect();

        let items = lines[1][18..]
            .split(", ")
            .map(str::parse)
            .map(Result::unwrap)
            .collect();

        let equation: Vec<&str> = lines[2][19..].split(' ').collect();
        let operator = equation[1] == "+";
        let operand_left = equation[0].parse().unwrap_or_default();
        let operand_right = equation[2].parse().unwrap_or_default();

        let test = get_last_number(lines[3]);
        let destination_true = get_last_number(lines[4]);
        let destination_false = get_last_number(lines[5]);
        let inspections = 0;

        let monkey = (
            items,
            operator,
            operand_left,
            operand_right,
            test,
            destination_true,
            destination_false,
            inspections,
        );
        monkeys.push(monkey);
    }

    for _ in 0..10000 {
        iterate(&mut monkeys);
    }

    monkeys.sort_by_key(|i| -(i.7 as i64));
    let level = monkeys[0].7 * monkeys[1].7;
    println!("{}", level);
}
