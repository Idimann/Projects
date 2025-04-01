//Couldn't test this, but i'm sure its right
/**
 * @param {string} s
 * @return {number}
**/
var scoreOfString = function(s) {
    return s
        .split("")
        .map((c) => c.charCodeAt(0))
        .map((_, i, arr) => (i >= arr.length - 1) ? NaN : Math.abs(arr[i] - arr[i + 1]))
        .filter((x) => !isNaN(x))
        .reduce((x, y) => x + y);
}

console.log(scoreOfString("hello")); //13 is correct
