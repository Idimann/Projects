//Works but is too slow to even submit lmfao

/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var threeSum = function(nums) {
    let result = []

    for(let i = 0; i < nums.length; i++) {
        for(let j = 0; j < i; j++) {
            for(let k = 0; k < j; k++) {
                if(nums[i] + nums[j] + nums[k] === 0) {
                    const adding = [nums[i], nums[j], nums[k]].sort();
                    let canAdd = true;

                    for(let x = 0; x < result.length; x++) {
                        let temp = true;

                        for(let y = 0; y < 3; y++) {
                            if(result[x][y] !== adding[y]) {
                                temp = false;
                                break;
                            }
                        }

                        if(temp) {
                            canAdd = false;
                            break;
                        }
                    }

                    if(canAdd)
                        result.push(adding);
                }
            }
        }
    }

    return result
};
