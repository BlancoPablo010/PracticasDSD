from calculadora import Calculadora


from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

transport = TSocket.TSocket("localhost", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)

transport.open()

print("Menu:")
print("1. Operación Básica")
print("2. Operación de Grados")
print("3. Operación Vectorial")
print("4. Operación Matricial")

choice = input("Ingrese el número: ")

if choice == "1":
    print("Operación Basica")
    firstNum = input("Introduzca el primer número: ")
    operation = input("Introduzca la operación(+, -, *, /):")
    secondNum = input("Introduzca el segundo número:")
    resultado = client.operacionBasica(int(firstNum), int(secondNum), operation)
    if resultado.error == 0:
        print("Resultado: %f" % resultado.res)
    elif resultado.error == 1:
        print("No se puede dividir por cero")
    else:
        print("Operación inválida")

elif choice == "2":
    print("Operación de Grados")
    operation = input("Introduzca la operación(sen, cos, tan, RAD): ")
    grados = input("Introduzca los grados: ")
    resultado = client.operacionGrados(float(grados), operation)
    if resultado.error == 0:
        print("Resultado: %f" % resultado.res)
    else:
        print("Operación inválida")

elif choice == "3":
    print("Operación Vectorial")
    length = input("Introduzca el tamaño de los vectores: ")
    firstVector = []
    secondVector = []
    for i in range(int(length)):
        firstVector.append(int(input("Introduzca el elemto %d del primer vector: " % i)))
    operation = input("Introduzca la operación(+, -, *, x): ")
    for i in range(int(length)):
        secondVector.append(int(input("Introduzca el elemto %d del segundo vector: " % i)))
    resultado = client.operacionVectorial(firstVector, secondVector, operation)
    if resultado.error == 0:
        print("Resultado: %s" % resultado.res)
    elif resultado.error == 1:
        print("La multiplicación vectorial solo se puede con tamaño de vectores 3")
    else:
        print("Operación inválida")

elif choice == "4":
    print("Operación Matricial")
    length = input("Introduzca el tamaño de las matrices: ")
    matrix1 = []
    matrix2 = []
    for i in range(int(length)):
        matrix1.append([])
        for j in range(int(length)):
            matrix1[i].append(int(input("Introduzca el elemnto %d %d de la primera matriz: " % (i, j))))
    operation = input("Introduzca la operación(+, -, *): ")
    for i in range(int(length)):
        matrix2.append([])
        for j in range(int(length)):
            matrix2[i].append(int(input("Introduzca el elemento %d %d de la segunda matriz " % (i, j))))
    resultado = client.operacionMatricial(matrix1, matrix2, operation)
    if resultado.error == 0:
        print("Resultado: ")
        for i in range(int(length)):
            print(resultado.res[i])
    else:
        print("Operación inválida")

else:
    print("Invalid choice")
