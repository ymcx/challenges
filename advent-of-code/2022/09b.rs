use std::{collections::HashSet, io};

fn move_head(head: (i32, i32), direction: char) -> (i32, i32) {
    match direction {
        'D' => (head.0 + 1, head.1),
        'U' => (head.0 - 1, head.1),
        'R' => (head.0, head.1 + 1),
        'L' => (head.0, head.1 - 1),
        _ => panic!(),
    }
}

fn move_tail(head: (i32, i32), tail: (i32, i32)) -> (i32, i32) {
    (
        tail.0 + (head.0 - tail.0).signum(),
        tail.1 + (head.1 - tail.1).signum(),
    )
}

fn is_close(head: (i32, i32), tail: (i32, i32)) -> bool {
    for y in tail.0 - 1..tail.0 + 2 {
        for x in tail.1 - 1..tail.1 + 2 {
            if (y, x) == head {
                return true;
            }
        }
    }

    false
}

fn main() {
    let instructions: Vec<(char, u32)> = io::stdin()
        .lines()
        .map(|line| {
            let line = line.unwrap();
            let (direction, amount) = line.split_once(' ').unwrap();
            let direction = direction.chars().next().unwrap();
            let amount = amount.parse().unwrap();
            (direction, amount)
        })
        .collect();

    let mut nodes = vec![(0, 0); 10];
    let mut visited = HashSet::new();
    visited.insert(nodes[9]);

    for (direction, amount) in instructions {
        for _ in 0..amount {
            nodes[0] = move_head(nodes[0], direction);

            for i in 1..nodes.len() {
                if !is_close(nodes[i - 1], nodes[i]) {
                    nodes[i] = move_tail(nodes[i - 1], nodes[i]);
                }
            }

            visited.insert(nodes[9]);
        }
    }

    println!("{}", visited.len());
}
