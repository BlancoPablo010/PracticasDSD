import http from 'node:http'
import { join } from 'node:path' 
import { readFile } from 'node:fs'
import { Server } from 'socket.io'

const httpServer = http
  .createServer((req, res) => {
    let { url } = req
    if (url == '/') {
      url = '/connections.html'
      const filename = join(process.cwd(), url)

      readFile(filename, (err, data) => {
        if (!err) {
          res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' })
          res.write(data)
        } else {
          res.writeHead(500, { 'Content-Type': 'text/plain' })
          res.write(`Error en la lectura del fichero: ${url}`)
        }
        res.end()
      })
    } else {
      console.log('Peticion no válida' + url)
      res.writeHead(404, { 'Content-Type': 'text/plain' })
      res.write('404 Not Found')
      res.end()
    }
  })

  let allClients = new Array()

  const io = new Server(httpServer)
  io.sockets.on('connection', (client) => {
    const cAddress = client.request.socket.remoteAddress
    const cPort = client.request.socket.remotePort

    allClients.push({ address: cAddress, port: cPort })
    console.log(`Nueva conexión de ${cAddress}:${cPort}`)

    io.sockets.emit('all-connections', allClients)

    client.on('output-evt', (data) => {
      client.emit('output-evt', 'Hola Cliente!')
    })

    client.on('disconnect', () => {
      console.log(`El usuario ${cAddress}:${cPort} se va a desconectar`)
      
      const index = allClients.findIndex((c) => c.address === cAddress && c.port === cPort)

      if (index !== -1) {
        allClients.splice(index, 1)
        io.socket.emit('all-connections', allClients)
      } else {
        console.log('No se ha encontrado el cliente')
      }

      console.log(`El usuario ${cAddress}:${cPort} se ha desconectado`)
    })
  })

  httpServer.listen(8080)
  console.log('Server running at http://localhost:8080/')