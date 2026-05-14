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

    let mut head = (0, 0);
    let mut tail = head;
    let mut visited = HashSet::new();
    visited.insert(tail);

    for (direction, amount) in instructions {
        for _ in 0..amount {
            head = move_head(head, direction);

            if !is_close(head, tail) {
                tail = move_tail(head, tail);
                visited.insert(tail);
            }
        }
    }

    println!("{}", visited.len());
}
