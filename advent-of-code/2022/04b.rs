use std::io;

fn split(line: &str) -> (u32, u32, u32, u32) {
    let parse = |i: &str| i.parse().unwrap();
    let (ab, cd) = line.split_once(',').unwrap();
    let (a, b) = ab.split_once('-').unwrap();
    let (c, d) = cd.split_once('-').unwrap();

    (parse(a), parse(b), parse(c), parse(d))
}

fn main() {
    let lines: Vec<_> = io::stdin().lines().map(|i| split(&i.unwrap())).collect();
    let mut sum: u32 = 0;

    for line in lines {
        let latter_on_left = line.3 < line.0;
        let latter_on_right = line.1 < line.2;

        if !latter_on_left && !latter_on_right {
            sum += 1;
        }
    }

    println!("{}", sum);
}
