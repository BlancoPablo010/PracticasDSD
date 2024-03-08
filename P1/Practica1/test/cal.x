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


  /* La siguiente unión se utiliza para discriminar entre llamadas
   *                 con éxito y llamadas con errores               */
  union calculator_res switch (int errnum) {
    case 0:
      double res; /* sin error: resultado de la operación */
    case 1:
      void; /* sin error: resultado de la operación matricial */
    default:
      void;               /* con error: nada */
  };


  program CALPROG {
    version CALVER {
      calculator_res CALCULATOR(operation) = 1;
    } = 1;
    version CALVER {
      calculator_res CALCULATOR(operation) = 1;
    } = 2;
  } = 0x20000155;

