import http from 'node:http'

http.createServer((req, res) => {
  console.log(req.headers)

  res.writeHead(200, { 'Content-Type': 'text/plain' })
  res.end('Hello World\n')
}).listen(8080)

console.log('Server running at http://localhost:8080/')