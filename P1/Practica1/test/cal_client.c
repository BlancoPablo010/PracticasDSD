/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "cal.h"


void
calprog_1(char *host)
{
	CLIENT *clnt;
	calculator_res  *result_1;
	operation calculator_1_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALPROG, CALVER1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	calculator_1_arg1.operator = malloc(1);

	char respuesta[1];
    short int unicaOperacion = 0;

    // Solicitar al usuario que ingrese dos números
    printf("Ingrese el primer numero: ");
    scanf("%lf", &calculator_1_arg1.firstNumber);

	printf("Ingrese una operación (+, -, *, /): ");
    scanf("%s", calculator_1_arg1.operator);

    printf("Ingrese el segundo numero: ");
    scanf("%lf", &calculator_1_arg1.secondNumber);


	result_1 = calculator_1(calculator_1_arg1, clnt);
	if (result_1 == (calculator_res *) NULL) {
		clnt_perror (clnt, "call failed");
		exit(1);
	}

	if(result_1->errnum == 2) {
		printf("Error: Division por cero\n");
	} else if(result_1->errnum == 3) {
		printf("Error: Operador invalido\n");
	} else {
		printf("%f %s %f = %f\n", calculator_1_arg1.firstNumber, calculator_1_arg1.operator, calculator_1_arg1.secondNumber, result_1->calculator_res_u);
	
	}

    printf("¿Quiere realizar otra operación? (y/n):");	
    scanf("%s", respuesta);

    if (respuesta[0] == 'y') {
        unicaOperacion = 1;
    }

	while(unicaOperacion == 1) {
		// Solicitar al usuario que ingrese dos números
        printf("¿Quiere utilizar el resultado anterior como el primer número?: (y/n):");
        scanf("%s", respuesta);

        if(respuesta[0] == 'n')
        {
            printf("Ingrese el primer número: ");
            scanf("%lf", &calculator_1_arg1.firstNumber);
        } else {
            calculator_1_arg1.firstNumber = result_1->calculator_res_u.res;
        }

        // Solicitar al usuario que ingrese la operación
        printf("Ingrese un operador (+, -, *, /): ");
        scanf("%s", calculator_1_arg1.operator);

        printf("¿Quiere utilizar el resultado anterior como el segundo número?: (y/n):");
        scanf("%s", respuesta);

        if(respuesta[0] == 'n')
        {
            printf("Ingrese el segundo número: ");
            scanf("%lf", &calculator_1_arg1.secondNumber);
        } else {
            calculator_1_arg1.secondNumber = result_1->calculator_res_u.res;
        }

		result_1 = calculator_1(calculator_1_arg1, clnt);
		if (result_1 == (calculator_res *) NULL) {
			clnt_perror (clnt, "call failed");
			exit(1);
		}

		if(result_1->errnum == 2) {
			printf("Error: Division por cero\n");
		} else if(result_1->errnum == 3) {
			printf("Error: Operador invalido\n");
		} else {
			printf("%f %s %f = %f\n", calculator_1_arg1.firstNumber, calculator_1_arg1.operator, calculator_1_arg1.secondNumber, result_1->calculator_res_u);
		
		}

		printf("¿Quiere realizar otra operación? (y/n):");
		scanf("%s", respuesta);

		if(respuesta[0] == 'n') {
			unicaOperacion = 0;
		}
	}

	xdr_free(xdr_calculator_res, result_1);
	free(calculator_1_arg1.operator);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

void
calprog_2(char *host)
{
	CLIENT *clnt;
	calculator_2_res  *result_1;
	operationMatrix calculator_matrix_2_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALPROG, CALVER2, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	calculator_matrix_2_arg1.operator = malloc(1);
	

	do {
		printf("Ingrese el tamaño de las matrices(máx. 10): ");
		scanf("%d", &calculator_matrix_2_arg1.size);
	} while(calculator_matrix_2_arg1.size >= 10 || calculator_matrix_2_arg1.size < 0);

/*Asignar memoria a las matrices*/

	calculator_matrix_2_arg1.firstMatrix.matrix_len = calculator_matrix_2_arg1.size;
	calculator_matrix_2_arg1.firstMatrix.matrix_val = (vector_t *)malloc(calculator_matrix_2_arg1.size * sizeof(vector_t));
	calculator_matrix_2_arg1.secondMatrix.matrix_len = calculator_matrix_2_arg1.size;
	calculator_matrix_2_arg1.secondMatrix.matrix_val = (vector_t *)malloc(calculator_matrix_2_arg1.size * sizeof(vector_t));
	

	for(int i=0; i<calculator_matrix_2_arg1.size; i++) {
		calculator_matrix_2_arg1.firstMatrix.matrix_val[i].vector_t_len = calculator_matrix_2_arg1.size;
		calculator_matrix_2_arg1.firstMatrix.matrix_val[i].vector_t_val = (double *)malloc(calculator_matrix_2_arg1.size * sizeof(double));
		calculator_matrix_2_arg1.secondMatrix.matrix_val[i].vector_t_len = calculator_matrix_2_arg1.size;
		calculator_matrix_2_arg1.secondMatrix.matrix_val[i].vector_t_val = (double *)malloc(calculator_matrix_2_arg1.size * sizeof(double));
	}

	calculator_matrix_2_arg1.escalar = 1;


	printf("Ingrese los valores de la primera matriz: \n");
	for (int i = 0; i < calculator_matrix_2_arg1.size; i++) {
		for (int j = 0; j < calculator_matrix_2_arg1.size; j++) {
			printf("Ingrese el valor de la posición (%d, %d): ", i, j);
			scanf("%lf", &calculator_matrix_2_arg1.firstMatrix.matrix_val[i].vector_t_val[j]);
		}
	}

	do {
		printf("Ingrese la operacion matricial (+, -, *, x[operacion escalar]): ");
		scanf("%s", calculator_matrix_2_arg1.operator);
	}while(calculator_matrix_2_arg1.operator[0] != '+' && calculator_matrix_2_arg1.operator[0] != '-' && calculator_matrix_2_arg1.operator[0] != '*' && calculator_matrix_2_arg1.operator[0] != 'x');

	if(calculator_matrix_2_arg1.operator[0] == 'x') {
		printf("Ingrese el escalar: ");
		scanf("%lf", &calculator_matrix_2_arg1.escalar);

		printf("\n");

		for(int i=0; i<calculator_matrix_2_arg1.size; i++) {
			for(int j=0; j<calculator_matrix_2_arg1.size; j++) {
				printf("%f ", calculator_matrix_2_arg1.firstMatrix.matrix_val[i].vector_t_val[j]);
			}
			printf("\n");
		}
		printf("\nMatriz  x  %f  =\n", calculator_matrix_2_arg1.escalar);

		result_1 = calculator_matrix_2(calculator_matrix_2_arg1, clnt);
		if (result_1 == (calculator_res *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if (result_1->errnum == 3) {
			printf("Error: Operador invalido\n");

		}

	}
	else {

		printf("Ingrese los valores de la segunda matriz: \n");
		for (int i = 0; i < calculator_matrix_2_arg1.size; i++) {
			for (int j = 0; j < calculator_matrix_2_arg1.size; j++) {
				printf("Ingrese el valor de la posición (%d, %d): ", i, j);
				scanf("%lf", &calculator_matrix_2_arg1.secondMatrix.matrix_val[i].vector_t_val[j]);
			}
		}

		printf("\n");

		for (int i = 0; i < calculator_matrix_2_arg1.size; i++) {
			for (int j = 0; j < calculator_matrix_2_arg1.size; j++) {
				printf("%f ", calculator_matrix_2_arg1.firstMatrix.matrix_val[i].vector_t_val[j]);
			}
			printf("\n");
		}

		printf("\n%s\n\n", calculator_matrix_2_arg1.operator);

		for (int i = 0; i < calculator_matrix_2_arg1.size; i++) {
			for (int j = 0; j < calculator_matrix_2_arg1.size; j++) {
				printf("%f ", calculator_matrix_2_arg1.secondMatrix.matrix_val[i].vector_t_val[j]);
			}
			printf("\n");
		}

		printf("\n=\n");
		
		result_1 = calculator_matrix_2(calculator_matrix_2_arg1, clnt);
		if (result_1 == (calculator_res *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if (result_1->errnum == 3) {
			printf("Error: Operador invalido\n");
			
		}
	}

	printf("\n");

	for (int i = 0; i < calculator_matrix_2_arg1.size; i++) {
		for (int j = 0; j < calculator_matrix_2_arg1.size; j++) {
			printf("%f ", result_1->calculator_2_res_u.res.matrix_val[i].vector_t_val[j]);
		}
		printf("\n");
	}
	printf("\n");

	


/*Liberar memoria del operador y de matrices*/
	xdr_free(xdr_calculator_res, result_1);

	free(calculator_matrix_2_arg1.operator);
	
	for(int i=0; i<calculator_matrix_2_arg1.size; i++) {
		free(calculator_matrix_2_arg1.firstMatrix.matrix_val[i].vector_t_val);
		free(calculator_matrix_2_arg1.secondMatrix.matrix_val[i].vector_t_val);
	}
	free(calculator_matrix_2_arg1.firstMatrix.matrix_val);
	free(calculator_matrix_2_arg1.secondMatrix.matrix_val);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calprog_3(char *host)
{
	CLIENT *clnt;
	calculator_3_res  *result_1;
	operationVector calculator_vector_3_arg1;





#ifndef	DEBUG
	clnt = clnt_create (host, CALPROG, CALVER3, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	printf("Introduzca el tamaño de los vectores: \n");
	scanf("%d", &calculator_vector_3_arg1.size);
	calculator_vector_3_arg1.firstVector.vector_t_len = calculator_vector_3_arg1.size;
	calculator_vector_3_arg1.secondVector.vector_t_len = calculator_vector_3_arg1.size;
	
	calculator_vector_3_arg1.firstVector.vector_t_val = (double *)malloc(calculator_vector_3_arg1.size * sizeof(double));
	calculator_vector_3_arg1.secondVector.vector_t_val = (double *)malloc(calculator_vector_3_arg1.size * sizeof(double));

	
	calculator_vector_3_arg1.operator = malloc(1);

	printf("Introduzca los valores del primer vector:\n");
	for(int i=0; i<calculator_vector_3_arg1.size; i++) {
		printf("Introduzca el valor de la posición %d: ", i);
		scanf("%lf", &calculator_vector_3_arg1.firstVector.vector_t_val[i]);
	}

	do {
		printf("Introduzca el valor de la operación vectorial(+, -, *[producto escalar], x[producto vectorial, máx. tamaño 3]): \n");
		scanf("%s", calculator_vector_3_arg1.operator);
	} while(calculator_vector_3_arg1.operator[0] != '+' && calculator_vector_3_arg1.operator[0] != '-' && calculator_vector_3_arg1.operator[0] != '*' && calculator_vector_3_arg1.operator[0] != 'x');

	calculator_vector_3_arg1.escalar = 1;


	printf("Introduzca los valores del segundo vector:\n");
	for(int i=0; i<calculator_vector_3_arg1.size; i++) {
		printf("Introduzca el valor de la posición %d: ", i);
		scanf("%lf", &calculator_vector_3_arg1.secondVector.vector_t_val[i]);
	}

	
	result_1 = calculator_vector_3(calculator_vector_3_arg1, clnt);
	if (result_1 == (calculator_3_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if(result_1->errnum == 2) {
		printf("Error: Producto vectorial máximo de 3 dimensiones\n");
	}
	else if(result_1->errnum == 3) {
		printf("Error: Operador invalido\n");
	
	}

	printf("\n[ ");

	for(int i=0; i<calculator_vector_3_arg1.size; i++) {
		printf("%f ", calculator_vector_3_arg1.firstVector.vector_t_val[i]);
	}
	printf("]\n\n%s\n\n[ ", calculator_vector_3_arg1.operator);
	for(int i=0; i<calculator_vector_3_arg1.size; i++) {
		printf("%f ", calculator_vector_3_arg1.secondVector.vector_t_val[i]);
	}

	printf("] \n\n=\n\n[ ");
	for(int i=0; i<result_1->calculator_3_res_u.res.vector_t_len; i++) {
		printf("%f ", result_1->calculator_3_res_u.res.vector_t_val[i]);
	}
	printf("]\n\n");

	xdr_free(xdr_calculator_3_res, result_1);
	free(calculator_vector_3_arg1.operator);
	free(calculator_vector_3_arg1.firstVector.vector_t_val);
	free(calculator_vector_3_arg1.secondVector.vector_t_val);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	int opcion = 0;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	while(opcion != 4) {

		printf("Calculadora:\nSeleccione una opción:\n1. Operación de flotantes.\n2. Operación de matrices.\n3. Operación de vectores.\n4. Salir.\n"); 
		scanf("%d", &opcion);

		switch(opcion) {
			case 1:
				calprog_1 (host);
				break;
			case 2:
				calprog_2 (host);
				break;
			case 3:
				calprog_3 (host);
				break;
			case 4:
				break;
			default:
				printf("Opción invalida\n");
				break;
		}
	}

	
exit (0);
}
