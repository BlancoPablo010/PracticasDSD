#!/bin/sh -e
echo "Compilando con javac"
javac Cliente.java

echo
echo "Lanzando el cliente"
echo
java -cp . -Djava.security.policy=server.policy Cliente 

