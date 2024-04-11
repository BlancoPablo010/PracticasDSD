struct resultBasic {
   1: i32      error,
   2: double   res
}

struct resultVector {
   1: i32         error,
   2: list<i32>   res
}

struct resultMatrix {
   1: i32               error,
   2: list<list<i32>>   res
}

service Calculadora {
   void ping(),
   resultBasic operacionBasica(1:i32 firstNum, 2:i32 secondNum, 3:string operation),
   resultBasic operacionGrados(1:double degree, 2:string operation),
   resultVector operacionVectorial(1:list<i32> firstVector, 2:list<i32> secondVector, 3:string operation),
   resultMatrix operacionMatricial(1:list<list<i32>> firstMatrix, 2:list<list<i32>> secondMatrix, 3:string operation)
}






