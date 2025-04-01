/**
 * @param {number} n
 * @return {string[]}
 */
var generateParenthesis = function(n) {
    if(n === 1) {
        return ["()"];
    }

    const prev = generateParenthesis(n - 1);
    let ret = new Array(prev.length);

    return prev;
};

console.log(generateParenthesis(3));
