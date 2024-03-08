/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "cal.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

calculator_res *
calculator_1(operation arg1,  CLIENT *clnt)
{
	static calculator_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, CALCULATOR,
		(xdrproc_t) xdr_operation, (caddr_t) &arg1,
		(xdrproc_t) xdr_calculator_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

calculator_res *
calculator_2(operation arg1,  CLIENT *clnt)
{
	static calculator_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, CALCULATOR,
		(xdrproc_t) xdr_operation, (caddr_t) &arg1,
		(xdrproc_t) xdr_calculator_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
