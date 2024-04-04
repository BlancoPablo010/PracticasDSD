/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CAL_H_RPCGEN
#define _CAL_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAX 1
#define MAX_SIZE 10

typedef struct {
	u_int vector_t_len;
	double *vector_t_val;
} vector_t;

typedef struct {
	u_int matrix_len;
	vector_t *matrix_val;
} matrix;

typedef char *operatorType;

typedef struct Operation operation;

typedef struct OperationMatrix operationMatrix;

typedef struct OperationVector operationVector;

struct Operation {
	double firstNumber;
	operatorType operator;
	double secondNumber;
};
typedef struct Operation Operation;

struct OperationMatrix {
	int size;
	matrix firstMatrix;
	operatorType operator;
	matrix secondMatrix;
	double escalar;
};
typedef struct OperationMatrix OperationMatrix;

struct OperationVector {
	int size;
	vector_t firstVector;
	operatorType operator;
	vector_t secondVector;
	double escalar;
};
typedef struct OperationVector OperationVector;

struct calculator_res {
	int errnum;
	union {
		double res;
	} calculator_res_u;
};
typedef struct calculator_res calculator_res;

struct calculator_2_res {
	int errnum;
	union {
		matrix res;
	} calculator_2_res_u;
};
typedef struct calculator_2_res calculator_2_res;

struct calculator_3_res {
	int errnum;
	union {
		vector_t res;
	} calculator_3_res_u;
};
typedef struct calculator_3_res calculator_3_res;

#define CALPROG 0x20000155
#define CALVER1 1

#if defined(__STDC__) || defined(__cplusplus)
#define CALCULATOR 1
extern  calculator_res * calculator_1(operation , CLIENT *);
extern  calculator_res * calculator_1_svc(operation , struct svc_req *);
extern int calprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define CALCULATOR 1
extern  calculator_res * calculator_1();
extern  calculator_res * calculator_1_svc();
extern int calprog_1_freeresult ();
#endif /* K&R C */
#define CALVER2 2

#if defined(__STDC__) || defined(__cplusplus)
#define CALCULATOR_MATRIX 1
extern  calculator_2_res * calculator_matrix_2(operationMatrix , CLIENT *);
extern  calculator_2_res * calculator_matrix_2_svc(operationMatrix , struct svc_req *);
extern int calprog_2_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define CALCULATOR_MATRIX 1
extern  calculator_2_res * calculator_matrix_2();
extern  calculator_2_res * calculator_matrix_2_svc();
extern int calprog_2_freeresult ();
#endif /* K&R C */
#define CALVER3 3

#if defined(__STDC__) || defined(__cplusplus)
#define CALCULATOR_VECTOR 1
extern  calculator_3_res * calculator_vector_3(operationVector , CLIENT *);
extern  calculator_3_res * calculator_vector_3_svc(operationVector , struct svc_req *);
extern int calprog_3_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define CALCULATOR_VECTOR 1
extern  calculator_3_res * calculator_vector_3();
extern  calculator_3_res * calculator_vector_3_svc();
extern int calprog_3_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_vector_t (XDR *, vector_t*);
extern  bool_t xdr_matrix (XDR *, matrix*);
extern  bool_t xdr_operatorType (XDR *, operatorType*);
extern  bool_t xdr_operation (XDR *, operation*);
extern  bool_t xdr_operationMatrix (XDR *, operationMatrix*);
extern  bool_t xdr_operationVector (XDR *, operationVector*);
extern  bool_t xdr_Operation (XDR *, Operation*);
extern  bool_t xdr_OperationMatrix (XDR *, OperationMatrix*);
extern  bool_t xdr_OperationVector (XDR *, OperationVector*);
extern  bool_t xdr_calculator_res (XDR *, calculator_res*);
extern  bool_t xdr_calculator_2_res (XDR *, calculator_2_res*);
extern  bool_t xdr_calculator_3_res (XDR *, calculator_3_res*);

#else /* K&R C */
extern bool_t xdr_vector_t ();
extern bool_t xdr_matrix ();
extern bool_t xdr_operatorType ();
extern bool_t xdr_operation ();
extern bool_t xdr_operationMatrix ();
extern bool_t xdr_operationVector ();
extern bool_t xdr_Operation ();
extern bool_t xdr_OperationMatrix ();
extern bool_t xdr_OperationVector ();
extern bool_t xdr_calculator_res ();
extern bool_t xdr_calculator_2_res ();
extern bool_t xdr_calculator_3_res ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CAL_H_RPCGEN */