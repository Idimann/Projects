fn print_vec<T: std::fmt::Display>(input: Vec<T>) {
    for x in input {
        println!("{}", x);
    }

    println!("Printed Vector!");
}

fn sort<T: std::cmp::PartialOrd>(mut input: Vec<T>) -> Vec<T> {
    if input.len() < 2 {
        return input;
    }

    if input.len() != 2 {
        for i in 0..=(input.len() / 2) {
            for j in 0..(input.len() - 1 - i) {
                if input[j] > input[j + 1] {
                    input.swap(j, j + 1);
                }
            }
        }
    }

    if input[0] > input[1] { //I know this is dumb
        input.swap(0, 1);
    }

    return input;
}

fn main() {
    let mut input: Vec<f32> = vec![
        3.5, 9.7, 5.4, 6.8, 2.1
    ];

    print_vec(input.clone());
    input = sort(input);
    print_vec(input);
}
