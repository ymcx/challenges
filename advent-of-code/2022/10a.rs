use std::io;

fn main() {
    let mut x = 1;
    let mut i = 0;
    let mut result = 0;

    for line in io::stdin().lines().map(Result::unwrap) {
        let mut line = line.split_ascii_whitespace();
        line.next();

        i += 1;
        if (i + 20) % 40 == 0 {
            result += i * x;
        }

        if let Some(number) = line.next() {
            i += 1;
            if (i + 20) % 40 == 0 {
                result += i * x;
            }

            x += number.parse::<i32>().unwrap();
        }
    }

    println!("{}", result);
}
