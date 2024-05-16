import http from 'node:http'
import { join } from 'node:path'
import { readFile } from 'node:fs'

function calcular(operacion, a, b) {
  switch (operacion) {
    case 'sumar':
      return a + b
    case 'restar':
      return a - b
    case 'producto':
      return a * b
    case 'dividir':
      return a / b
    default:
      return 'Operación no válida'
  }
}

http.createServer((req, res) => {

  let { url } = req
  if (url == '/') {
    url = '/calc.html'
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
    url = url.slice(1)
    const params = url.split('/')
    let output = ''
    if (params.length === 3) {
      const [operacion, a, b] = params
      output = calcular(operacion, Number(a), Number(b)).toString()
    } else {
      output = 'Error: el número de parámetros no es correcto'
    }

    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' })
    res.write(output)
    res.end()
  }
})
.listen(8080)

console.log('Server running at http://localhost:8080/')