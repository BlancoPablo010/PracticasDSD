import http          from 'node:http'
import {join}        from 'node:path'
import {readFile}    from 'node:fs'
import {Server}      from 'socket.io'
import {MongoClient} from 'mongodb'

const httpServer = http
    .createServer((request, response) => {
        let {url} = request
        if(url == '/') {
            url = '/servidor.html'
            const filename = join(process.cwd(), url)

            readFile(filename, (err, data) => {
                if(!err) {
                    response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
                    response.write(data)
                } else {
                    response.writeHead(500, {"Content-Type": "text/plain"})
                    response.write(`Error en la lectura del fichero: ${url}`)
                }
                response.end()
            });
        } else if (url == '/usuario') {
          url = '/usuario.html'
            const filename = join(process.cwd(), url)

            readFile(filename, (err, data) => {
                if(!err) {
                    response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
                    response.write(data)
                } else {
                    response.writeHead(500, {"Content-Type": "text/plain"})
                    response.write(`Error en la lectura del fichero: ${url}`)
                }
                response.end()
            });
        }
        else {
            console.log('Peticion invalida: ' + url)
            response.writeHead(404, {'Content-Type': 'text/plain'})
            response.write('404 Not Found\n')
            response.end()
        }
    });

var actuadores = {persiana: true, aireAcondicionado: false, radio:false, calefaccion: false}

MongoClient.connect('mongodb://localhost:27017')
    .then(db => {
        const dbo = db.db('domotica')
        const collection = dbo.collection('sensores')

        const io = new Server(httpServer)
        
        io.sockets.on('connection', (client) => {
            const cAddress = client.request.socket.remoteAddress
            const cPort = client.request.socket.remotePort
        
            console.log(`Nueva conexión de ${cAddress}:${cPort}`)
        
            client.on('disconnect', () => {
                console.log(`El usuario ${cAddress}:${cPort} se va a desconectar`)
            })
        
            // Cambio de sensores
            client.on('postSensores', (data) => {
              client.emit('sensoresRecibidos', 'Datos recibidos!')
              const sensor = {temp: parseFloat(data.temp), ilum: parseFloat(data.ilum), sonido: parseFloat(data.sonido), fecha: new Date()}

              collection.insertOne(sensor)
                
              const ultimoSensor = {temp: sensor.temp, ilum: sensor.ilum, sonido: sensor.sonido}
              client.broadcast.emit('cambioUltimoSensor', ultimoSensor)
              
            })

            // Obtener todo el historial de sensores
            client.on('getSensores', () => {
              collection.find({}).toArray()
                .then(results => {
                  if (results.length !== 0) {
                    var sensores = []
                    results.forEach((r) => {
                      sensores.push(
                        `Temperatura: ${r.temp}ºC, Iluminación: ${r.ilum} lux, Sonido: ${r.sonido} dB, Fecha: ${r.fecha.toLocaleString()}`
                      )
                    })
                    client.emit('sensores', sensores)
                  }
                })
            })
            
            // Alertas
            client.on('alertaTemperaturaAlta', () => {
              actuadores.aireAcondicionado = true
              actuadores.calefaccion = false
              var data = {mensaje: 'Temperatura alta', actuadores: actuadores}
              client.broadcast.emit('mostrarAlerta', data)
            })

            client.on('alertaTemperaturaNormal', () => {
              actuadores.aireAcondicionado = false
              actuadores.calefaccion = false
              var data = {mensaje: 'Temperatura normal', actuadores: actuadores}
              client.broadcast.emit('mostrarAlerta', data)
            })

            client.on('alertaTemperaturaBaja', () => {
              actuadores.aireAcondicionado = false
              actuadores.calefaccion = true
              var data = {mensaje: 'Temperatura baja', actuadores: actuadores}
              client.broadcast.emit('mostrarAlerta', data)
            })

            client.on('alertaIluminacionAlta', () => {
              actuadores.persiana = true
              var data = {mensaje: 'Iluminación alta', actuadores: actuadores}
              client.broadcast.emit('mostrarAlerta', data)
            })

            client.on('alertaIluminacionBaja', () => {
              actuadores.persiana = false
              var data = {mensaje: 'Iluminación baja', actuadores: actuadores}
              client.broadcast.emit('mostrarAlerta', data)
            })

            client.on('alertaSonidoAlto', () => {
              actuadores.radio = false
              var data = {mensaje: 'Sonido alto', actuadores: actuadores}
              client.broadcast.emit('mostrarAlerta', data)
            })

            // Cambio de actuadores por el usuario
            client.on('cambiaPersiana', (data) => {
              actuadores.persiana = data.persiana
            })

            client.on('cambiaAireAcondicionado', (data) => {
              actuadores.aireAcondicionado = data.aireAcondicionado
            })

            client.on('cambiaRadio', (data) => {
              actuadores.radio = data.radio
            })

            // Obtener estado de actuadores

            client.on('getActuadores', () => {
              client.emit('actuadores', actuadores)
            })

            // Obtener sensores actuales y redigirlos al usuario

            client.on('getUltimoSensor', (data) => {
              collection.find({}).sort({fecha: -1}).limit(1).toArray()
                .then(results => {
                  if (results.length !== 0) {
                    var ultimoSensor = {temp: results[0].temp, ilum: results[0].ilum, sonido: results[0].sonido}
                    client.emit('ultimoSensor', ultimoSensor)
                  }
                })
            })
        })

    })
    .catch(err => {
        console.log('Error al conectar con la base de datos')
    })


httpServer.listen(8080)

console.log('Interfaz de servidor en http://localhost:8080/')
console.log('Interfaz de usuario en http://localhost:8080/usuario')
