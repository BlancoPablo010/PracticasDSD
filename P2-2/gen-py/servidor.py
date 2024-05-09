import glob
import sys
import math

from calculadora import Calculadora
from calculadora.ttypes import resultBasic
from calculadora.ttypes import resultVector
from calculadora.ttypes import resultMatrix

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import logging

logging.basicConfig(level=logging.DEBUG)


class CalculadoraHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print("me han hecho ping()")

    def operacionBasica(self, firstNum, secondNum, operation):

        if(operation == "+"):
            return resultBasic(0, firstNum + secondNum)
        elif(operation == "-"):
            return resultBasic(0, firstNum - secondNum)
        elif(operation == "*"):
            return resultBasic(0, firstNum * secondNum)
        elif(operation == "/"):
            if (secondNum == 0):
                return resultBasic(1, 0)
            return resultBasic(0, firstNum / secondNum)
        else:
            return resultBasic(2, 0)
        
    def operacionGrados(self, grados, operation):
        if(operation == "sen"):
            return resultBasic(0, math.sin(math.radians(grados)))
        elif(operation == "cos"):
            return resultBasic(0, math.cos(math.radians(grados)))
        elif(operation == "tan"):
            return resultBasic(0, math.tan(math.radians(grados)))
        elif(operation == "RAD"):
            return resultBasic(0, math.radians(grados))
        else:
            return resultBasic(1, 0)

    def operacionVectorial(self, firstVector, secondVector, operation):
        if(operation == "+"):
            return resultVector(0, [firstVector[i] + secondVector[i] for i in range(len(firstVector))])
        elif(operation == "-"):
            return resultVector(0, [firstVector[i] - secondVector[i] for i in range(len(firstVector))])
        elif(operation == "*"):
            final = [0]
            for i in range(len(firstVector)):
                final[0] += firstVector[i] * secondVector[i]
            return resultVector(0, final)
        elif(operation == "x"):
            if(len(firstVector) == 3 and len(secondVector) == 3):
                final = [firstVector[1]*secondVector[2] - firstVector[2]*secondVector[1],
                         firstVector[2]*secondVector[0] - firstVector[0]*secondVector[2],
                         firstVector[0]*secondVector[1] - firstVector[1]*secondVector[0]]
                return resultVector(0, final)
            else:
                return resultVector(1, [0])
        else:
            return resultVector(2, [0])
        
    def operacionMatricial(self, firstMatrix, secondMatrix, operation):
        if(operation == "+"):
            final = [[firstMatrix[i][j] + secondMatrix[i][j] for j in range(len(firstMatrix))] for i in range(len(firstMatrix))]
            return resultMatrix(0, final)
        elif(operation == "-"):
            final = [[firstMatrix[i][j] - secondMatrix[i][j] for j in range(len(firstMatrix))] for i in range(len(firstMatrix))]
            return resultMatrix(0, final)
        elif(operation == "*"):
            final = [[0 for j in range(len(firstMatrix))] for i in range(len(firstMatrix))]
            for i in range(len(firstMatrix)):
                for j in range(len(firstMatrix)):
                    for k in range(len(firstMatrix)):
                        final[i][j] += firstMatrix[i][k] * secondMatrix[k][j]
            return resultMatrix(0, final)
        else:
            return resultMatrix(1, [[0]])

if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("iniciando servidor...")
    server.serve()
    print("fin")
