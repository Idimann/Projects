//Barely passed (Horrifically slow (Beats 5% (lmfao)))
/**
 * @param {number[]} height
 * @return {number}
*/
var maxArea = function(height) {
    let ret = 0;

    let min = function(a, b) {
        return a < b ? a : b;
    }

    for(let i = 0; i < height.length - 1; i++) {
        for(let j = 0; j < height.length; j++) {
            if(j <= i) {
                if(height[j] > height[i])
                    break;
            }
            else {
                let value = min(height[i], height[j]) * (j - i);

                if(value > ret)
                    ret = value;
            }
        }
    }

    return ret;
}
