fn print_vec<T: std::fmt::Display>(input: &Vec<T>) {
    for x in input {
        println!("{}", x);
    }

    println!("Printed Vector!");
}

fn min<T: std::cmp::PartialOrd> (x1: T, x2: T) -> T {
    if x1 < x2 {
        return x1;
    }

    return x2;
}

fn dist(first: &str, second: &str) -> usize {
    match (first.len(), second.len()) {
        (0, x) => return x,
        (x, 0) => return x,
        (_, _) => {
            let o1 = dist(&first[1..first.len()], &second[1..second.len()]) + {
                if first[0..1] == second[0..1] {
                    0
                }
                else {
                    1
                }
            };

            let o2 = 1 + dist(&first[1..first.len()], &second);
            let o3 = 1 + dist(&first, &second[1..second.len()]);

            return min(min(o1, o2), o3);
        }
    };
}

fn fuzzy(matching: &str, input: &mut Vec<&str>) {
    if input.len() < 2 {
        return;
    }

    if input.len() != 2 {
        for i in 0..=(input.len() / 2) {
            for j in 0..(input.len() - 1 - i) {
                if dist(matching, input[j]) > dist(matching, input[j + 1]) {
                    input.swap(j, j + 1);
                }
            }
        }
    }

    if dist(matching, input[0]) > dist(matching, input[1]) { //I know this is dumb
        input.swap(0, 1);
    }
}

fn main() {
    let mut vec = vec!["First", "Second", "Third"];
    fuzzy("Sec", &mut vec);

    print_vec(&vec);
}
