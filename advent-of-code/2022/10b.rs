use std::io;

fn contains(i: usize, x: i32) -> bool {
    let position = i as i32 % 40;
    x - 1 <= position && position <= x + 1
}

fn main() {
    let mut x = 1;
    let mut i = 0;
    let mut screen = vec![vec![' '; 40]; 6];

    for line in io::stdin().lines().map(Result::unwrap) {
        let mut line = line.split_ascii_whitespace();
        line.next();

        if contains(i, x) {
            screen[i / 40][i % 40] = '#';
        }
        i += 1;

        if let Some(number) = line.next() {
            if contains(i, x) {
                screen[i / 40][i % 40] = '#';
            }
            i += 1;
            x += number.parse::<i32>().unwrap();
        }
    }

    for row in screen {
        for item in row {
            print!("{}", item);
        }
        println!();
    }
}
