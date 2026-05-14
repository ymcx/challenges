use std::{cmp, collections::HashMap, io, path::PathBuf};

fn cd(line: &str, directory: &PathBuf) -> PathBuf {
    let mut directory = directory.clone();

    let next = line.split(' ').last().unwrap();
    if next == ".." {
        directory.pop();
    } else {
        directory.push(PathBuf::from(next));
    }

    directory
}

fn ls(line: &str, directory: &PathBuf) -> (PathBuf, u32) {
    let (size, file) = line.split_once(' ').unwrap();

    let mut directory = directory.clone();
    directory.push(file);

    let size = size.parse().unwrap_or_default();
    (directory, size)
}

fn main() {
    let lines: Vec<String> = io::stdin().lines().map(|i| i.unwrap()).collect();
    let mut directory = PathBuf::from("/");
    let mut files: HashMap<PathBuf, u32> = HashMap::new();

    for line in lines {
        if line.starts_with("$ cd") {
            directory = cd(&line, &directory);
        } else if !line.starts_with("$") {
            let (file, size) = ls(&line, &directory);
            files.insert(file, size);
        }
    }

    let needed = files.values().sum::<u32>() - 40000000;
    let mut result = u32::MAX;

    for (directory, &score) in files.iter() {
        if score != 0 {
            continue;
        }

        let mut sum = 0;
        for (d, &s) in files.iter() {
            if d.starts_with(directory) {
                sum += s;
            }
        }

        if sum >= needed {
            result = cmp::min(result, sum);
        }
    }

    println!("{}", result);
}
