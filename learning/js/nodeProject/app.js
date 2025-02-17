import { createServer } from 'http';

const hostname = '127.0.0.1';
const port = 3000;

function filter(list, filterFunc) {
    let returning = [];

    for(const e of list) {
        if(filterFunc(e))
            returning.push(e);
    }

    return returning;
}

function map(list, mapFunc) {
    let returning = [];

    for(const e of list) {
        returning.push(mapFunc(e));
    }

    return returning;
}

const server = createServer((_req, res) => {
    let list = [3, 4, 5];

    list = map(list, (x) => {
        return x + 1;
    });

    list = filter(list, (x) => {
        return x % 2 == 0;
    });

    console.log(list);

    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/plain');
    res.end('Hello World');
});

server.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
});
