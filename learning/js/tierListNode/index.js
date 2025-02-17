import { createServer } from 'node:http';
import { readFileSync } from 'fs';

// const hostname = '127.0.0.1';
const port = 3000;

const server = createServer((_req, res) => {
    res.statusCode = 200;
});

server.listen(port, () => {
    console.log('Server running on port ', port);
});

server.on('request', (req, res) => {
    if(req.method === 'GET') {
        if(req.url === '/') {
            const data = readFileSync('index.html');

            res.writeHead(200, {'Content-Type' : 'text/html'});
            return res.end(data);
        }
        else if(req.url === '/app.js') {
            const data = readFileSync('app.js');

            res.writeHead(200, {'Content-Type' : 'application/javascript'});
            return res.end(data);
        }
        else if(req.url === '/style.css') {
            const data = readFileSync('style.css');

            res.writeHead(200, {'Content-Type' : 'text/css'});
            return res.end(data);
        }
    }
});
