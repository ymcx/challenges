use std::io;

fn is_visible(board: &Vec<Vec<u32>>, y: usize, x: usize) -> bool {
    let value = board[y][x];
    let y_max = board.len();
    let x_max = board[0].len();

    (0..y).all(|y| board[y][x] < value)
        || (0..x).all(|x| board[y][x] < value)
        || (y + 1..y_max).all(|y| board[y][x] < value)
        || (x + 1..x_max).all(|x| board[y][x] < value)
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
            result += if is_visible(&board, y, x) { 1 } else { 0 };
        }
    }

    println!("{}", result);
}
