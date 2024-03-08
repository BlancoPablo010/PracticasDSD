#include <stdio.h>

/*
  struct OperationMatrix{
    int size;                             /* tamaño de las matrices de la operación 
    double firstMatrix<MAX_SIZE><MAX_SIZE>;       /* primera matriz de la operación 
    operatorType operator;                              /* operador de la operación 
    double secondMatrix<MAX_SIZE><MAX_SIZE>;      /* segunda matriz de la operación 
    double escalar;                            /* escalar para un tipo de operación 
  };
*/

#define MAX_SIZE 10

struct Operacion {
    double num1;
    char operador[1];
    double num2;
    double resultado;
}  ;

struct OperacionMatricial {
    int size;
    double matriz1[MAX_SIZE][MAX_SIZE];
    char operador[1];
    double matriz2[MAX_SIZE][MAX_SIZE];
    double escalar;
    double resultado[MAX_SIZE][MAX_SIZE];
} ;

int operar(struct Operacion *operacion) {
    switch (operacion->operador[0]) {
        case '+':
            operacion->resultado = operacion->num1 + operacion->num2;
            break;
        case '-':
            operacion->resultado = operacion->num1 - operacion->num2;
            break;
        case '*':
            operacion->resultado = operacion->num1 * operacion->num2;
            break;
        case '/':
            if (operacion->num2 != 0) {
                operacion->resultado = operacion->num1 / operacion->num2;
            } else {
                return 2;
            }
            break;
        default:
            return 3;
            break;
    }
}

int operar2(struct OperacionMatricial *operacion) {
    int i, j;
    switch (operacion->operador[0]) {
        case '+':
            for (i = 0; i < operacion->size; i++) {
                for (j = 0; j < operacion->size; j++) {
                    operacion->resultado[i][j] = operacion->matriz1[i][j] + operacion->matriz2[i][j];
                }
            }
            break;
        case '-':
            for (i = 0; i < operacion->size; i++) {
                for (j = 0; j < operacion->size; j++) {
                    operacion->resultado[i][j] = operacion->matriz1[i][j] - operacion->matriz2[i][j];
                }
            }
            break;
        case '*':
            for (i = 0; i < operacion->size; i++) {
                for (j = 0; j < operacion->size; j++) {
                    operacion->resultado[i][j] = operacion->matriz1[i][j] * operacion->matriz2[i][j];
                }
            }
            break;

        case 'x':
            for (i = 0; i < operacion->size; i++) {
                for (j = 0; j < operacion->size; j++) {
                    operacion->resultado[i][j] = operacion->matriz1[i][j] * operacion->escalar;
                }
            }
            break;
        default:
            return 3;
            break;
    }
}

int main() {



    struct Operacion operacion;

    char respuesta[1];
    short int unicaOperacion = 0;
    short int operacionMatricial = 0;

    printf("¿Quiere realizar una operacón matricial? (y/n): ");
    scanf("%s", respuesta);

    if (respuesta[0] == 'y') {
        operacionMatricial = 1;
    }

    if(operacionMatricial) {
        struct OperacionMatricial operacionMatricial;

        printf("Ingrese el tamaño de las matrices: ");
        scanf("%d", &operacionMatricial.size);

        printf("Ingrese la operacion matricial (+, -, *, x[operacion escalar]): ");
        scanf("%s", operacionMatricial.operador);

        if(operacionMatricial.operador[0] == 'x') {
            printf("Ingrese el escalar: ");
            scanf("%lf", &operacionMatricial.escalar);

            printf("Ingrese los valores de la matriz: \n");
            for (int i = 0; i < operacionMatricial.size; i++) {
                for (int j = 0; j < operacionMatricial.size; j++) {
                    printf("Ingrese el valor de la posición (%d, %d): ", i, j);
                    scanf("%lf", &operacionMatricial.matriz1[i][j]);
                }
            }

            operar2(&operacionMatricial);

        }
        else {
            printf("Ingrese los valores de la primera matriz: \n");
            for (int i = 0; i < operacionMatricial.size; i++) {
                for (int j = 0; j < operacionMatricial.size; j++) {
                    printf("Ingrese el valor de la posición (%d, %d): ", i, j);
                    scanf("%lf", &operacionMatricial.matriz1[i][j]);
                }
            }

            printf("Ingrese los valores de la segunda matriz: \n");
            for (int i = 0; i < operacionMatricial.size; i++) {
                for (int j = 0; j < operacionMatricial.size; j++) {
                    printf("Ingrese el valor de la posición (%d, %d): ", i, j);
                    scanf("%lf", &operacionMatricial.matriz2[i][j]);
                }
            }

            operar2(&operacionMatricial);
        }


        printf("Resultado: \n");
        for (int i = 0; i < operacionMatricial.size; i++) {
            for (int j = 0; j < operacionMatricial.size; j++) {
                printf("%f ", operacionMatricial.resultado[i][j]);
            }
            printf("\n");
        }

        return 0;
    }

    if (!operacionMatricial) {

        printf("¿Quiere realizar más de una operación? (y/n): ");
        scanf("%s", respuesta);

        if (respuesta[0] == 'y') {
            unicaOperacion = 1;
        }

        // Solicitar al usuario que ingrese la operación
        printf("Ingrese una operacion (+, -, *, /): ");
        scanf("%s", operacion.operador);

        // Solicitar al usuario que ingrese dos números
        printf("Ingrese el primer numero: ");
        scanf("%lf", &operacion.num1);

        printf("Ingrese el segundo numero: ");
        scanf("%lf", &operacion.num2);

        int error = operar(&operacion);

        if(error == 2) {
            printf("Error: Division por cero\n");
        } else if(error == 3) {
            printf("Error: Operador invalido\n");
        } else {
            printf("Resultado: %f\n", operacion.resultado);
        }




        while (unicaOperacion == 1) {

            // Solicitar al usuario que ingrese dos números
            printf("¿Quiere utilizar el resultado anterior como este número?: (y/n):");
            scanf("%s", respuesta);

            if(respuesta[0] == 'n')
            {
                printf("Ingrese el primer numero: ");
                scanf("%lf", &operacion.num1);
            } else {
                operacion.num1 = operacion.resultado;
            }

            // Solicitar al usuario que ingrese la operación
            printf("Ingrese una operacion (+, -, *, /): ");
            scanf("%s", operacion.operador);

            printf("¿Quiere utilizar el resultado anterior como este número?: (y/n):");
            scanf("%s", respuesta);

            if(respuesta[0] == 'n')
            {
                printf("Ingrese el segundo numero: ");
                scanf("%lf", &operacion.num2);
            } else {
                operacion.num2 = operacion.resultado;
            }

            // Realizar la operación y mostrar el resultado
            int error = operar(&operacion);

            if(error == 2) {
                printf("Error: Division por cero\n");
            } else if(error == 3) {
                printf("Error: Operador invalido\n");
            } else {
                printf("Resultado: %f\n", operacion.resultado);
            }

            printf("¿Quiere realizar otra operación? (y/n):");
            scanf("%s", respuesta);

            if (respuesta[0] == 'n') {
                unicaOperacion = 0;
            }
        }
    }


    


    return 0;
}