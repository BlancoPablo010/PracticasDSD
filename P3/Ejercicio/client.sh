#!/bin/sh -e
echo "Compilando con javac"
javac Cliente.java

echo
echo "Introduzca el número de réplicas que desea lanzar"
read replicas
java -cp . -Djava.security.policy=server.policy Cliente $replicas

