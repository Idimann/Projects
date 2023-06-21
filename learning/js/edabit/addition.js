function add(first, second) {
    return (first + 0) + (second + 0);
}

// import readline module
const readline = require("readline");

// create interface for input and output
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

// create empty user input
let first = "";
let second = "";

// question user to enter name
rl.question("First number\n", function (string) {
    first = string;
});

rl.question("Second number\n", function (string) {
    second = string;
});

console.log(add(parseInt(first), parseInt(second)));

// close input stream
rl.close();
