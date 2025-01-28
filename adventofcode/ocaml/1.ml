open Stdlib

let rec sum_lines accum =
    match In_channel.input_line In_channel.stdin with
    | Some line -> (
        match Stdlib.int_of_string_opt line with
        | Some value -> sum_lines (accum + value)
        | None -> accum
    )
    | None -> accum
;;

let counter = 5

let rec solve count times =
    if times == counter then
        count
    else
        let result = (sum_lines 0) in
        if result > count then
            (solve result (times + 1))
        else
            (solve count (times + 1))
;;

print_int (solve 0 0);
print_string "\n"
