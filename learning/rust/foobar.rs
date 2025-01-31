fn get_str(n: i32) -> String {
    let list: Vec<(i32, &str)> = vec![
        (3, "Foo"),
        (5, "Bar"),
        (7, "Lmfao")
    ];

    let mut adding: String = "".to_string();

    for (i, name) in list {
        if n % i == 0 {
            adding = format!("{}{}", adding, name);
        }
    }

    return adding;
}

fn main() {
    for i in 1..=100 {
        println!("{}: {}!", i, get_str(i).to_string());
    }
}
