import io from 'socket.io-client'

const client = io('http://localhost:8080')

var ultimoSensor = {temp: 20, ilum: 200, sonido: 15}

// Cambio de sensor 
client.on('cambioUltimoSensor', (data) => {
  ultimoSensor = data

  if (ultimoSensor.temp > 30) {
    client.emit('alertaTemperaturaAlta')
  }
  if (ultimoSensor.temp > 15 && ultimoSensor.temp < 30) {
    client.emit('alertaTemperaturaNormal')
  }
  if (ultimoSensor.temp < 15) {
    client.emit('alertaTemperaturaBaja')
  }
  if (ultimoSensor.ilum > 1000) {
    client.emit('alertaIluminacionAlta')
  }
  if (ultimoSensor.ilum < 100) {
    client.emit('alertaIluminacionBaja')
  }
  if (ultimoSensor.sonido > 45) {
    client.emit('alertaSonidoAlto')
  }
})
