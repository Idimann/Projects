type maze = {
    arr: boolean[][];
};

function path(start: number, end: number, size: number[]): maze {
    if(size.length != 2)
        return { arr: [] };

    if(start >= size[1] || end >= size[1])
        return { arr: [] };

    let returning: maze = {
        arr: new Array<Array<boolean>>(size[0])
    };

    for(let i = 0; i < size[0]; i++)
        returning.arr[i] = new Array<boolean>(size[1]).fill(false);

    const allPossib = [
        [1, 0],
        [-1, 0],
        [0, 1],
        [0, -1]
    ];

    let iterating: number[] = [0, start];
    while(iterating[0] != size[0] - 1 || iterating[1] != end) {
        console.log(iterating);

        allPossib
            .filter((x) => {
                const pos = [iterating[0] + x[0], iterating[1] + x[1]];

                if(pos[0] < 0 || pos[1] < 0)
                    return false;

                if(pos[0] == size[0] - 1 || pos[1] == size[1] - 1)
                    return false;

                if(pos[0] == size[0] - 1 && pos[1] == end)
                    return true;

                if(returning.arr[pos[0]][pos[1]])
                    return false;

                for(let i = 0; i < allPossib.length; i++) {
                    if(allPossib[i] == pos)
                        continue;

                    const tempPos = [pos[0] + allPossib[i][0], pos[1] + allPossib[i][1]];

                    if(tempPos[0] < 0 || tempPos[1] < 0 ||
                       pos[0] == size[0] - 1 || pos[1] == size[1] - 1)
                        return false;

                    if(returning.arr[pos[0]][pos[1]])
                        return false;
                }

                return true;
            })
            .every((x, _i, arr) => {
                const pos = [iterating[0] + x[0], iterating[1] + x[1]];

                if(pos[0] == size[0] - 1 && pos[1] == end) {
                    iterating = pos;
                    returning.arr[iterating[0]][iterating[1]] = true;
                    return false;
                }

                if(pos[0] == size[0] - 1 &&
                   Math.abs(end - pos[1]) < Math.abs(end - iterating[1])) {
                    iterating = pos;
                    returning.arr[iterating[0]][iterating[1]] = true;
                    return false;
                }

                const prob = 1 / arr.length;

                if(prob == 1 || Math.random() <= prob) {
                    iterating = pos;
                    returning.arr[iterating[0]][iterating[1]] = true;
                    return false;
                }

                return true;
            });
    }

    return returning;
}

function display(maze: maze) {
    for (let i = 0; i < maze.arr.length; i++) {
        let output = "";
        for(let j = 0; j < maze.arr[i].length; j++) {
            //This is the right order (the ji thing)
            output += maze.arr[j][i] ? "##" : "  ";
        }

        console.log(output);
    }
}

display(path(1, 5, [7, 7]));
//console.log(path(1, 5, [7, 7]));
