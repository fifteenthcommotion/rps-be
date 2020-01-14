#include "rps.h"

void fail_400(const char * const message, sqlite3 *pdb) {
	printf("Content-type: text/plain; charset=utf-8\n");
	printf("Status: 400 Bad Request\n\n");
	printf("%s\n",message);
	sqlite3_close(pdb);
	exit(0);
}

void fail_500(const char * const message, sqlite3 *pdb) {
	printf("Content-type: text/plain; charset=utf-8\n");
	printf("Status: 500 Internal Server Error\n\n");
	printf("%s\n",message);
	sqlite3_close(pdb);
	exit(0);
}

void success_200(const char * const message, sqlite3 *pdb) {
	printf("Content-type: text/plain; charset=utf-8\n");
	printf("Status: 200 OK\n\n");
	printf("%s\n",message);
	sqlite3_close(pdb);
	exit(0);
}

