/* dir.x : Protocolo de listado de directorio remoto */
  const MAX= 1;            /* longitud máxima de la entrada del operador */
  typedef string operatorType<MAX>;              /* entrada del operador */  
  typedef struct Operation *operation;       /* estructura de la operación completa */

  struct Operation{
    double firstNumber;                 /* primer double de la operación */
    operatorType operator;                   /* operador de la operación */
    double secondNumber;               /* segundo double de la operación */
    double result;                          /* resultado de la operación */
  };

  /* La siguiente unión se utiliza para discriminar entre llamadas
   *                 con éxito y llamadas con errores               */
  union calculator_res switch (int errnum) {
    case 0:
      namenode res; /* sin error: resultado de la operación */
    case 1:
      void;        /* con error: intentando dividir entre 0 */
    case 2:
      void;     /* con error: error al seleccionar operador */
    case 3:
      void;                              /* con error: nada */
  };

    program CALPROG {
        version CALVER {
            calculator_res CALCULATOR() = 1;
        } = 1;
    } = 0x20000155;
