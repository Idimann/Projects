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
            let o1 = dist(&first[1..first.len()], &second[1..second.len()]) +
            {
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

fn main() {
    let first = "Hello";
    let second = "Bullo";

    let result = dist(&first, &second);
    println!("Result: {result}");
}
