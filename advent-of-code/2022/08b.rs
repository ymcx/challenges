use std::io;

fn visible(board: &Vec<Vec<u32>>, y: usize, x: usize) -> usize {
    let value = board[y][x];
    let y_max = board.len();
    let x_max = board[0].len();

    let up = (0..y)
        .rev()
        .position(|y| board[y][x] >= value)
        .map(|i| i + 1)
        .unwrap_or(y);

    let left = (0..x)
        .rev()
        .position(|x| board[y][x] >= value)
        .map(|i| i + 1)
        .unwrap_or(x);

    let down = (y + 1..y_max)
        .position(|y| board[y][x] >= value)
        .map(|i| i + 1)
        .unwrap_or(y_max - y - 1);

    let right = (x + 1..x_max)
        .position(|x| board[y][x] >= value)
        .map(|i| i + 1)
        .unwrap_or(x_max - x - 1);

    up * left * down * right
}

fn main() {
    let board: Vec<Vec<u32>> = io::stdin()
        .lines()
        .map(|i| {
            i.unwrap()
                .chars()
                .map(|i| i.to_digit(10).unwrap())
                .collect()
        })
        .collect();

    let mut result = 0;
    let y_max = board.len();
    let x_max = board[0].len();

    for y in 0..y_max {
        for x in 0..x_max {
            let new = visible(&board, y, x);
            result = result.max(new);
        }
    }

    println!("{}", result);
}
