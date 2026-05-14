use std::{
    collections::HashSet,
    io::{self, Read},
};

fn get_index(string: &str, length: usize) -> usize {
    let mut index = 0;
    for i in length..=string.len() {
        let mut chars = HashSet::new();
        for j in i - length..i {
            let char = string.chars().nth(j).unwrap();
            chars.insert(char);
        }

        if chars.len() == length {
            index = i;
            break;
        }
    }

    index
}

fn main() {
    let mut text = String::default();
    io::stdin().read_to_string(&mut text).ok();
    text.pop();

    let index = get_index(&text, 14);
    println!("{}", index);
}
