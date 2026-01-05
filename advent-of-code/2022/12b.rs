use std::{
    collections::{HashMap, VecDeque},
    io::{self, Read},
};

fn read_char(char: char) -> u32 {
    let char = match char {
        'S' => 'a',
        'E' => 'z',
        _ => char,
    };

    char as u32 - 'a' as u32
}

fn find_chars(text: &str, char: char, length: i32) -> Vec<(i32, i32)> {
    text.replace('\n', "")
        .match_indices(char)
        .map(|(i, _)| (i as i32 / length, i as i32 % length))
        .collect()
}

fn read_board() -> (Vec<Vec<u32>>, Vec<(i32, i32)>, (i32, i32), (i32, i32)) {
    let mut text = String::new();
    io::stdin().read_to_string(&mut text).unwrap();
    text.pop();

    let board: Vec<Vec<u32>> = text
        .split('\n')
        .map(|line| line.chars().map(|char| read_char(char)).collect())
        .collect();
    let boundary = (board.len() as i32, board[0].len() as i32);
    let starts = [
        find_chars(&text, 'S', boundary.1),
        find_chars(&text, 'a', boundary.1),
    ]
    .concat();
    let end = find_chars(&text, 'E', boundary.1)[0];

    (board, starts, end, boundary)
}

fn main() {
    let (board, starts, end, boundary) = read_board();
    let mut queue = VecDeque::from_iter(starts.into_iter().map(|start| (start, 0, 0)));
    let mut visited = HashMap::new();
    let mut result = u32::MAX;

    while !queue.is_empty() {
        let (point, steps, elevation) = queue.pop_front().unwrap();

        if point.0 < 0 || point.1 < 0 || boundary.0 <= point.0 || boundary.1 <= point.1 {
            continue;
        }

        if visited.get(&point).map_or(false, |&i| i <= steps) {
            continue;
        }

        let elevation_new = board[point.0 as usize][point.1 as usize];
        if elevation + 1 < elevation_new {
            continue;
        }

        if point == end {
            result = result.min(steps);
        }

        visited.insert(point, steps);

        for point in [
            (point.0 + 1, point.1),
            (point.0 - 1, point.1),
            (point.0, point.1 + 1),
            (point.0, point.1 - 1),
        ] {
            queue.push_back((point, steps + 1, elevation_new));
        }
    }

    println!("{}", result);
}
