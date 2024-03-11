/* dir.x : Protocolo de listado de directorio remoto */
  const MAX= 1;                             /* longitud máxima de la entrada del operador */
  const MAX_SIZE = 10;                       /* longitud máxima de las matrices y vectores */
  typedef double vector_t<MAX_SIZE>;
  typedef vector_t matrix<MAX_SIZE>;
  typedef string operatorType<MAX>;                               /* entrada del operador */  
  typedef struct Operation operation;                /* estructura de la operación basica */
  typedef struct OperationMatrix operationMatrix; /* estructura de la operación matricial */

  struct Operation{
    double firstNumber;                 /* primer double de la operación */
    operatorType operator;                   /* operador de la operación */
    double secondNumber;               /* segundo double de la operación */
  };

  struct OperationMatrix{
    int size;
    matrix firstMatrix;
    operatorType operator;
    matrix secondMatrix;
    double escalar;
  };


  /* La siguiente unión se utiliza para discriminar entre llamadas
   *                 con éxito y llamadas con errores               */
  union calculator_res switch (int errnum) {
    case 0:
      double res; /* sin error: resultado de la operación */
    default:
      void;               /* con error: nada */
  };

  union calculator_2_res switch (int errnum) {
    case 0:
      matrix res;
    default:
      void;
  };


  program CALPROG {
    version CALVER1 {
      calculator_res CALCULATOR(operation) = 1;
    } = 1;
    version CALVER2 {
      calculator_2_res CALCULATOR_MATRIX(operationMatrix) = 1;
    } = 2;
  } = 0x20000155;