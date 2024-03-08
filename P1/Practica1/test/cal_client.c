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
	clnt = clnt_create (host, CALPROG, CALVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = calculator_1(calculator_1_arg1, clnt);
	if (result_1 == (calculator_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
calprog_2(char *host)
{
	CLIENT *clnt;
	calculator_res  *result_1;
	operation calculator_2_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALPROG, CALVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = calculator_2(calculator_2_arg1, clnt);
	if (result_1 == (calculator_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	calprog_1 (host);
	calprog_2 (host);
exit (0);
}
