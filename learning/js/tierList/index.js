const http = require('http');

const port = 8080;
const hostname = "127.0.0.1";

const server = http.createServer((req, res) => {
    res.statusCode = 200;
    res.setHeader("Content-Type", "text/plain");
    res.end("Start");
});

server.listen(port, hostname, () => {
    console.log("Server running");
});
