//Idk why this is called binarySearch but it is
function binarySearch(list, point) {
    let min = 0;
    let max = list.length - 1;

    //Hacky fix
    if(list[max] === point)
        return max;

    while(max > min) {
        let mid = Math.floor(min + (max - min) / 2);

        if(list[mid] === point)
            return mid;
        else if(list[mid] > point)
            max = mid;
        else
            min = mid;
    }

    return -1;
}

function test() {
    const list = [
        1,
        4,
        7,
        9,
        69,
        420,
        523523
    ];

    list.forEach((x) => {
        console.log(binarySearch(list, x));
    })
}

test();
