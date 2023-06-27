print_string "Hello world!\n"

let add x y = x + y;;

let rec factorial x = 
    if x = 2 then 2
    else x * factorial (x - 1)
;;

let test = 
    let x = add 5 3 in
    factorial x;;

print_int test;

print_string "\n"
