#!/bin/sh -e

echo
echo "Compilando con javac"
javac *.java




echo
echo "Introduzca el número de réplicas que desea lanzar"

read replicas

java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=127.0.0.1 -Djava.rmi.server.port=1098 -Djava.security.policy=server.policy ReplicaServidor $replicas &


echo 
echo "Pulse la tecla enter para terminar los servidores"

read input

# Obtener los IDs de todos los procesos de Java
java_pids=$(pgrep -f java.*&)

# Iterar sobre los IDs de los procesos de Java y matarlos
for pid in $java_pids; do
    kill -9 $pid
done

echo "Todos los procesos de Java han sido terminados."