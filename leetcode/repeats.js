// Beats 99.47%

/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLongestSubstring = function(s) {
    let returning = 0;
    let current = 0;

    for(let i = 0; i < s.length; i++) {
        for(let j = current; j < i; j++) {
            if(s[i] === s[j]) {
                if (i - current > returning)
                    returning = i - current;

                current = j + 1;
                break;
            }
        }
    }

    if (s.length - current > returning)
        returning = s.length - current;

    return returning;
};
