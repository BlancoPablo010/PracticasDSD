// Suponiendo que tienes una conexión a tu base de datos MongoDB y una colección llamada "miColeccion"

// Importa el cliente de MongoDB
import { MongoClient } from 'mongodb';

MongoClient.connect('mongodb://localhost:27017').then(db => {
    const dbo = db.db('domotica')
    const collection = dbo.collection('sensores')
    collection.deleteMany({}).then(result => {
        console.log('Se han eliminado todos los documentos de la colección')
    })
})