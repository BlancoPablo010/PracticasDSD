import http from 'node:http'

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
  res.write(`<h1>${output}</h1>`)
  res.end()
})
.listen(8080)

console.log('Server running at http://localhost:8080/')