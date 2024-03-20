/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "cal.h"

calculator_res *
calculator_1_svc(operation arg1,  struct svc_req *rqstp)
{
	static calculator_res  result;

	/*
	 * insert server code here
	 */

	return &result;
}

calculator_2_res *
calculator_matrix_2_svc(operationMatrix arg1,  struct svc_req *rqstp)
{
	static calculator_2_res  result;

	/*
	 * insert server code here
	 */

	return &result;
}

calculator_3_res *
calculator_vector_3_svc(operationVector arg1,  struct svc_req *rqstp)
{
	static calculator_3_res  result;

	switch (arg1.operator) {
		case "+":
			result.calculator_3_res_u.res.vector_t_len = arg1.size;
			result.calculator_3_res_u.res.vector_t_val = (double *)malloc(arg1.size * sizeof(double));
			for (int i = 0; i < arg1.size; i++) {
				result.calculator_3_res_u.res.vector_t_val[i] = arg1.firstVector.vector_t_val[i] + arg1.secondVector.vector_t_val[i];
			}
			break;
		case "-":
			result.calculator_3_res_u.res.vector_t_len = arg1.size;
			result.calculator_3_res_u.res.vector_t_val = (double *)malloc(arg1.size * sizeof(double));
			for (int i = 0; i < arg1.size; i++) {
				result.calculator_3_res_u.res.vector_t_val[i] = arg1.firstVector.vector_t_val[i] - arg1.secondVector.vector_t_val[i];
			}
			break;
		case "*":
		    result.calculator_3_res_u.res.vector_t_len = 1;
			result.calculator_3_res_u.res.vector_t_val = (double *)malloc(sizeof(double));
			result.calculator_3_res_u.res.vector_t_val[0] = 0;
			for (int i = 0; i < arg1.size; i++) {
				result.calculator_3_res_u.res.vector_t_val[0] += arg1.firstVector.vector_t_val[i] * arg1.secondVector.vector_t_val[i];
			}
			break;
		case "x":
		    if(arg1.size != 3) {
				result.errnum = 2;
		        return &result;
		    }
			else {
				result.calculator_3_res_u.res.vector_t_len = 3;
				result.calculator_3_res_u.res.vector_t_val = (double *)malloc(3 * sizeof(double));
				result.calculator_3_res_u.res.vector_t_val[0] = arg1.firstVector.vector_t_val[1] * arg1.secondVector.vector_t_val[2] - arg1.firstVector.vector_t_val[2] * arg1.secondVector.vector_t_val[1];
				result.calculator_3_res_u.res.vector_t_val[1] = arg1.firstVector.vector_t_val[2] * arg1.secondVector.vector_t_val[0] - arg1.firstVector.vector_t_val[0] * arg1.secondVector.vector_t_val[2];
				result.calculator_3_res_u.res.vector_t_val[2] = arg1.firstVector.vector_t_val[0] * arg1.secondVector.vector_t_val[1] - arg1.firstVector.vector_t_val[1] * arg1.secondVector.vector_t_val[0];
				break;
			}
		default:
			result.errnum = 3;
			return &result;
			break;
	}

	return &result;
}
