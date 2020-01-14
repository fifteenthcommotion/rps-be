#include "rps.h"



int main () {
	sqlite3 *pdb = NULL;
	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char *qs = getenv("QUERY_STRING");
	char username [256];
	char password [256];
	char buffer [SQLMAXLEN];
	char * token;

	int pqs_out;
	pqs_out = parseqs(qs,username,password,NULL,NULL,NULL);
	failonout(pqs_out,pdb);

	snprintf(buffer,SQLMAXLEN,"INSERT INTO players (username,password) VALUES ('%.255s','%.255s')",username,password);

	sqlite3_open(DB_PATH,&pdb);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	flag = sqlite3_step(pst);

	while (flag==SQLITE_BUSY) flag = sqlite3_step(pst);
	sqlite3_finalize(pst);


	if (flag==SQLITE_ERROR) fail_400("Username taken",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);
	
	success_200("success",pdb);


}
