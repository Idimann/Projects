function add(first, second) {
    return (first + 0) + (second + 0);
}

// import readline module
import { createInterface } from "readline";

// create interface for input and output
const rl = createInterface({
    input: process.stdin,
    output: process.stdout,
});

// create empty user input
let first = "";
let second = "";

// question user to enter name
rl.question("First number\n", (string) => {
    first = string;
});

rl.question("Second number\n", (string) => {
    second = string;
});

console.log(add(parseInt(first), parseInt(second)));

// close input stream
rl.close();
